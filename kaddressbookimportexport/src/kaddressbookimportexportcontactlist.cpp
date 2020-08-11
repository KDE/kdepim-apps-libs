/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kaddressbookimportexportcontactlist.h"

using namespace KAddressBookImportExport;

KAddressBookImportExportContactList::KAddressBookImportExportContactList()
{
}

bool KAddressBookImportExportContactList::isEmpty() const
{
    return mAddressList.isEmpty() && mContactGroupList.isEmpty();
}

int KAddressBookImportExportContactList::count() const
{
    return mAddressList.count() + mContactGroupList.count();
}

void KAddressBookImportExportContactList::clear()
{
    mAddressList.clear();
    mContactGroupList.clear();
}

void KAddressBookImportExportContactList::append(const KContacts::Addressee &addr)
{
    mAddressList.append(addr);
}

void KAddressBookImportExportContactList::append(const KContacts::ContactGroup &group)
{
    mContactGroupList.append(group);
}

KContacts::ContactGroup::List KAddressBookImportExportContactList::contactGroupList() const
{
    return mContactGroupList;
}

void KAddressBookImportExportContactList::setContactGroupList(const KContacts::ContactGroup::List &value)
{
    mContactGroupList = value;
}

KContacts::Addressee::List KAddressBookImportExportContactList::addressList() const
{
    return mAddressList;
}

void KAddressBookImportExportContactList::setAddressList(const KContacts::Addressee::List &value)
{
    mAddressList = value;
}
