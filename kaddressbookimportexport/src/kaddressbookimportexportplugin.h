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


#ifndef KADDRESSBOOKIMPORTEXPORTPLUGIN_H
#define KADDRESSBOOKIMPORTEXPORTPLUGIN_H

#include <PimCommon/AbstractGenericPlugin>
#include "kaddressbook_importexport_export.h"
#include <QList>
class QAction;
namespace KAddressBookImportExport
{
class KADDRESSBOOK_IMPORTEXPORT_EXPORT KAddressBookImportExportPlugin : public PimCommon::AbstractGenericPlugin
{
    Q_OBJECT
public:
    explicit KAddressBookImportExportPlugin(QObject *parent = Q_NULLPTR);
    ~KAddressBookImportExportPlugin();
    QList<QAction *> importActions() const;
    void setImportActions(const QList<QAction *> &importAction);

    QList<QAction *> exportActions() const;
    void setExportActions(const QList<QAction *> &exportAction);

protected:
    QList<QAction *> mImportActions;
    QList<QAction *> mExportActions;
};
}
#endif // KADDRESSBOOKIMPORTEXPORTPLUGIN_H
