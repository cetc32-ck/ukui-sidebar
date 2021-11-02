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
#include "singleApplication.h"
#include <QtNetwork/QLocalSocket>
#include <QFileInfo>

#define TIME_OUT                (500)    // 500ms

SingleApplication::SingleApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , w(NULL)
    , _isRunning(false)
    , _localServer(NULL) {

    // 取应用程序名作为LocalServer的名字
    //Take the application name as the LocalServer name.
    _serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName() + QLatin1String(getenv("DISPLAY"));

    _initLocalConnection();
}


// 检查是否已經有一个实例在运行, true - 有实例运行， false - 没有实例运行
/*
 *  check if there is already an instance running, true
 *  there is an instance running, false - no instance running
*/
bool SingleApplication::isRunning() {
    return _isRunning;
}

// 通过socket通讯实现程序单实例运行，监听到新的连接时触发该函数
/*
 * Single instance execution of the program via socket communication
 * which is triggered when a new connection is listened to
*/
void SingleApplication::_newLocalConnection() {
    QLocalSocket *socket = _localServer->nextPendingConnection();
    if(socket) {
        socket->waitForReadyRead(2*TIME_OUT);
        delete socket;

        _activateWindow();
    }
}

// 通过socket通讯实现程序单实例运行，初始化本地连接，如果连接不上server，则创建，否则退出
/*
 * Single instance running of the program via socket communication,
 * initializing the local connection,
 * creating it if you can't connect to the server, otherwise exiting
*/
void SingleApplication::_initLocalConnection() {
    _isRunning = false;

    QLocalSocket socket;
    socket.connectToServer(_serverName);
    if(socket.waitForConnected(TIME_OUT)) {
        fprintf(stderr, "%s already running.\n",
                _serverName.toLocal8Bit().constData());
        _isRunning = true;

        return;
    }


    _newLocalServer();
}

// 创建LocalServer
// create localserver
void SingleApplication::_newLocalServer() {
    _localServer = new QLocalServer(this);
    connect(_localServer, SIGNAL(newConnection()), this, SLOT(_newLocalConnection()));
    if(!_localServer->listen(_serverName)) {
        // 此时监听失败，可能是程序崩溃时,残留进程服务导致的,移除之
        /*
         * This is a listening failure,
         * probably caused by the residual process service when the program crashes,
         * remove it.
        */
        if(_localServer->serverError() == QAbstractSocket::AddressInUseError) {
            QLocalServer::removeServer(_serverName); // <-- 重点
            _localServer->listen(_serverName); // 再次监听
        }
    }
}

// 激活主窗口
//Activate the main window
void SingleApplication::_activateWindow() {
    if(w) {
        w->show();
        w->raise();
        w->activateWindow();
    }
}
