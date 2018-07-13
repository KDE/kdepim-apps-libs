/*
  This file is part of KAddressBook.

  Copyright (c) 2010 Tobias Koenig <tokoe@kde.org>

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

#ifndef GRANTLEECONTACTFORMATTER_H
#define GRANTLEECONTACTFORMATTER_H

#include <Akonadi/Contact/AbstractContactFormatter>
#include "kaddressbook_grantlee_export.h"

namespace GrantleeTheme {
class Theme;
}

namespace KAddressBookGrantlee {
/**
 * @short A class that formats a contact as HTML code.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class KADDRESSBOOK_GRANTLEE_EXPORT GrantleeContactFormatter : public Akonadi::AbstractContactFormatter
{
public:
    /**
     * Creates a new grantlee contact formatter.
     */
    explicit GrantleeContactFormatter();

    /**
     * Destroys the grantlee contact formatter.
     */
    ~GrantleeContactFormatter() override;

    void setAbsoluteThemePath(const QString &path);

    void setGrantleeTheme(const GrantleeTheme::Theme &theme);

    void setForceDisableQRCode(bool b);
    Q_REQUIRED_RESULT bool forceDisableQRCode() const;

    /**
     * Returns the contact formatted as HTML
     */
    Q_REQUIRED_RESULT QString toHtml(HtmlForm form = SelfcontainedForm) const override;

    void setShowQRCode(bool b);
private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

#endif
