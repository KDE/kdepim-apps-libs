/*
  Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>
  Copyright (c) 2015 Laurent Montel <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
*/

#ifndef KADDRESSBOOKIMPORTEXPORTCONTACTEXPORTSELECTIONDIALOG_H
#define KADDRESSBOOKIMPORTEXPORTCONTACTEXPORTSELECTIONDIALOG_H

#include "kaddressbook_importexport_export.h"
#include <KContacts/Addressee>
#include <QDialog>
#include <KAddressBookImportExport/KAddressBookImportExportContactList>
#include <KAddressBookImportExport/KAddressBookExportSelectionWidget>
#include <AkonadiCore/Item>
class QItemSelectionModel;
class KAddressBookContactSelectionWidget;
namespace Akonadi
{
class Collection;
}

/**
 * @short A dialog to select a group of contacts.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
namespace KAddressBookImportExport
{
class KAddressBookExportSelectionWidget;
class KAddressBookContactSelectionWidget;
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
    explicit KAddressBookContactSelectionDialog(QItemSelectionModel *selectionModel, bool allowToSelectTypeToExport, QWidget *parent = Q_NULLPTR);

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
    KAddressBookImportExport::KAddressBookImportExportContactList selectedContacts() const;

    KAddressBookExportSelectionWidget::ExportFields exportType() const;
    void setAddGroupContact(bool addGroupContact);

    Akonadi::Item::List selectedItems() const;
private:
    KAddressBookContactSelectionWidget *mSelectionWidget;
    KAddressBookExportSelectionWidget *mVCardExport;
};
}
#endif