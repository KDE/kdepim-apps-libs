/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

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


#include "composerwebengine.h"
#include <QStandardPaths>
#include <QFile>
#include <QFileInfo>
#include <QWebEnginePage>
#include <KMessageBox>
#include <KLocalizedString>
using namespace ComposerEditorWebEngine;

ComposerWebEngine::ComposerWebEngine(QWidget *parent)
    : QWebEngineView(parent)
{
    QFile file(initialHtml());
    //qCDebug(COMPOSEREDITORNG_LOG) << file.fileName();

    if (!file.open(QIODevice::ReadOnly)) {
        KMessageBox::error(this, i18n("Cannot open template file %1.", QFileInfo(file).absoluteFilePath()), i18n("composer editor"));
    } else {
        setContent(file.readAll());    //, "application/xhtml+xml" );
    }

    page()->runJavaScript(QStringLiteral("document.documentElement.contentEditable = true"));
}

ComposerWebEngine::~ComposerWebEngine()
{

}

QString ComposerWebEngine::initialHtml()
{
    return QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("composereditorwebengine/composereditorinitialhtml"));
}
