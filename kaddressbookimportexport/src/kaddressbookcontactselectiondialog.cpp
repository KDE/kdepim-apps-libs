/*
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kaddressbookcontactselectiondialog.h"
#include "kaddressbookcontactselectionwidget.h"

#include <QVBoxLayout>
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
using namespace KAddressBookImportExport;

KAddressBookContactSelectionDialog::KAddressBookContactSelectionDialog(QItemSelectionModel *selectionModel, bool allowToSelectTypeToExport, QWidget *parent)
    : QDialog(parent)
    , mVCardExport(nullptr)
{
    setWindowTitle(i18nc("@title:window", "Select Contacts"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mSelectionWidget = new KAddressBookContactSelectionWidget(selectionModel, this);
    if (allowToSelectTypeToExport) {
        mainLayout->addWidget(mSelectionWidget);
        mVCardExport = new KAddressBookExportSelectionWidget(this);
        mainLayout->addWidget(mVCardExport);
    } else {
        mainLayout->addWidget(mSelectionWidget);
    }

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &KAddressBookContactSelectionDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &KAddressBookContactSelectionDialog::reject);
    mainLayout->addWidget(buttonBox);
}

void KAddressBookContactSelectionDialog::setMessageText(const QString &message)
{
    mSelectionWidget->setMessageText(message);
}

void KAddressBookContactSelectionDialog::setDefaultAddressBook(const Akonadi::Collection &addressBook)
{
    mSelectionWidget->setDefaultAddressBook(addressBook);
}

Akonadi::Item::List KAddressBookContactSelectionDialog::selectedItems() const
{
    return mSelectionWidget->selectedItems();
}

KAddressBookImportExport::KAddressBookImportExportContactList KAddressBookContactSelectionDialog::selectedContacts() const
{
    return mSelectionWidget->selectedContacts();
}

KAddressBookExportSelectionWidget::ExportFields KAddressBookContactSelectionDialog::exportType() const
{
    if (mVCardExport) {
        return mVCardExport->exportType();
    } else {
        return KAddressBookExportSelectionWidget::None;
    }
}

void KAddressBookContactSelectionDialog::setAddGroupContact(bool addGroupContact)
{
    mSelectionWidget->setAddGroupContact(addGroupContact);
}
