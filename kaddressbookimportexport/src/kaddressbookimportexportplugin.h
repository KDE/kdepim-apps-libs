/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KADDRESSBOOKIMPORTEXPORTPLUGIN_H
#define KADDRESSBOOKIMPORTEXPORTPLUGIN_H

#include <PimCommon/AbstractGenericPlugin>
#include "kaddressbook_importexport_export.h"
namespace KAddressBookImportExport {

/** Import/export plugin. */
class KADDRESSBOOK_IMPORTEXPORT_EXPORT KAddressBookImportExportPlugin : public PimCommon::AbstractGenericPlugin
{
    Q_OBJECT
public:
    explicit KAddressBookImportExportPlugin(QObject *parent = nullptr);
    ~KAddressBookImportExportPlugin();
};
}
#endif // KADDRESSBOOKIMPORTEXPORTPLUGIN_H
