#include "keysight_33510b_server.h"

#include <QTcpSocket>

KeySight_33510BServer::KeySight_33510BServer(QObject *parent)
    : QObject{parent}
    , _server(new QTcpServer(this))
{
    connect(_server, &QTcpServer::newConnection, this, &KeySight_33510BServer::onNewConnection);
}

void KeySight_33510BServer::startServer(int port)
{
    if (!_server->listen(QHostAddress::Any, port)) {
        qDebug() << "[KeySight 33510B] failed to start tcp server on port:" << port;
    }
    qDebug() << "[KeySight 33510B] server successfully started on port:" << port;
}

void KeySight_33510BServer::onNewConnection()
{
    QTcpSocket* client = _server->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, this, &KeySight_33510BServer::onReadyRead);
    connect(client, &QTcpSocket::disconnected, _server, &QTcpServer::deleteLater);
    qDebug() << "[KeySight 33510B] new connection";
}

void KeySight_33510BServer::onReadyRead()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = client->readAll();
    qDebug() << "[KeySight 33510B] received data -" << data;
    parse(client, data);
}

void KeySight_33510BServer::parse(QTcpSocket* client, QString str)
{
    QString cmd = str.simplified().toLower();

    if (cmd.startsWith("func")) {
        // function call
    }

}
