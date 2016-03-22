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

#include "contactgrantleeprintemail.h"
using namespace KAddressBookGrantlee;

ContactGrantleePrintEmail::ContactGrantleePrintEmail(const KContacts::Addressee &addressee, const KContacts::Email &email, QObject *parent)
    : QObject(parent),
      mEmail(email),
      mAddressee(addressee)
{

}

ContactGrantleePrintEmail::~ContactGrantleePrintEmail()
{

}

QString ContactGrantleePrintEmail::email() const
{
    //TODO
    return {};
}

QString ContactGrantleePrintEmail::emailFormatted() const
{
    const QString email = mEmail.mail();
    const QString fullEmail = QString::fromLatin1(QUrl::toPercentEncoding(mAddressee.fullEmail(email)));

    const QString url = QStringLiteral("<a href=\"mailto:%1\">%2</a>")
                        .arg(fullEmail, email);
    return url;
}
