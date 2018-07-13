/*
   Copyright (C) 2013-2018 Montel Laurent <montel@kde.org>

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

#ifndef CONTACTGRANTLEEPRINTIMOBJECT_H
#define CONTACTGRANTLEEPRINTIMOBJECT_H
#include <QObject>
namespace KAddressBookGrantlee {
class ContactGrantleeImObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type)
    Q_PROPERTY(QString address READ address)

public:
    explicit ContactGrantleeImObject(const QString &type, const QString &address, QObject *parent = nullptr);
    ~ContactGrantleeImObject();

    Q_REQUIRED_RESULT QString type() const;
    Q_REQUIRED_RESULT QString address() const;

private:
    QString mType;
    QString mAddress;
};
}
#endif // CONTACTGRANTLEEPRINTIMOBJECT_H
