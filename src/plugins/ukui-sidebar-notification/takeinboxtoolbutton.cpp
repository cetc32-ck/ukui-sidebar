/*
* Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
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

#include "takeinboxtoolbutton.h"
#include <QToolTip>
#include <QMouseEvent>
#include <QDebug>

TakeInBoxToolButton::TakeInBoxToolButton()
{
    m_bEnterTakeInBox = false;
    setAutoRaise(true);
    setProperty("isWindowButton",0x1);
}

void TakeInBoxToolButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setIconSize(QSize(24,24));
    //设置边框, 边框色, 背景色, 字体色, 字号
    if (false == m_bEnterTakeInBox) {
          setIcon(QIcon(":/images/box-24-hover.svg"));
          this->setToolTip((tr("Enter unimportant news")));

    } else {
        setIcon(QIcon(":/images/exitbox-24-hover.svg"));
        this->setToolTip((tr("Quit unimportant news")));
    }
    return;
}

void TakeInBoxToolButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    if (false == m_bEnterTakeInBox) {
        setIcon(QIcon(":/images/box-24.svg"));
    } else {
        setIcon(QIcon(":/images/exitbox-24.svg"));
    }

    return;
}

//鼠标点击事件
void TakeInBoxToolButton::mousePressEvent(QMouseEvent *event)
{

    if (event->buttons() == Qt::LeftButton) {
        setIconSize(QSize(20,20));
        if (false == m_bEnterTakeInBox) {
            setIcon(QIcon(":/images/box-24-hover.svg"));
        } else {
            setIcon(QIcon(":/images/exitbox-24-hover.svg"));
        }
    }

    return;
}

void TakeInBoxToolButton::mouseReleaseEvent(QMouseEvent *event)
{
    setIconSize(QSize(24,24));
    //设置边框, 边框色, 背景色, 字体色, 字号
    if (false == m_bEnterTakeInBox) {
        setIcon(QIcon(":/images/box-24.svg"));
    } else {
        setIcon(QIcon(":/images/exitbox-24.svg"));
    }

    int x = event->x();
    int y = event->y();
    //假如在QRect(0, 0, 24, 24));这个区域里，就发出信号
    if (x >= 0 && x <= 29 && y >= 0 && y<=29) {
        emit Sig_clicked();
    }
    return;
}


