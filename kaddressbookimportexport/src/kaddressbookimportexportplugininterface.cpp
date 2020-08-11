/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kaddressbookimportexportplugininterface.h"

using namespace KAddressBookImportExport;

KAddressBookImportExportPluginInterface::KAddressBookImportExportPluginInterface(QObject *parent)
    : PimCommon::AbstractGenericPluginInterface(parent)
    , mImportExportAction(Import)
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

KAddressBookImportExportPluginInterface::ImportExportAction KAddressBookImportExportPluginInterface::importExportAction() const
{
    return mImportExportAction;
}

void KAddressBookImportExportPluginInterface::setImportExportAction(ImportExportAction importExportAction)
{
    mImportExportAction = importExportAction;
}

Akonadi::Collection KAddressBookImportExportPluginInterface::defaultCollection() const
{
    return mDefaultCollection;
}

void KAddressBookImportExportPluginInterface::setDefaultCollection(const Akonadi::Collection &defaultCollection)
{
    mDefaultCollection = defaultCollection;
}

QItemSelectionModel *KAddressBookImportExportPluginInterface::itemSelectionModel() const
{
    return mItemSelectionModel;
}

void KAddressBookImportExportPluginInterface::setItemSelectionModel(QItemSelectionModel *itemSelectionModel)
{
    mItemSelectionModel = itemSelectionModel;
}

bool KAddressBookImportExportPluginInterface::canImportFileType(const QUrl &url)
{
    Q_UNUSED(url);
    return false;
}

void KAddressBookImportExportPluginInterface::importFile(const QUrl &url)
{
    Q_UNUSED(url);
}

bool KAddressBookImportExportPluginInterface::canImportData() const
{
    return false;
}

void KAddressBookImportExportPluginInterface::importData(const QByteArray &data)
{
    Q_UNUSED(data);
}
