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

#ifndef SENDLATERINFO_H
#define SENDLATERINFO_H

#include <item.h>
#include <QDateTime>
#include "sendlater_export.h"

class KConfigGroup;

namespace SendLater {

/** Send later information. */
class SENDLATER_EXPORT SendLaterInfo
{
public:
    explicit SendLaterInfo();
    explicit SendLaterInfo(const KConfigGroup &config);
    SendLaterInfo(const SendLater::SendLaterInfo &info);
    ~SendLaterInfo();

    enum RecurrenceUnit {
        Days = 0,
        Weeks,
        Months,
        Years
    };

    Q_REQUIRED_RESULT bool isValid() const;

    void setItemId(Akonadi::Item::Id id);
    Q_REQUIRED_RESULT Akonadi::Item::Id itemId() const;

    void setRecurrenceUnit(RecurrenceUnit unit);
    Q_REQUIRED_RESULT RecurrenceUnit recurrenceUnit() const;

    void setRecurrenceEachValue(int value);
    Q_REQUIRED_RESULT int recurrenceEachValue() const;

    Q_REQUIRED_RESULT bool isRecurrence() const;
    void setRecurrence(bool b);

    void setDateTime(const QDateTime &time);
    Q_REQUIRED_RESULT QDateTime dateTime() const;

    void readConfig(const KConfigGroup &config);
    void writeConfig(KConfigGroup &config);

    void setLastDateTimeSend(const QDateTime &date);
    Q_REQUIRED_RESULT QDateTime lastDateTimeSend() const;

    void setSubject(const QString &subject);
    Q_REQUIRED_RESULT QString subject() const;

    void setTo(const QString &to);
    Q_REQUIRED_RESULT QString to() const;

    bool operator ==(const SendLaterInfo &other) const;

private:
    QString mTo;
    QString mSubject;
    QDateTime mDateTime;
    QDateTime mLastDateTimeSend;
    Akonadi::Item::Id mId = -1;
    int mRecurrenceEachValue = 1;
    RecurrenceUnit mRecurrenceUnit = Days;
    bool mRecurrence = false;
};
}

#endif // SENDLATERINFO_H
