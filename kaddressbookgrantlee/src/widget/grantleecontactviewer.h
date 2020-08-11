/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRANTLEECONTACTVIEWER_H
#define GRANTLEECONTACTVIEWER_H

#include "kaddressbook_grantlee_export.h"
#include <Akonadi/Contact/ContactViewer>

namespace KAddressBookGrantlee {
class GrantleeContactFormatter;

/** Grantlee-based contact viewer. */
class KADDRESSBOOK_GRANTLEE_EXPORT GrantleeContactViewer : public Akonadi::ContactViewer
{
    Q_OBJECT
public:
    explicit GrantleeContactViewer(QWidget *parent = nullptr);
    ~GrantleeContactViewer();

    void setForceDisableQRCode(bool b);

private:
    QString kaddressBookAbsoluteThemePath();
    KAddressBookGrantlee::GrantleeContactFormatter *mFormatter = nullptr;
};
}

#endif // GRANTLEECONTACTVIEWER_H
