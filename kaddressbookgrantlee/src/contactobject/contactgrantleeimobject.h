/*
  Copyright (c) 2013-2016 Montel Laurent <montel@kde.org>

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

#ifndef CONTACTGRANTLEEPRINTIMOBJECT_H
#define CONTACTGRANTLEEPRINTIMOBJECT_H
#include <QObject>
namespace KAddressBookGrantlee
{
class ContactGrantleeImObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type)
    Q_PROPERTY(QString address READ address)

public:
    explicit ContactGrantleeImObject(const QString &type, const QString &address, QObject *parent = Q_NULLPTR);
    ~ContactGrantleeImObject();

    QString type() const;
    QString address() const;

private:
    QString mType;
    QString mAddress;
};
}
#endif // CONTACTGRANTLEEPRINTIMOBJECT_H