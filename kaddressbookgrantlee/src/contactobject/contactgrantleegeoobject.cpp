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

#include "contactgrantleegeoobject.h"

using namespace KAddressBookGrantlee;

ContactGrantleeGeoObject::ContactGrantleeGeoObject(const KContacts::Geo &geo, QObject *parent)
    : QObject(parent),
      mGeo(geo)
{

}

ContactGrantleeGeoObject::~ContactGrantleeGeoObject()
{

}

float ContactGrantleeGeoObject::latitude() const
{
    if (mGeo.isValid()) {
        return mGeo.latitude();
    }
    return -1;
}

float ContactGrantleeGeoObject::longitude() const
{
    if (mGeo.isValid()) {
        return mGeo.longitude();
    }
    return -1;
}

QString ContactGrantleeGeoObject::toString() const
{
    QString result;
    if (mGeo.isValid()) {
        result = QStringLiteral("%1 %2, %3 %2").arg(mGeo.latitude()).arg(QChar(176)).arg(mGeo.longitude());
    }
    return result;
}

bool ContactGrantleeGeoObject::isValid() const
{
    return mGeo.isValid();
}
