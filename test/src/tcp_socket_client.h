#ifndef TCP_SOCKET_CLIENT_H
#define TCP_SOCKET_CLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocketClient(QString address, int port, QObject *parent = nullptr);

private slots:
    void onConnected();
    void onReadyRead();

private:
    QTcpSocket* _socket;
};

#endif // TCP_SOCKET_CLIENT_H
