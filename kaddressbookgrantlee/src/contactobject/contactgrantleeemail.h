/*
   Copyright (C) 2016-2018 Montel Laurent <montel@kde.org>

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

#ifndef PRINT_CONTACTGRANTLEEEMAIL_H
#define PRINT_CONTACTGRANTLEEEMAIL_H

#include <QObject>

#include <KContacts/Addressee>
#include <KContacts/Email>

namespace KAddressBookGrantlee {
class ContactGrantleeEmail : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString emailFormatted READ emailFormatted)
    Q_PROPERTY(QString email READ email)
    Q_PROPERTY(bool preferred READ preferred)
public:
    explicit ContactGrantleeEmail(const KContacts::Addressee &addressee, const KContacts::Email &email, QObject *parent = nullptr);
    ~ContactGrantleeEmail();
    Q_REQUIRED_RESULT QString emailFormatted() const;

    Q_REQUIRED_RESULT QString email() const;
    Q_REQUIRED_RESULT bool preferred() const;
private:
    KContacts::Email mEmail;
    KContacts::Addressee mAddressee;
};
}
#endif // PRINT_CONTACTGRANTLEEEMAIL_H
