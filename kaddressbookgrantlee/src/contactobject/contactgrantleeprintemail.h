/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

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

#ifndef CONTACTGRANTLEEPRINTEMAIL_H
#define CONTACTGRANTLEEPRINTEMAIL_H

#include <QObject>

#include <KContacts/Addressee>
#include <KContacts/Email>

namespace KAddressBookGrantlee
{
class ContactGrantleeEmail : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString emailFormatted READ emailFormatted)
    Q_PROPERTY(QString email READ email)
    Q_PROPERTY(bool preferred READ preferred)
public:
    explicit ContactGrantleeEmail(const KContacts::Addressee &addressee, const KContacts::Email &email, QObject *parent = Q_NULLPTR);
    ~ContactGrantleeEmail();
    QString emailFormatted() const;

    QString email() const;
    bool preferred() const;
private:
    KContacts::Email mEmail;
    KContacts::Addressee mAddressee;
};
}
#endif // CONTACTGRANTLEEPRINTEMAIL_H
