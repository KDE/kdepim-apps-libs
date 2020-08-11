/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KADDRESSBOOKIMPORTEXPORTPLUGINMANAGER_H
#define KADDRESSBOOKIMPORTEXPORTPLUGINMANAGER_H

#include <QObject>
#include <PimCommon/PluginUtil>
#include "kaddressbook_importexport_export.h"

namespace KAddressBookImportExport {
class KAddressBookImportExportPlugin;
class KAddressBookImportExportPrivate;

/** Contact import/export plugin manager. */
class KADDRESSBOOK_IMPORTEXPORT_EXPORT KAddressBookImportExportPluginManager : public QObject
{
    Q_OBJECT
public:
    explicit KAddressBookImportExportPluginManager(QObject *parent = nullptr);
    ~KAddressBookImportExportPluginManager();
    static KAddressBookImportExportPluginManager *self();

    Q_REQUIRED_RESULT QVector<KAddressBookImportExportPlugin *> pluginsList() const;

    Q_REQUIRED_RESULT QVector<PimCommon::PluginUtilData> pluginsDataList() const;

    Q_REQUIRED_RESULT QString configGroupName() const;
    Q_REQUIRED_RESULT QString configPrefixSettingKey() const;
    KAddressBookImportExportPlugin *pluginFromIdentifier(const QString &id);
private:
    KAddressBookImportExportPrivate *const d;
};
}

#endif // KADDRESSBOOKIMPORTEXPORTPLUGINMANAGER_H
