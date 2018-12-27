/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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

#include "contactgrantleeemail.h"
using namespace KAddressBookGrantlee;

ContactGrantleeEmail::ContactGrantleeEmail(const KContacts::Addressee &addressee, const KContacts::Email &email, QObject *parent)
    : QObject(parent)
    , mEmail(email)
    , mAddressee(addressee)
{
}

ContactGrantleeEmail::~ContactGrantleeEmail()
{
}

QString ContactGrantleeEmail::email() const
{
    const QString email = mEmail.mail();
    return mAddressee.fullEmail(email);
}

bool ContactGrantleeEmail::preferred() const
{
    const QStringList value = mEmail.parameters().value(QStringLiteral("type"));
    //Validate PREF and pref
    return value.contains(QLatin1String("pref"), Qt::CaseInsensitive);
}

QString ContactGrantleeEmail::emailFormatted() const
{
    const QString email = mEmail.mail();
    const QString fullEmail = QString::fromLatin1(QUrl::toPercentEncoding(mAddressee.fullEmail(email)));

    const QString url = QStringLiteral("<a href=\"mailto:%1\">%2</a>")
                        .arg(fullEmail, email);
    return url;
}
