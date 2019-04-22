/*
   Copyright (C) 2019 Volker Krause <vkrause@kde.org>

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

#ifndef KADDRESSBOOKGRANTLEE_CONTACTGRANTLEEWRAPPER_H
#define KADDRESSBOOKGRANTLEE_CONTACTGRANTLEEWRAPPER_H

#include <KContacts/Addressee>

namespace KAddressBookGrantlee {

/**
 * Additional properties for the KContacts::Addressee Grantlee model.
 */
class ContactGrantleeWrapper : public KContacts::Addressee
{
    Q_GADGET
    // ### those probably should eventually become i18n calls in the template itself
    Q_PROPERTY(QString addressBookLabel READ addressBookLabel)
    Q_PROPERTY(QString anniversaryLabel READ anniversaryLabel)
    Q_PROPERTY(QString assistantLabel READ assistantLabel)
    Q_PROPERTY(QString birthdayLabel READ birthdayLabel)
    Q_PROPERTY(QString departmentLabel READ departmentLabel)
    Q_PROPERTY(QString noteLabel READ noteLabel)
    Q_PROPERTY(QString managerLabel READ managerLabel)
    Q_PROPERTY(QString officeLabel READ officeLabel)
    Q_PROPERTY(QString professionLabel READ professionLabel)
    Q_PROPERTY(QString spouseLabel READ spouseLabel)

    Q_PROPERTY(QString addressBookName READ addressBookName)
    Q_PROPERTY(int age READ age)
    Q_PROPERTY(QString cryptoPreference READ cryptoPreference)
    Q_PROPERTY(QString signaturePreference READ signaturePreference)

    // ### this shouldn't be returning assembled HTML, that's a job for Grantlee
    Q_PROPERTY(QString photo READ photoImgElement)
    Q_PROPERTY(QString logo READ logoImgElement)

    // ### those two would be unneccessary if we had a proper way for formatting dates in Grantlee
    Q_PROPERTY(QString formattedBirthday READ formattedBirthday)
    Q_PROPERTY(QString formattedAnniversary READ formattedAnniversary)

    // ### this is temporary, until KContacts::Impp takes over this part
    Q_PROPERTY(QVariantList imAddresses READ imAddresses)

public:
    ContactGrantleeWrapper();
    ContactGrantleeWrapper(const KContacts::Addressee &addr);

private:

    QString addressBookLabel() const;
    QString anniversaryLabel() const;
    QString assistantLabel() const;
    QString managerLabel() const;
    QString officeLabel() const;
    QString professionLabel() const;
    QString spouseLabel() const;

    QString addressBookName() const;
    int age() const;
    QString cryptoPreference() const;
    QString signaturePreference() const;

    QString photoImgElement() const;
    QString logoImgElement() const;

    QString formattedBirthday() const;
    QString formattedAnniversary() const;

    QVariantList imAddresses() const;
};

}

Q_DECLARE_METATYPE(KAddressBookGrantlee::ContactGrantleeWrapper)

#endif // KADDRESSBOOKGRANTLEE_CONTACTGRANTLEEWRAPPER_H
