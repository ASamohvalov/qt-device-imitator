#include "tcp_socket_client.h"

TcpSocketClient::TcpSocketClient(QString address, int port, QObject *parent)
    : QObject{parent}
    , _socket(new QTcpSocket(this))
{
    _socket->connectToHost(address, port);
    connect(_socket, &QTcpSocket::connected, this, &TcpSocketClient::onConnected);
    connect(_socket, &QTcpSocket::readyRead, this, &TcpSocketClient::onReadyRead);
}

void TcpSocketClient::onConnected()
{
    qDebug() << "device is connected";

    _socket->write("output off\n");
    _socket->flush();

    _socket->write("meas:volt ?\n");
    _socket->flush();
}

void TcpSocketClient::onReadyRead()
{
    QByteArray data = _socket->readAll();
    qDebug() << data;
}
