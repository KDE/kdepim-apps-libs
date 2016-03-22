/*
  Copyright (c) 2013-2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "contactgrantleeprintaddressobject.h"

using namespace KAddressBookGrantlee;
ContactGrantleeAddressObject::ContactGrantleeAddressObject(const KContacts::Address &address, QObject *parent)
    : QObject(parent),
      mAddress(address)
{
}

ContactGrantleeAddressObject::~ContactGrantleeAddressObject()
{
}

QString ContactGrantleeAddressObject::type() const
{
    return KContacts::Address::typeLabel(mAddress.type());
}

QString ContactGrantleeAddressObject::street() const
{
    return mAddress.street();
}

QString ContactGrantleeAddressObject::postOfficeBox() const
{
    return mAddress.postOfficeBox();
}

QString ContactGrantleeAddressObject::locality() const
{
    return mAddress.locality();
}

QString ContactGrantleeAddressObject::region() const
{
    return mAddress.region();
}

QString ContactGrantleeAddressObject::postalCode() const
{
    return mAddress.postalCode();
}

QString ContactGrantleeAddressObject::country() const
{
    return mAddress.country();
}

QString ContactGrantleeAddressObject::label() const
{
    return mAddress.label();
}

QString ContactGrantleeAddressObject::formattedAddress() const
{
    return mAddress.formattedAddress().replace(QStringLiteral("\n"), QStringLiteral("<br>"));
}
