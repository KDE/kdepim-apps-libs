/*
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>
  SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KAddressBookCONTACTSELECTIONWIDGET_H
#define KAddressBookCONTACTSELECTIONWIDGET_H

#include <KContacts/Addressee>
#include <AkonadiCore/Item>
#include "kaddressbook_importexport_export.h"
#include "KAddressBookImportExport/KAddressBookImportExportContactList"

#include <QWidget>

class QCheckBox;
class QItemSelectionModel;
class QLabel;
class QRadioButton;

namespace Akonadi {
class Collection;
class CollectionComboBox;
}

namespace KAddressBookImportExport {
/**
 * @short A widget to select a group of contacts.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class KADDRESSBOOK_IMPORTEXPORT_EXPORT KAddressBookContactSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Creates a new contact selection widget.
     *
     * @param selectionModel The model that contains the currently selected contacts.
     * @param parent The parent widget.
     */
    explicit KAddressBookContactSelectionWidget(QItemSelectionModel *selectionModel, QWidget *parent = nullptr);

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

    void setAddGroupContact(bool addGroupContact);
    Q_REQUIRED_RESULT Akonadi::Item::List selectedItems() const;
private:
    void initGui();

    Q_REQUIRED_RESULT KAddressBookImportExport::KAddressBookImportExportContactList collectAllContacts() const;
    Q_REQUIRED_RESULT KAddressBookImportExport::KAddressBookImportExportContactList collectSelectedContacts() const;
    Q_REQUIRED_RESULT KAddressBookImportExport::KAddressBookImportExportContactList collectAddressBookContacts() const;

    Q_REQUIRED_RESULT Akonadi::Item::List collectAllItems() const;
    Q_REQUIRED_RESULT Akonadi::Item::List collectSelectedItems() const;
    Q_REQUIRED_RESULT Akonadi::Item::List collectAddressBookItems() const;

    QItemSelectionModel *const mSelectionModel;

    QLabel *mMessageLabel = nullptr;
    QRadioButton *mAllContactsButton = nullptr;
    QRadioButton *mSelectedContactsButton = nullptr;
    QRadioButton *mAddressBookContactsButton = nullptr;
    Akonadi::CollectionComboBox *mAddressBookSelection = nullptr;
    QCheckBox *mAddressBookSelectionRecursive = nullptr;
    bool mAddContactGroup = false;
};
}
#endif
