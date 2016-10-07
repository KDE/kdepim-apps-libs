/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "kaddressbookimportexportplugininterface.h"

using namespace KAddressBookImportExport;

KAddressBookImportExportPluginInterface::KAddressBookImportExportPluginInterface(QObject *parent)
    : PimCommon::AbstractGenericPluginInterface(parent)
{

}

KAddressBookImportExportPluginInterface::~KAddressBookImportExportPluginInterface()
{

}

QList<QAction *> KAddressBookImportExportPluginInterface::importActions() const
{
    return mImportActions;
}

void KAddressBookImportExportPluginInterface::setImportActions(const QList<QAction *> &importAction)
{
    mImportActions = importAction;
}

QList<QAction *> KAddressBookImportExportPluginInterface::exportActions() const
{
    return mExportActions;
}

void KAddressBookImportExportPluginInterface::setExportActions(const QList<QAction *> &exportAction)
{
    mExportActions = exportAction;
}
