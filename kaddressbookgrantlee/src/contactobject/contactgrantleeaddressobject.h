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

#ifndef PRINT_CONTACTGRANTLEEADDRESSOBJECT_H
#define PRINT_CONTACTGRANTLEEADDRESSOBJECT_H
#include <QObject>
#include <KContacts/Addressee>
namespace KAddressBookGrantlee {
class ContactGrantleeAddressObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type)
    Q_PROPERTY(QString street READ street)
    Q_PROPERTY(QString postOfficeBox READ postOfficeBox)
    Q_PROPERTY(QString locality READ locality)
    Q_PROPERTY(QString region READ region)
    Q_PROPERTY(QString postalCode READ postalCode)
    Q_PROPERTY(QString country READ country)
    Q_PROPERTY(QString label READ label)
    Q_PROPERTY(QString formattedAddress READ formattedAddress)

public:
    explicit ContactGrantleeAddressObject(const KContacts::Address &address, QObject *parent = nullptr);
    ~ContactGrantleeAddressObject();

    Q_REQUIRED_RESULT QString type() const;
    Q_REQUIRED_RESULT QString street() const;
    Q_REQUIRED_RESULT QString postOfficeBox() const;
    Q_REQUIRED_RESULT QString locality() const;
    Q_REQUIRED_RESULT QString region() const;
    Q_REQUIRED_RESULT QString postalCode() const;
    Q_REQUIRED_RESULT QString country() const;
    Q_REQUIRED_RESULT QString label() const;
    Q_REQUIRED_RESULT QString formattedAddress() const;

private:
    KContacts::Address mAddress;
};
}
#endif // PRINT_CONTACTGRANTLEEADDRESSOBJECT_H
