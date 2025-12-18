#include "tcp_socket_client.h"

TcpSocketClient::TcpSocketClient(QString address, int port, QObject *parent)
    : QObject{parent}
    , _socket(new QTcpSocket(this))
{
    _socket->connectToHost(address, port);
    connect(_socket, &QTcpSocket::connected, this, &TcpSocketClient::onConnected);
}

void TcpSocketClient::onConnected()
{
    qDebug() << "device is connected";

    QDataStream in(_socket);
    in.setVersion(QDataStream::Qt_6_4);
    in << "hello world!!!";
}


void TcpSocketClient::onReadyRead()
{

}
