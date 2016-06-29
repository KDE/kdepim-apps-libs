/*
   Copyright (C) 2014-2016 Montel Laurent <montel@kde.org>

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

#include "contactgrantleecryptoobject.h"
#include "Libkleo/Enum"

using namespace KAddressBookGrantlee;
inline QString loadCustom(const KContacts::Addressee &contact, const QString &key)
{
    return contact.custom(QStringLiteral("KADDRESSBOOK"), key);
}

ContactGrantleeCryptoObject::ContactGrantleeCryptoObject(const KContacts::Addressee &address, QObject *parent)
    : QObject(parent),
      mAddress(address)
{
}

ContactGrantleeCryptoObject::~ContactGrantleeCryptoObject()
{

}

QString ContactGrantleeCryptoObject::signaturePreference() const
{
    return Kleo::signingPreferenceToLabel(Kleo::stringToSigningPreference(loadCustom(mAddress, QStringLiteral("CRYPTOSIGNPREF"))));
}

QString ContactGrantleeCryptoObject::cryptoPreference() const
{
    return Kleo::encryptionPreferenceToLabel(Kleo::stringToEncryptionPreference(loadCustom(mAddress, QStringLiteral("CRYPTOENCRYPTPREF"))));
}
