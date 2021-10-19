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

#ifndef MONITORTHREAD_H
#define MONITORTHREAD_H

#include <QThread>
#include <QDateTime>
#include <QGSettings>
#include <QMap>

class NotificationPlugin;
class QProcess;

class MonitorThread : public QThread
{
    Q_OBJECT
public:
    MonitorThread(NotificationPlugin *parent);
    void run();                                 //线程入口函数（工作线程的主函数）
    void extractData(QString strOutput);
    void getSettingsValue();
    QList<char *> listExistsPath();
    void fromSettingsGetInfoToList();
    void switchEnable(bool bEnabled);
    bool powerstatus =true;

private:
    NotificationPlugin*     m_parent;           //传一个插件对象指针，用来回传槽函数
    QProcess*               m_pProcess;
    QGSettings*             m_pSettings;
    QGSettings* m_pControlCenterGseting;
    QMap<QString, int>      m_nAppMaxNum;
    QMap<QString, bool>     m_mapAppSwitch;
    bool                    m_bEnabled;         //控制面板通知中心总开关
    bool getControlCentorAppNotify(QString appName);

signals:
    void Sig_Notify(QString, QString, QString, QString, QDateTime, int, bool);
    void Sig_Takein(QString, QString, QString, QString, QDateTime, int, bool);
    void Sig_CloseAppMsg(QString strAppName);
    void Sig_UpdateAppMaxNum(QString strAppName, int maxNum);

public slots:
    void readOutputData();
    void appNotifySettingChangedSlot();
};

#endif // MONITORTHREAD_H
