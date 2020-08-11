/*
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef IMPORTEXPORT_KADDRESSBOOKCONTACTSELECTIONDIALOG_H
#define IMPORTEXPORT_KADDRESSBOOKCONTACTSELECTIONDIALOG_H

#include "kaddressbook_importexport_export.h"
#include <KContacts/Addressee>
#include <QDialog>
#include <KAddressBookImportExport/KAddressBookImportExportContactList>
#include <KAddressBookImportExport/KAddressBookExportSelectionWidget>
#include <AkonadiCore/Item>
class QItemSelectionModel;
class KAddressBookContactSelectionWidget;
namespace Akonadi {
class Collection;
}

namespace KAddressBookImportExport {
class KAddressBookExportSelectionWidget;
class KAddressBookContactSelectionWidget;

/**
 * @short A dialog to select a group of contacts.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class KADDRESSBOOK_IMPORTEXPORT_EXPORT KAddressBookContactSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Creates a new contact selection dialog.
     *
     * @param selectionModel The model that contains the currently selected contacts.
     * @param parent The parent widget.
     */
    explicit KAddressBookContactSelectionDialog(QItemSelectionModel *selectionModel, bool allowToSelectTypeToExport, QWidget *parent = nullptr);

    /**
     * Sets the @p message text.
     */
    void setMessageText(const QString &message);

    /**
     * Sets the default addressbook.
     */
    void setDefaultAddressBook(const Akonadi::Collection &addressBook);

    /**
     * Returns the list of selected contacts.
     */
    Q_REQUIRED_RESULT KAddressBookImportExport::KAddressBookImportExportContactList selectedContacts() const;

    Q_REQUIRED_RESULT KAddressBookExportSelectionWidget::ExportFields exportType() const;
    void setAddGroupContact(bool addGroupContact);

    Q_REQUIRED_RESULT Akonadi::Item::List selectedItems() const;
private:
    KAddressBookContactSelectionWidget *mSelectionWidget = nullptr;
    KAddressBookExportSelectionWidget *mVCardExport = nullptr;
};
}
#endif
