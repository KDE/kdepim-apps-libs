/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

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
#include "contactobject/contactgrantleewrapper.h"

#include <grantlee/context.h>
#include <grantlee/engine.h>
#include <grantlee/metatype.h>
#include <grantlee/templateloader.h>

#include <QMetaProperty>
#include <QVariant>

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
GRANTLEE_MAKE_GADGET(KContacts::Geo)
GRANTLEE_MAKE_GADGET(KContacts::PhoneNumber)
GRANTLEE_MAKE_GADGET(KContacts::ResourceLocatorUrl)
GRANTLEE_MAKE_GADGET(KAddressBookGrantlee::ContactGrantleeWrapper)

GRANTLEE_BEGIN_LOOKUP(QUrl)
if (property == QLatin1String("scheme")) {
    return object.scheme();
}
GRANTLEE_END_LOOKUP

using namespace KAddressBookGrantlee;

GrantleePrint::GrantleePrint()
{
    init();
}

GrantleePrint::GrantleePrint(const QString &themePath)
    : GrantleeTheme::GenericFormatter(QStringLiteral("theme.html"), themePath)
{
    init();
}

GrantleePrint::~GrantleePrint() = default;

void GrantleePrint::init()
{
    Grantlee::registerMetaType<KContacts::Address>();
    Grantlee::registerMetaType<KContacts::Email>();
    Grantlee::registerMetaType<KContacts::Geo>();
    Grantlee::registerMetaType<KContacts::PhoneNumber>();
    Grantlee::registerMetaType<KContacts::ResourceLocatorUrl>();
    Grantlee::registerMetaType<QUrl>();
    Grantlee::registerMetaType<ContactGrantleeWrapper>();
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
    contactsList.reserve(contacts.count());
    for (const KContacts::Addressee &contact : contacts) {
        contactsList.push_back(QVariant::fromValue(ContactGrantleeWrapper(contact)));
    }
    QVariantHash mapping;
    mapping.insert(QStringLiteral("contacts"), contactsList);

    return render(mapping);
}
