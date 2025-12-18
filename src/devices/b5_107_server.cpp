#include "b5_107_server.h"

B5_107Server::B5_107Server(QObject *parent)
    : QObject{parent}
    , _server(new QTcpServer())
{
    connect(_server, &QTcpServer::newConnection, this, &B5_107Server::onNewConnection);
}

void B5_107Server::startServer(int port)
{
    if (!_server->listen(QHostAddress::Any, port)) {
        qDebug() << "[B5-107] failed to start tcp server on port:" << port;
        return;
    }
    qDebug() << "[B5-107] server successfully started on port:" << port;
}

void B5_107Server::onNewConnection()
{
    QTcpSocket* client = _server->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, this, &B5_107Server::onReadyRead);
    connect(client, &QTcpSocket::disconnected, client, &QTcpSocket::deleteLater);
    qDebug() << "[B5-107] new connection";
}

void B5_107Server::onReadyRead()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = client->readAll();
    qDebug() << "[B5-107] received data -" << data;
    client->write("hello");
}
