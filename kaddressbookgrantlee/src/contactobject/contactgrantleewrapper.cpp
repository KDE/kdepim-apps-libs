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

#include "contactgrantleewrapper.h"

#include <Libkleo/Enum>

#include <KLocalizedString>

#include <QBuffer>
#include <QImage>
#include <QLocale>

using namespace KAddressBookGrantlee;

static_assert(sizeof(KContacts::Addressee) == sizeof(KAddressBookGrantlee::ContactGrantleeWrapper), "Grantlee wrapper must not have member variables to prevent sliciing issues");

ContactGrantleeWrapper::ContactGrantleeWrapper() = default;

ContactGrantleeWrapper::ContactGrantleeWrapper(const KContacts::Addressee& addr)
    : KContacts::Addressee(addr)
{
}

QString ContactGrantleeWrapper::addressBookLabel() const
{
    return i18n("Address Book");
}

QString ContactGrantleeWrapper::anniversaryLabel() const
{
    return i18n("Anniversary");
}

QString ContactGrantleeWrapper::assistantLabel() const
{
    return i18n("Assistant's Name");
}

QString ContactGrantleeWrapper::managerLabel() const
{
    return i18n("Manager's Name");
}

QString ContactGrantleeWrapper::officeLabel() const
{
    return i18n("Office");
}

QString ContactGrantleeWrapper::professionLabel() const
{
    return i18n("Profession");
}

QString ContactGrantleeWrapper::spouseLabel() const
{
    return i18n("Partner's Name");
}

QString ContactGrantleeWrapper::addressBookName() const
{
    return custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("AddressBook"));
}

int ContactGrantleeWrapper::age() const
{
    QDate now = QDate::currentDate();
    int age = now.year() - birthday().date().year();
    if (birthday().date() > now.addYears(-age)) {
        age--;
    }
    return age;
}

QString ContactGrantleeWrapper::cryptoPreference() const
{
    return Kleo::encryptionPreferenceToLabel(Kleo::stringToEncryptionPreference(custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOENCRYPTPREF"))));
}

QString ContactGrantleeWrapper::signaturePreference() const
{
    return Kleo::signingPreferenceToLabel(Kleo::stringToSigningPreference(custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOSIGNPREF"))));
}

static QString imgToDataUrl(const QImage &image)
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return QStringLiteral("data:image/%1;base64,%2").arg(QStringLiteral("PNG"), QString::fromLatin1(ba.toBase64()));
}

QString ContactGrantleeWrapper::logoImgElement() const
{
    if (logo().isEmpty()) {
        return {};
    }
    return QStringLiteral("<img src=\"%1\" width=\"%2\" height=\"%3\"> &nbsp;").arg(imgToDataUrl(logo().data()), QString::number(60), QString::number(60));
}

QString ContactGrantleeWrapper::photoImgElement() const
{
    if (photo().isEmpty()) {
        return {};
    }
    return QStringLiteral("<img src=\"%1\" width=\"%2\" height=\"%3\"> &nbsp;").arg(imgToDataUrl(photo().data()), QString::number(60), QString::number(60));
}

QString ContactGrantleeWrapper::formattedBirthday() const
{
    return QLocale().toString(birthday().date());
}

QString ContactGrantleeWrapper::formattedAnniversary() const
{
    return QLocale().toString(anniversary());
}

#include "moc_contactgrantleewrapper.cpp"
