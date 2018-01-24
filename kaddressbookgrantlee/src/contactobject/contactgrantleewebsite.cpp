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

#include "contactgrantleewebsite.h"
#include <QUrl>

using namespace KAddressBookGrantlee;

ContactGrantleeWebSite::ContactGrantleeWebSite(const KContacts::ResourceLocatorUrl &resourceLocator, QObject *parent)
    : QObject(parent)
    , mResourceLocator(resourceLocator)
{
}

ContactGrantleeWebSite::~ContactGrantleeWebSite()
{
}

QString ContactGrantleeWebSite::url() const
{
    return mResourceLocator.url().toDisplayString();
}

bool ContactGrantleeWebSite::preferred() const
{
    const QStringList value = mResourceLocator.parameters().value(QStringLiteral("type"));
    //Validate PREF and pref
    return value.contains(QLatin1String("pref"), Qt::CaseInsensitive);
}
