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

#include "composerwebenginewidget.h"
#include "composerwebengine.h"
#include "widgets/findreplacebar.h"

#include <QVBoxLayout>

using namespace ComposerEditorWebEngine;

class ComposerEditorWebEngine::ComposerWebEngineWidgetPrivate
{
public:
    ComposerWebEngineWidgetPrivate(ComposerWebEngineWidget *qq)
        : webEngine(Q_NULLPTR),
          q(qq)
    {

    }
    void initialize();
    FindReplaceBar *findReplace;
    ComposerWebEngine *webEngine;
    ComposerWebEngineWidget *q;
};

void ComposerWebEngineWidgetPrivate::initialize()
{
    QVBoxLayout *vbox = new QVBoxLayout(q);
    webEngine = new ComposerWebEngine(q);
    vbox->addWidget(webEngine);
    findReplace = new FindReplaceBar(webEngine);
    vbox->addWidget(findReplace);
    //TODO add texttospeech ?
}

ComposerWebEngineWidget::ComposerWebEngineWidget(QWidget *parent)
    : QWidget(parent),
      d(new ComposerEditorWebEngine::ComposerWebEngineWidgetPrivate(this))
{

}

ComposerWebEngineWidget::~ComposerWebEngineWidget()
{
    delete d;
}

