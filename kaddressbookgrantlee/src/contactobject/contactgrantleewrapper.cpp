/*
   Copyright (C) 2019 Volker Krause <vkrause@kde.org>

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

#include "contactgrantleewrapper.h"

#include <contacteditor/improtocols.h>

#include <KLocalizedString>

#include <QLocale>

using namespace KAddressBookGrantlee;

static_assert(sizeof(KContacts::Addressee) == sizeof(KAddressBookGrantlee::ContactGrantleeWrapper), "Grantlee wrapper must not have member variables to prevent sliciing issues");

QString ContactGrantleeWrapper::addressBookLabel() const
{
    return i18n("Address Book");
}

QString ContactGrantleeWrapper::anniversaryLabel() const
{
    return i18n("Anniversary");
}

QString ContactGrantleeWrapper::assistantLabel() const
{
    return i18n("Assistant's Name");
}

QString ContactGrantleeWrapper::managerLabel() const
{
    return i18n("Manager's Name");
}

QString ContactGrantleeWrapper::officeLabel() const
{
    return i18n("Office");
}

QString ContactGrantleeWrapper::professionLabel() const
{
    return i18n("Profession");
}

QString ContactGrantleeWrapper::spouseLabel() const
{
    return i18n("Partner's Name");
}

QString ContactGrantleeWrapper::addressBookName() const
{
    return custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("AddressBook"));
}

int ContactGrantleeWrapper::age() const
{
    QDate now = QDate::currentDate();
    int age = now.year() - birthday().date().year();
    if (birthday().date() > now.addYears(-age)) {
        age--;
    }
    return age;
}

QString ContactGrantleeWrapper::formattedBirthday() const
{
    return QLocale().toString(birthday().date());
}

QString ContactGrantleeWrapper::formattedAnniversary() const
{
    return QLocale().toString(anniversary());
}

static QVariantHash imAddressHash(const QString &typeKey, const QString &imAddress)
{
    QVariantHash addressObject;
    addressObject.insert(QStringLiteral("serviceLabel"), IMProtocols::self()->name(typeKey));
    addressObject.insert(QStringLiteral("address"), imAddress);
    addressObject.insert(QStringLiteral("serviceIcon"), IMProtocols::self()->icon(typeKey));
    return addressObject;
}

QVariantList ContactGrantleeWrapper::imAddresses() const
{
    QVariantList imAddrs;
    const QStringList customs = this->customs();
    for (const QString &custom : customs) {
        if (custom.startsWith(QLatin1String("messaging/"))) {
            const int pos = custom.indexOf(QLatin1Char(':'));
            QString key = custom.left(pos);
            key.remove(QStringLiteral("-All"));
            const QString value = custom.mid(pos + 1);
            imAddrs.append(imAddressHash(key, value));
        }
    }

    return imAddrs;
}
