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

#ifndef KADDRESSBOOKIMPORTEXPORTPLUGININTERFACE_H
#define KADDRESSBOOKIMPORTEXPORTPLUGININTERFACE_H

#include "kaddressbook_importexport_export.h"
#include <PimCommon/AbstractGenericPluginInterface>
#include <QList>
#include <AkonadiCore/Collection>
class QItemSelectionModel;
namespace KAddressBookImportExport {
class KADDRESSBOOK_IMPORTEXPORT_EXPORT KAddressBookImportExportPluginInterface : public PimCommon::AbstractGenericPluginInterface
{
    Q_OBJECT
public:
    explicit KAddressBookImportExportPluginInterface(QObject *parent = nullptr);
    ~KAddressBookImportExportPluginInterface();

    enum ImportExportAction {
        Import = 0,
        Export = 1
    };

    QList<QAction *> importActions() const;
    void setImportActions(const QList<QAction *> &importAction);

    QList<QAction *> exportActions() const;
    void setExportActions(const QList<QAction *> &exportAction);

    ImportExportAction importExportAction() const;
    void setImportExportAction(const ImportExportAction &importExportAction);

    Akonadi::Collection defaultCollection() const;
    void setDefaultCollection(const Akonadi::Collection &defaultCollection);

    void setSelectionModel(QItemSelectionModel *model);

    QItemSelectionModel *itemSelectionModel() const;
    void setItemSelectionModel(QItemSelectionModel *itemSelectionModel);

    virtual bool canImportFileType(const QUrl &url);
    virtual void importFile(const QUrl &url);

    virtual bool canImportData() const;
    virtual void importData(const QByteArray &data);

protected:
    QList<QAction *> mImportActions;
    QList<QAction *> mExportActions;
    ImportExportAction mImportExportAction;
    Akonadi::Collection mDefaultCollection;
    QItemSelectionModel *mItemSelectionModel = nullptr;
};
}
#endif // KADDRESSBOOKIMPORTEXPORTPLUGININTERFACE_H
