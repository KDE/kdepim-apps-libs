/*
  This file is part of KAddressBook.

  Copyright (c) 2010 Tobias Koenig <tokoe@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
*/

#include "grantleecontactformatter.h"
#include "grantleetheme/grantleetheme.h"
#include "grantleecontactutils.h"
#include "../contactobject/contactgrantleeimobject.h"
#include "../contactobject/contactgrantleecryptoobject.h"

#include <KContacts/Addressee>

#include <GrantleeTheme/GrantleeThemeEngine>
#include <GrantleeTheme/GrantleeKi18nLocalizer>

#include <grantlee/context.h>
#include <grantlee/metatype.h>
#include <grantlee/templateloader.h>

#include <AkonadiCore/Item>

#include <KColorScheme>

#include <KIconLoader>
#include <KStringHandler>
#include <KConfigGroup>
#include <KLocalizedString>

#include <contacteditor/improtocols.h>

#include <QLocale>
#include <QMetaProperty>
#include <QRegularExpression>
#include <QSet>

using namespace KAddressBookGrantlee;

// Grantlee has no Q_GADGET support yet
#define GRANTLEE_MAKE_GADGET(Class) \
    GRANTLEE_BEGIN_LOOKUP(Class) \
    const auto idx = Class::staticMetaObject.indexOfProperty(property.toUtf8().constData()); \
    if (idx < 0) { \
        return {};} \
    const auto mp = Class::staticMetaObject.property(idx); \
    return mp.readOnGadget(&object); \
    GRANTLEE_END_LOOKUP

GRANTLEE_MAKE_GADGET(KContacts::Address)
GRANTLEE_MAKE_GADGET(KContacts::Email)
GRANTLEE_MAKE_GADGET(KContacts::PhoneNumber)
GRANTLEE_MAKE_GADGET(KContacts::ResourceLocatorUrl)

GRANTLEE_BEGIN_LOOKUP(QUrl)
if (property == QLatin1String("scheme")) {
    return object.scheme();
}
GRANTLEE_END_LOOKUP

class Q_DECL_HIDDEN GrantleeContactFormatter::Private
{
public:
    Private()
        : forceDisableQRCode(false)
        , showQRCode(true)
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QStringLiteral("View"));
        showQRCode = group.readEntry("QRCodes", true);

        mEngine.reset(new GrantleeTheme::Engine);

        mTemplateLoader = QSharedPointer<Grantlee::FileSystemTemplateLoader>(new Grantlee::FileSystemTemplateLoader());
    }

    ~Private()
    {
        mTemplateLoader.clear();
    }

    void changeGrantleePath(const QString &path)
    {
        mTemplateLoader->setTemplateDirs(QStringList() << path);
        mEngine->addTemplateLoader(mTemplateLoader);

        mSelfcontainedTemplate = mEngine->loadByName(QStringLiteral("contact.html"));
        if (mSelfcontainedTemplate->error()) {
            mErrorMessage += mSelfcontainedTemplate->errorString() + QStringLiteral("<br>");
        }

        mEmbeddableTemplate = mEngine->loadByName(QStringLiteral("contact_embedded.html"));
        if (mEmbeddableTemplate->error()) {
            mErrorMessage += mEmbeddableTemplate->errorString() + QStringLiteral("<br>");
        }
    }

    QVector<QObject *> mObjects;
    std::unique_ptr<GrantleeTheme::Engine> mEngine;
    QSharedPointer<Grantlee::FileSystemTemplateLoader> mTemplateLoader;
    Grantlee::Template mSelfcontainedTemplate;
    Grantlee::Template mEmbeddableTemplate;
    QString mErrorMessage;
    bool forceDisableQRCode = false;
    bool showQRCode = false;
};

GrantleeContactFormatter::GrantleeContactFormatter()
    : d(new Private)
{
    Grantlee::registerMetaType<KContacts::Address>();
    Grantlee::registerMetaType<KContacts::Email>();
    Grantlee::registerMetaType<KContacts::PhoneNumber>();
    Grantlee::registerMetaType<KContacts::ResourceLocatorUrl>();
    Grantlee::registerMetaType<QUrl>();
}

GrantleeContactFormatter::~GrantleeContactFormatter()
{
    delete d;
}

void GrantleeContactFormatter::setAbsoluteThemePath(const QString &path)
{
    d->changeGrantleePath(path);
}

void GrantleeContactFormatter::setGrantleeTheme(const GrantleeTheme::Theme &theme)
{
    d->changeGrantleePath(theme.absolutePath());
}

void GrantleeContactFormatter::setForceDisableQRCode(bool b)
{
    if (d->forceDisableQRCode != b) {
        d->forceDisableQRCode = b;
    }
}

bool GrantleeContactFormatter::forceDisableQRCode() const
{
    return d->forceDisableQRCode;
}

void GrantleeContactFormatter::setShowQRCode(bool b)
{
    d->showQRCode = b;
}

inline static void setHashField(QVariantHash &hash, const QString &name, const QString &value)
{
    if (!value.isEmpty()) {
        hash.insert(name, value);
    }
}

static QVariantHash imAddressHash(const QString &typeKey, const QString &imAddress)
{
    QVariantHash addressObject;

    const QString dispLabel = i18nc("@title:row label for an Instant Messaging address, %1 is I18Ned protocol name",
                                    "IM (%1)", IMProtocols::self()->name(typeKey));

    setHashField(addressObject, QStringLiteral("type"), dispLabel);
    setHashField(addressObject, QStringLiteral("imAddress"), imAddress);

    const QString iconUrl = QUrl::fromLocalFile(KIconLoader::global()->iconPath(IMProtocols::self()->icon(typeKey),
                                                                                -KIconLoader::SizeSmall)).url();
    const QString url = QStringLiteral("<img src=\"%1\" align=\"top\" height=\"%2\" width=\"%2\"/>").arg(iconUrl, QString::number(KIconLoader::SizeSmall));
    addressObject.insert(QStringLiteral("imIcon"), url);

    return addressObject;
}

static int contactAge(const QDate &date)
{
    QDate now = QDate::currentDate();
    int age = now.year() - date.year();
    if (date > now.addYears(-age)) {
        age--;
    }
    return age;
}

QString GrantleeContactFormatter::toHtml(HtmlForm form) const
{
    if (!d->mErrorMessage.isEmpty()) {
        return d->mErrorMessage;
    }

    KContacts::Addressee rawContact;
    const Akonadi::Item localItem = item();
    if (localItem.isValid() && localItem.hasPayload<KContacts::Addressee>()) {
        rawContact = localItem.payload<KContacts::Addressee>();
    } else {
        rawContact = contact();
    }

    if (rawContact.isEmpty()) {
        return QString();
    }

    QVariantHash contactObject;
    GrantleeContactUtils grantleeContactUtil;
    // Name parts
    setHashField(contactObject, QStringLiteral("name"), rawContact.realName());
    setHashField(contactObject, QStringLiteral("formattedName"), rawContact.formattedName());
    setHashField(contactObject, QStringLiteral("prefix"), rawContact.prefix());
    setHashField(contactObject, QStringLiteral("givenName"), rawContact.givenName());
    setHashField(contactObject, QStringLiteral("additionalName"), rawContact.additionalName());
    setHashField(contactObject, QStringLiteral("familyName"), rawContact.familyName());
    setHashField(contactObject, QStringLiteral("suffix"), rawContact.suffix());
    setHashField(contactObject, QStringLiteral("nickName"), rawContact.nickName());

    // Dates
    const QDate birthday = rawContact.birthday().date();
    if (birthday.isValid()) {
        grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("birthdayi18n"));

        const QString formattedBirthday = QLocale().toString(birthday);
        contactObject.insert(QStringLiteral("birthday"), formattedBirthday);

        const int years = contactAge(birthday);
        contactObject.insert(QStringLiteral("age"), QString::number(years));
        contactObject.insert(QStringLiteral("birthdayage"), QString(formattedBirthday
                                                                    +QStringLiteral("&nbsp;&nbsp;")
                                                                    +i18np("(One year old)", "(%1 years old)", years)));
    }

    const QDate anniversary
        = QDate::fromString(rawContact.custom(QStringLiteral("KADDRESSBOOK"),
                                              QStringLiteral("X-Anniversary")), Qt::ISODate);
    if (anniversary.isValid()) {
        contactObject.insert(QStringLiteral("anniversary"),
                             QLocale().toString(anniversary));
        grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("anniversaryi18n"));
    }

    // Emails
    grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("emailsi18n"));
    contactObject.insert(QStringLiteral("emails"), QVariant::fromValue(rawContact.emailList()));

    // Phone numbers
    contactObject.insert(QStringLiteral("phoneNumbers"), QVariant::fromValue(rawContact.phoneNumbers()));

    // IM
    QVariantList imAddresses;
    const QStringList customs = rawContact.customs();
    for (const QString &custom : customs) {
        if (custom.startsWith(QLatin1String("messaging/"))) {
            int pos = custom.indexOf(QLatin1Char(':'));
            QString key = custom.left(pos);
            key.remove(QStringLiteral("-All"));
            const QString value = custom.mid(pos + 1);

            imAddresses.append(imAddressHash(key, value));
        }
    }

    contactObject.insert(QStringLiteral("imAddresses"), imAddresses);

    // Homepage
    grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("websitei18n"));
    contactObject.insert(QStringLiteral("urls"), QVariant::fromValue(rawContact.extraUrlList()));

    // Blog Feed
    contactObject.insert(QStringLiteral("blogFeed"), rawContact.blogFeed());
    grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("blogUrli18n"));

    // Address Book
    const QString addressBookName
        = rawContact.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("AddressBook"));
    if (!addressBookName.isEmpty()) {
        contactObject.insert(QStringLiteral("addressBookName"), addressBookName);
        grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("addressBookNamei18n"));
    }

    // Addresses
    contactObject.insert(QStringLiteral("addresses"), QVariant::fromValue(rawContact.addresses()));

    // Note
    if (!rawContact.note().isEmpty()) {
        const QString notes = QStringLiteral("<a>%1</a>").arg(rawContact.note().replace(QLatin1Char('\n'), QStringLiteral("<br>")));
        contactObject.insert(QStringLiteral("note"), notes);
        grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("notei18n"));
    }


    setHashField(contactObject, QStringLiteral("mailer"), rawContact.mailer());

    setHashField(contactObject, QStringLiteral("title"), rawContact.title());

    setHashField(contactObject, QStringLiteral("role"), rawContact.role());

    QString job = rawContact.title();
    if (job.isEmpty()) {
        job = rawContact.role();
    }
    if (job.isEmpty()) {
        job = rawContact.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Profession"));
    }
    setHashField(contactObject, QStringLiteral("job"), job);

    setHashField(contactObject, QStringLiteral("organization"), rawContact.organization());

    setHashField(contactObject, QStringLiteral("department"), rawContact.department());
    grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("departmenti18n"));

    //setHashField( contactObject, QStringLiteral( "note" ), rawContact.note() );

    setHashField(contactObject, QStringLiteral("profession"),
                 rawContact.custom(QStringLiteral("KADDRESSBOOK"),
                                   QStringLiteral("X-Profession")));
    grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("Professioni18n"));
    setHashField(contactObject, QStringLiteral("office"),
                 rawContact.custom(QStringLiteral("KADDRESSBOOK"),
                                   QStringLiteral("X-Office")));
    grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("officei18n"));

    setHashField(contactObject, QStringLiteral("manager"),
                 rawContact.custom(QStringLiteral("KADDRESSBOOK"),
                                   QStringLiteral("X-ManagersName")));
    grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("manageri18n"));

    setHashField(contactObject, QStringLiteral("assistant"),
                 rawContact.custom(QStringLiteral("KADDRESSBOOK"),
                                   QStringLiteral("X-AssistantsName")));
    grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("assistanti18n"));

    setHashField(contactObject, QStringLiteral("spouse"),
                 rawContact.custom(QStringLiteral("KADDRESSBOOK"),
                                   QStringLiteral("X-SpousesName")));
    grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("spousei18n"));

    setHashField(contactObject, QStringLiteral("imAddress"),
                 rawContact.custom(QStringLiteral("KADDRESSBOOK"),
                                   QStringLiteral("X-IMAddress")));
    grantleeContactUtil.insertVariableToQVariantHash(contactObject, QStringLiteral("imAddressi18n"));

    // Custom fields

    QVariantList customFields;
    QVariantList customFieldsUrl;
    static QSet<QString> blacklistedKeys;
    if (blacklistedKeys.isEmpty()) {
        blacklistedKeys.insert(QStringLiteral("CRYPTOPROTOPREF"));
        blacklistedKeys.insert(QStringLiteral("OPENPGPFP"));
        blacklistedKeys.insert(QStringLiteral("SMIMEFP"));
        blacklistedKeys.insert(QStringLiteral("CRYPTOSIGNPREF"));
        blacklistedKeys.insert(QStringLiteral("CRYPTOENCRYPTPREF"));
        blacklistedKeys.insert(QStringLiteral("Anniversary"));
        blacklistedKeys.insert(QStringLiteral("BlogFeed"));
        blacklistedKeys.insert(QStringLiteral("Profession"));
        blacklistedKeys.insert(QStringLiteral("Office"));
        blacklistedKeys.insert(QStringLiteral("ManagersName"));
        blacklistedKeys.insert(QStringLiteral("AssistantsName"));
        blacklistedKeys.insert(QStringLiteral("SpousesName"));
        blacklistedKeys.insert(QStringLiteral("IMAddress"));
        blacklistedKeys.insert(QStringLiteral("AddressBook"));
        blacklistedKeys.insert(QStringLiteral("MailPreferedFormatting"));
        blacklistedKeys.insert(QStringLiteral("MailAllowToRemoteContent"));
        blacklistedKeys.insert(QStringLiteral("MAILPREFEREDFORMATTING"));
        blacklistedKeys.insert(QStringLiteral("MAILALLOWTOREMOTECONTENT"));
    }

    if (!customs.empty()) {
        for (QString custom : qAsConst(customs)) {   //krazy:exclude=foreach
            if (custom.startsWith(QLatin1String("KADDRESSBOOK-"))) {
                custom.remove(QStringLiteral("KADDRESSBOOK-X-"));
                custom.remove(QStringLiteral("KADDRESSBOOK-"));

                int pos = custom.indexOf(QLatin1Char(':'));
                QString key = custom.left(pos);
                QString value = custom.mid(pos + 1);

                if (blacklistedKeys.contains(key)) {
                    continue;
                }

                bool addUrl = false;
                // check whether it is a custom local field
                for (int i = 0; i < customFieldDescriptions().size(); ++i) {
                    const QVariantMap description = customFieldDescriptions().at(i);
                    if (description.value(QStringLiteral("key")).toString() == key) {
                        key = description.value(QStringLiteral("title")).toString();
                        const QString descriptionType = description.value(QStringLiteral("type")).toString();
                        if (descriptionType == QLatin1String("boolean")) {
                            if (value == QLatin1String("true")) {
                                value = i18nc("Boolean value", "yes");
                            } else {
                                value = i18nc("Boolean value", "no");
                            }
                        } else if (descriptionType == QLatin1String("date")) {
                            const QDate date = QDate::fromString(value, Qt::ISODate);
                            value = QLocale().toString(date, QLocale::ShortFormat);
                        } else if (descriptionType == QLatin1String("time")) {
                            const QTime time = QTime::fromString(value, Qt::ISODate);
                            value = QLocale::system().toString(time, QLocale::ShortFormat);
                        } else if (descriptionType == QLatin1String("datetime")) {
                            const QDateTime dateTime = QDateTime::fromString(value, Qt::ISODate);
                            value = QLocale().toString(dateTime, QLocale::ShortFormat);
                        } else if (descriptionType == QLatin1String("url")) {
                            value = KStringHandler::tagUrls(value.toHtmlEscaped());
                            addUrl = true;
                        }
                        break;
                    }
                }
                QVariantHash customFieldObject;
                customFieldObject.insert(QStringLiteral("title"), key);
                customFieldObject.insert(QStringLiteral("value"), value);

                if (addUrl) {
                    customFieldsUrl.append(customFieldObject);
                } else {
                    customFields.append(customFieldObject);
                }
            }
        }
    }

    contactObject.insert(QStringLiteral("customFields"), customFields);
    contactObject.insert(QStringLiteral("customFieldsUrl"), customFieldsUrl);

    if (!d->forceDisableQRCode) {
        if (d->showQRCode) {
            contactObject.insert(QStringLiteral("hasqrcode"), QStringLiteral("true"));
        }
    }

    QVariantHash colorsObject;

    colorsObject.insert(
        QStringLiteral("linkColor"),
        KColorScheme(QPalette::Active, KColorScheme::View).foreground().color().name());

    colorsObject.insert(
        QStringLiteral("textColor"),
        KColorScheme(QPalette::Active, KColorScheme::View).foreground().color().name());

    colorsObject.insert(
        QStringLiteral("backgroundColor"),
        KColorScheme(QPalette::Active, KColorScheme::View).background().color().name());

    QVariantHash mapping;
    mapping.insert(QStringLiteral("contact"), contactObject);
    mapping.insert(QStringLiteral("colors"), colorsObject);

    Grantlee::Context context(mapping);
    context.setLocalizer(d->mEngine->localizer());

    if (form == SelfcontainedForm) {
        return d->mSelfcontainedTemplate->render(&context);
    } else if (form == EmbeddableForm) {
        return d->mEmbeddableTemplate->render(&context);
    } else {
        return QString();
    }
}

void GrantleeContactFormatter::setApplicationDomain(const QByteArray &domain)
{
    d->mEngine->localizer()->setApplicationDomain(domain);
}
