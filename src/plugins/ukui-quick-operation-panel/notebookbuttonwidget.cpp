/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/
#include "notebookbuttonwidget.h"
#include <QDebug>

notebookButtonWidget::notebookButtonWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void notebookButtonWidget::initMemberVariables()
{
    m_pButtonWidget = new QWidget();
    m_pButtonWidget->setFixedSize(56, 56);

    m_pLabelFotmatText = new LabelFotmatText;

    m_pNoteButton = new ShortcutButton();
    m_pNoteButton->m_bStatusButton = false;
    connect(m_pNoteButton, &ShortcutButton::clicked, this, &notebookButtonWidget::NoteButtonClickSlots);
    m_pNoteButton->setIcon(QIcon::fromTheme(KYLIN_BLUETOOTH_NORMAL_NAME, QIcon(KYLIN_BLUETOOTH_NORMAL_PATH)));
    m_pNoteButton->setFixedSize(56, 56);
    m_pNoteButton->setIconSize(QSize(24, 24));

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pNoteLabel  = new QLabel();
    m_pNoteLabel->setFixedWidth(60);
    m_pNoteLabel->setText(m_pLabelFotmatText->SetFormatBody(QObject::tr("NoteBook"), m_pNoteLabel));
    m_pNoteLabel->setAlignment(Qt::AlignHCenter);

    if (m_pLabelFotmatText->m_bTooltips) {
        this->setToolTip(QObject::tr("NoteBook"));
    }

    m_pVboxButtonLayout = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout->setSpacing(0);

    m_pVboxLayout       = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pNoteButton->setStyle(m_pStyleNormal);

    this->setFixedSize(63, 82);
    this->setContentsMargins(0, 0, 0, 0);
}

void notebookButtonWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pNoteButton);
    m_pButtonWidget->setLayout(m_pVboxButtonLayout);

    m_pVboxLayout->addWidget(m_pButtonWidget, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(5, 4));
    m_pVboxLayout->addWidget(m_pNoteLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

void notebookButtonWidget::NoteButtonClickSlots()
{
    qDebug()<<"便签本......";
    QProcess p(0);
    p.startDetached("ukui-notebook");
    p.waitForStarted();
    return;
}
