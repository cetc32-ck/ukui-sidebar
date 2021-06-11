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
#include "screenshotwidget.h"
#include <QDebug>
#include <QMetaType>

screenshotWidget::screenshotWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

screenshotWidget::~screenshotWidget()
{

}

void screenshotWidget::initMemberVariables()
{
    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pLabelFotmatText = new LabelFotmatText();

    m_pscreenshotButton = new ShortcutButton();
    m_pscreenshotButton->m_bStatusButton = false;
    m_pscreenshotButton->setIcon(QIcon::fromTheme(KYLIN_SCREENSHOT_NORMAL_NAME, QIcon(KYLIN_SCREENSHOT_NORMAL_PATH)));
    m_pscreenshotButton->setFixedSize(56, 56);
    m_pscreenshotButton->setIconSize(QSize(24, 24));
    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pscreenshotButton->setStyle(m_pStyleNormal);
    connect(m_pscreenshotButton, &ShortcutButton::clicked, this, &screenshotWidget::sreenShotButtonClickedSlots);

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pscreenshotlabel = new QLabel();
    m_pscreenshotlabel->setFixedWidth(60);
    m_pscreenshotlabel->setText(m_pLabelFotmatText->SetFormatBody(QObject::tr("Screenshots"), m_pscreenshotlabel));
    m_pscreenshotlabel->setAlignment(Qt::AlignHCenter);

    if (m_pLabelFotmatText->m_bTooltips) {
        this->setToolTip(QObject::tr("Screenshots"));
    }

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(63, 82);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void screenshotWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pscreenshotButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(15, 4));
    m_pVboxLayout->addWidget(m_pscreenshotlabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

void screenshotWidget::sreenShotButtonClickedSlots()
{
    qDebug()<<"截图......";
    QProcess p(0);
    p.startDetached("kylin-screenshot gui");
    p.waitForStarted();
    return;
}

//--->zyj
int screenshot::typeId = qRegisterMetaType<screenshot*>();
screenshot::screenshot(QObject *parent): ShortcutInterface(parent)
{
}

bool screenshot::action() const
{
    qDebug()<<"截图快捷按钮";
    QProcess p(0);
    p.startDetached("kylin-screenshot gui");
    p.waitForStarted();
    return true;
}



//---<
