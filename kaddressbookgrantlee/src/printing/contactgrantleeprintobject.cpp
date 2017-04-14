/*
   Copyright (C) 2013-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "contactgrantleeprintobject.h"
#include "../contactobject/contactgrantleeaddressobject.h"
#include "../contactobject/contactgrantleephoneobject.h"
#include "../contactobject/contactgrantleeimobject.h"
#include "../contactobject/contactgrantleegeoobject.h"
#include "../contactobject/contactgrantleecryptoobject.h"
#include "../contactobject/contactgrantleewebsite.h"
#include "../contactobject/contactgrantleeemail.h"

#include <KContacts/PhoneNumber>

#include <QBuffer>
#include <QVariant>
#include <grantlee/metatype.h>
#include <QLocale>
#include <QImage>

using namespace KAddressBookGrantlee;

ContactGrantleePrintObject::ContactGrantleePrintObject(const KContacts::Addressee &address, QObject *parent)
    : QObject(parent)
    , mAddress(address)
{
    const auto addresses = address.addresses();
    mListAddress.reserve(addresses.size());
    for (const KContacts::Address &addr : addresses) {
        mListAddress << new ContactGrantleeAddressObject(addr);
    }

    const auto webSites = address.extraUrlList();
    mListWebSite.reserve(webSites.size());
    for (const KContacts::ResourceLocatorUrl &webSite : webSites) {
        mListWebSite << new ContactGrantleeWebSite(webSite);
    }

    const auto phoneNumbers = address.phoneNumbers();
    mListPhones.reserve(phoneNumbers.size());
    for (const KContacts::PhoneNumber &phone : phoneNumbers) {
        mListPhones << new ContactGrantleePhoneObject(phone);
    }

    const auto emails = address.emailList();
    mListEmails.reserve(emails.size());
    for (const KContacts::Email &email : emails) {
        mListEmails << new ContactGrantleeEmail(mAddress, email);
    }

    const QStringList customs = mAddress.customs();
    for (const QString &custom : customs) {
        if (custom.startsWith(QStringLiteral("messaging/"))) {
            const int pos = custom.indexOf(QLatin1Char(':'));
            QString key = custom.left(pos);
            key.remove(QStringLiteral("-All"));
            const QString value = custom.mid(pos + 1);
            mListIm << new ContactGrantleeImObject(key, value);
        }
    }
    mGeoObject = new ContactGrantleeGeoObject(address.geo());
    mCryptoObject = new ContactGrantleeCryptoObject(address);
}

ContactGrantleePrintObject::~ContactGrantleePrintObject()
{
    delete mGeoObject;
    qDeleteAll(mListAddress);
    qDeleteAll(mListPhones);
    qDeleteAll(mListIm);
    qDeleteAll(mListWebSite);
    qDeleteAll(mListEmails);
    delete mCryptoObject;
}

QString ContactGrantleePrintObject::realName() const
{
    return mAddress.realName();
}

QString ContactGrantleePrintObject::formattedName() const
{
    return mAddress.formattedName();
}

QString ContactGrantleePrintObject::prefix() const
{
    return mAddress.prefix();
}

QString ContactGrantleePrintObject::givenName() const
{
    return mAddress.givenName();
}

QString ContactGrantleePrintObject::additionalName() const
{
    return mAddress.additionalName();
}

QString ContactGrantleePrintObject::familyName() const
{
    return mAddress.familyName();
}

QString ContactGrantleePrintObject::suffix() const
{
    return mAddress.suffix();
}

QString ContactGrantleePrintObject::nickName() const
{
    return mAddress.nickName();
}

QString ContactGrantleePrintObject::name() const
{
    return mAddress.name();
}

QString ContactGrantleePrintObject::languages() const
{
    QString result;
    QStringList langList;
    const KContacts::Lang::List lstLangs = mAddress.langs();
    langList.reserve(lstLangs.count());
    for (const KContacts::Lang &lang : lstLangs) {
        langList.append(lang.language());
    }
    if (!langList.isEmpty()) {
        result = langList.join(QLatin1Char(','));
    }
    return result;
}

QStringList ContactGrantleePrintObject::emails() const
{
    QStringList emails;
    const QStringList lstEmails(mAddress.emails());
    for (const QString &email : lstEmails) {
        const QString fullEmail = QString::fromLatin1(QUrl::toPercentEncoding(mAddress.fullEmail(email)));

        const QString url = QStringLiteral("<a href=\"mailto:%1\">%2</a>")
                            .arg(fullEmail, email);
        emails << url;
    }
    return emails;
}

QString ContactGrantleePrintObject::organization() const
{
    return mAddress.organization();
}

QString ContactGrantleePrintObject::note() const
{
    return mAddress.note().replace(QLatin1Char('\n'), QStringLiteral("<br>"));
}

QString ContactGrantleePrintObject::webPage() const
{
    return mAddress.url().url().toDisplayString();
}

QString ContactGrantleePrintObject::webSite() const
{
    return webPage();
}

QString ContactGrantleePrintObject::title() const
{
    return mAddress.title();
}

QString ContactGrantleePrintObject::preferredEmail() const
{
    return mAddress.preferredEmail();
}

QString ContactGrantleePrintObject::role() const
{
    return mAddress.role();
}

QString ContactGrantleePrintObject::birthday() const
{
    return QLocale().toString(mAddress.birthday().date(), QLocale::LongFormat);
}

QString ContactGrantleePrintObject::department() const
{
    return mAddress.department();
}

QVariant ContactGrantleePrintObject::addresses() const
{
    return QVariant::fromValue(mListAddress);
}

QVariant ContactGrantleePrintObject::webSites() const
{
    return QVariant::fromValue(mListWebSite);
}

QVariant ContactGrantleePrintObject::emailsList() const
{
    return QVariant::fromValue(mListEmails);
}

QVariant ContactGrantleePrintObject::phones() const
{
    return QVariant::fromValue(mListPhones);
}

QVariant ContactGrantleePrintObject::instantManging() const
{
    return QVariant::fromValue(mListIm);
}

QVariant ContactGrantleePrintObject::geo() const
{
    return QVariant::fromValue(mGeoObject);
}

QVariant ContactGrantleePrintObject::crypto() const
{
    return QVariant::fromValue(mCryptoObject);
}

QString ContactGrantleePrintObject::addressBookName() const
{
    const QString addressBookName = mAddress.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("AddressBook"));
    return addressBookName;
}

QString ContactGrantleePrintObject::photo() const
{
    if (mAddress.photo().isEmpty()) {
        return QString();
    } else {
        const QString photoStr = QStringLiteral("<img src=\"%1\" width=\"%2\" height=\"%3\"> &nbsp;")
                                 .arg(imgToDataUrl(mAddress.photo().data()), QString::number(60), QString::number(60));
        return photoStr;
    }
}

QString ContactGrantleePrintObject::imgToDataUrl(const QImage &image) const
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return QStringLiteral("data:image/%1;base64,%2").arg(QStringLiteral("PNG"), QString::fromLatin1(ba.toBase64()));
}

QString ContactGrantleePrintObject::logo() const
{
    if (mAddress.logo().isEmpty()) {
        return QString();
    } else {
        const QString photoStr = QStringLiteral("<img src=\"%1\" width=\"%2\" height=\"%3\"> &nbsp;")
                                 .arg(imgToDataUrl(mAddress.logo().data()), QString::number(60), QString::number(60));
        return photoStr;
    }
}

QString ContactGrantleePrintObject::anniversary() const
{
    const QDate anniversary = QDate::fromString(mAddress.custom(QStringLiteral("KADDRESSBOOK"),
                                                                QStringLiteral("X-Anniversary")), Qt::ISODate);
    if (anniversary.isValid()) {
        return QLocale().toString(anniversary);
    }
    return QString();
}

QString ContactGrantleePrintObject::profession() const
{
    return mAddress.custom(QStringLiteral("KADDRESSBOOK"),
                           QStringLiteral("X-Profession"));
}

QString ContactGrantleePrintObject::office() const
{
    return mAddress.custom(QStringLiteral("KADDRESSBOOK"),
                           QStringLiteral("X-Office"));
}

QString ContactGrantleePrintObject::manager() const
{
    return mAddress.custom(QStringLiteral("KADDRESSBOOK"),
                           QStringLiteral("X-ManagersName"));
}

QString ContactGrantleePrintObject::assistant() const
{
    return mAddress.custom(QStringLiteral("KADDRESSBOOK"),
                           QStringLiteral("X-AssistantsName"));
}

QString ContactGrantleePrintObject::spouse() const
{
    return mAddress.custom(QStringLiteral("KADDRESSBOOK"),
                           QStringLiteral("X-SpousesName"));
}
