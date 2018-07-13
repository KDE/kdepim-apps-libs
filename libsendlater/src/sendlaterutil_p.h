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

#ifndef SENDLATERUTIL_P_H
#define SENDLATERUTIL_P_H

#include "sendlater_export.h"
#include <KSharedConfig>

namespace SendLater {
class SendLaterInfo;
namespace SendLaterUtil {
Q_REQUIRED_RESULT QDateTime updateRecurence(SendLater::SendLaterInfo *info, QDateTime dateTime);
}
}
#endif // SENDLATERUTIL_P_H
