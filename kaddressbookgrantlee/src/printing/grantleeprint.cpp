/*
   Copyright (C) 2015-2019 Montel Laurent <montel@kde.org>

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

#include "grantleeprint.h"
#include "contactgrantleeprintobject.h"

#include "formatter/grantleecontactutils.h"

#include <grantlee/context.h>
#include <grantlee/engine.h>
#include <grantlee/metatype.h>
#include <grantlee/templateloader.h>

#include <QMetaProperty>

// Grantlee has no Q_GADGET support yet
#define GRANTLEE_MAKE_GADGET(Class) \
    GRANTLEE_BEGIN_LOOKUP(Class) \
    const auto idx = Class::staticMetaObject.indexOfProperty(property.toUtf8().constData()); \
    if (idx < 0) { \
        return {};} \
    const auto mp = Class::staticMetaObject.property(idx); \
    return mp.readOnGadget(&object); \
    GRANTLEE_END_LOOKUP

GRANTLEE_MAKE_GADGET(KContacts::Geo)

using namespace KAddressBookGrantlee;

GrantleePrint::GrantleePrint(QObject *parent)
    : PimCommon::GenericGrantleeFormatter(parent)
{
    init();
}

GrantleePrint::GrantleePrint(const QString &themePath, QObject *parent)
    : PimCommon::GenericGrantleeFormatter(QStringLiteral("theme.html"), themePath, parent)
{
    init();
}

GrantleePrint::~GrantleePrint()
{
}

void GrantleePrint::init()
{
    Grantlee::registerMetaType<KContacts::Geo>();
}

QString GrantleePrint::contactsToHtml(const KContacts::Addressee::List &contacts)
{
    if (!errorMessage().isEmpty()) {
        return errorMessage();
    }

    if (contacts.isEmpty()) {
        return QString();
    }
    QVariantList contactsList;
    QList<ContactGrantleePrintObject *> lst;
    const int numberContacts(contacts.count());
    lst.reserve(numberContacts);
    contactsList.reserve(numberContacts);
    for (const KContacts::Addressee &address : contacts) {
        ContactGrantleePrintObject *contactPrintObject = new ContactGrantleePrintObject(address);
        lst.append(contactPrintObject);
        contactsList << QVariant::fromValue(static_cast<QObject *>(contactPrintObject));
    }
    QVariantHash mapping;
    QVariantHash contactI18n;
    GrantleeContactUtils grantleeContactUtil;
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("birthdayi18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("anniversaryi18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("emailsi18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("websitei18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("blogUrli18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("addressBookNamei18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("notei18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("departmenti18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("Professioni18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("officei18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("manageri18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("assistanti18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("spousei18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("imAddressi18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("latitudei18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("longitudei18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("organizationi18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("titlei18n"));
    grantleeContactUtil.insertVariableToQVariantHash(contactI18n, QStringLiteral("nextcontacti18n"));
    mapping.insert(QStringLiteral("contacti18n"), contactI18n);
    mapping.insert(QStringLiteral("contacts"), contactsList);

    const QString content = render(mapping);
    qDeleteAll(lst);
    return content;
}
