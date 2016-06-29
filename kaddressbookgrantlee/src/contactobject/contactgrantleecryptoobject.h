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

#ifndef CONTACTGRANTLEEPRINTCRYPTOOBJECT_H
#define CONTACTGRANTLEEPRINTCRYPTOOBJECT_H
#include <QObject>
#include <KContacts/Addressee>
namespace KAddressBookGrantlee
{
class ContactGrantleeCryptoObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString signaturePreference READ signaturePreference)
    Q_PROPERTY(QString cryptoPreference READ cryptoPreference)
public:
    explicit ContactGrantleeCryptoObject(const KContacts::Addressee &address, QObject *parent = Q_NULLPTR);
    ~ContactGrantleeCryptoObject();

    QString signaturePreference() const;
    QString cryptoPreference() const;

private:
    KContacts::Addressee mAddress;
};
}

#endif // CONTACTGRANTLEEPRINTCRYPTOOBJECT_H
