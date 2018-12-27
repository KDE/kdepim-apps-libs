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

#ifndef SENDLATERTIMEDATEWIDGET_H
#define SENDLATERTIMEDATEWIDGET_H

#include <QWidget>
#include <QDateTime>

class KTimeComboBox;
class KDateComboBox;

namespace SendLater {
class SendLaterTimeDateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SendLaterTimeDateWidget(QWidget *parent = nullptr);
    ~SendLaterTimeDateWidget();

    void setDateTime(const QDateTime &);
    Q_REQUIRED_RESULT QDateTime dateTime() const;

Q_SIGNALS:
    void dateTimeChanged(const QDateTime &);
    void dateChanged(const QString &);
private:
    void slotDateTimeChanged();
    KTimeComboBox *mTimeComboBox = nullptr;
    KDateComboBox *mDateComboBox = nullptr;
};
}

#endif // SENDLATERTIMEDATEWIDGET_H
