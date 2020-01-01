/*
   Copyright (C) 2013-2020 Laurent Montel <montel@kde.org>

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

#include "sendlaterinfo.h"

#include <KConfigGroup>

using namespace SendLater;

SendLaterInfo::SendLaterInfo()
{
}

SendLaterInfo::SendLaterInfo(const KConfigGroup &config)
{
    readConfig(config);
}

SendLaterInfo::SendLaterInfo(const SendLaterInfo &info)
{
    mId = info.itemId();
    mRecurrenceEachValue = info.recurrenceEachValue();
    mRecurrenceUnit = info.recurrenceUnit();
    mRecurrence = info.isRecurrence();
    mSubject = info.subject();
    mTo = info.to();
    mDateTime = info.dateTime();
    mLastDateTimeSend = info.lastDateTimeSend();
}

SendLaterInfo::~SendLaterInfo()
{
}

bool SendLaterInfo::isValid() const
{
    return (mId != -1) && mDateTime.isValid();
}

bool SendLaterInfo::isRecurrence() const
{
    return mRecurrence;
}

void SendLaterInfo::setRecurrence(bool b)
{
    mRecurrence = b;
}

void SendLaterInfo::setRecurrenceUnit(SendLaterInfo::RecurrenceUnit unit)
{
    mRecurrenceUnit = unit;
}

SendLaterInfo::RecurrenceUnit SendLaterInfo::recurrenceUnit() const
{
    return mRecurrenceUnit;
}

void SendLaterInfo::setRecurrenceEachValue(int value)
{
    mRecurrenceEachValue = value;
}

int SendLaterInfo::recurrenceEachValue() const
{
    return mRecurrenceEachValue;
}

void SendLaterInfo::setItemId(Akonadi::Item::Id id)
{
    mId = id;
}

Akonadi::Item::Id SendLaterInfo::itemId() const
{
    return mId;
}

void SendLaterInfo::setDateTime(const QDateTime &time)
{
    mDateTime = time;
}

QDateTime SendLaterInfo::dateTime() const
{
    return mDateTime;
}

void SendLaterInfo::setLastDateTimeSend(const QDateTime &dateTime)
{
    mLastDateTimeSend = dateTime;
}

QDateTime SendLaterInfo::lastDateTimeSend() const
{
    return mLastDateTimeSend;
}

void SendLaterInfo::setSubject(const QString &subject)
{
    mSubject = subject;
}

QString SendLaterInfo::subject() const
{
    return mSubject;
}

void SendLaterInfo::setTo(const QString &to)
{
    mTo = to;
}

QString SendLaterInfo::to() const
{
    return mTo;
}

bool SendLaterInfo::operator ==(const SendLaterInfo &other) const
{
    return (itemId() == other.itemId())
           && (recurrenceUnit() == other.recurrenceUnit())
           && (recurrenceEachValue() == other.recurrenceEachValue())
           && (isRecurrence() == other.isRecurrence())
           && (dateTime() == other.dateTime())
           && (lastDateTimeSend() == other.lastDateTimeSend())
           && (subject() == other.subject())
           && (to() == other.to());
}

void SendLaterInfo::readConfig(const KConfigGroup &config)
{
    if (config.hasKey(QStringLiteral("lastDateTimeSend"))) {
        mLastDateTimeSend = QDateTime::fromString(config.readEntry("lastDateTimeSend"), Qt::ISODate);
    }
    mDateTime = config.readEntry("date", QDateTime::currentDateTime());
    mRecurrence = config.readEntry("recurrence", false);
    mRecurrenceEachValue = config.readEntry("recurrenceValue", 1);
    mRecurrenceUnit = static_cast<RecurrenceUnit>(config.readEntry("recurrenceUnit", static_cast<int>(Days)));
    mId = config.readEntry("itemId", -1);
    mSubject = config.readEntry("subject");
    mTo = config.readEntry("to");
}

void SendLaterInfo::writeConfig(KConfigGroup &config)
{
    if (mLastDateTimeSend.isValid()) {
        config.writeEntry("lastDateTimeSend", mLastDateTimeSend.toString(Qt::ISODate));
    }
    config.writeEntry("date", mDateTime);
    config.writeEntry("recurrence", mRecurrence);
    config.writeEntry("recurrenceValue", mRecurrenceEachValue);
    config.writeEntry("recurrenceUnit", static_cast<int>(mRecurrenceUnit));
    config.writeEntry("itemId", mId);
    config.writeEntry("subject", mSubject);
    config.writeEntry("to", mTo);
    config.sync();
}

QDebug operator<<(QDebug d, const SendLaterInfo &info)
{
    d << "mTo: " << info.to();
    d << "mSubject: " << info.subject();
    d << "mDateTime: " << info.dateTime().toString();
    d << "mLastDateTimeSend: " << info.lastDateTimeSend().toString();
    d << "mId: " << info.itemId();
    d << "mRecurrenceEachValue: " << info.recurrenceEachValue();
    d << "mRecurrenceUnit: " << info.recurrenceUnit();
    d << "mRecurrence: " << info.isRecurrence();
    return d;
}
