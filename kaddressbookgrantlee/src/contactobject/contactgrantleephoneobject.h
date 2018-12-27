/*
   Copyright (C) 2013-2019 Montel Laurent <montel@kde.org>

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

#ifndef PRINT_CONTACTGRANTLEEPHONEOBJECT_H
#define PRINT_CONTACTGRANTLEEPHONEOBJECT_H
#include <QObject>
#include <KContacts/PhoneNumber>
namespace KAddressBookGrantlee {
class ContactGrantleePhoneObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type)
    Q_PROPERTY(QString number READ number)
    Q_PROPERTY(bool preferred READ preferred)

public:
    explicit ContactGrantleePhoneObject(const KContacts::PhoneNumber &phone, QObject *parent = nullptr);
    ~ContactGrantleePhoneObject();

    Q_REQUIRED_RESULT QString type() const;
    Q_REQUIRED_RESULT QString number() const;
    Q_REQUIRED_RESULT bool preferred() const;
private:
    KContacts::PhoneNumber mPhoneNumber;
};
}

#endif // PRINT_CONTACTGRANTLEEPHONEOBJECT_H
