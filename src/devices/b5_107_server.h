#ifndef B5_107_SERVER_H
#define B5_107_SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class B5_107Server : public QObject
{
    Q_OBJECT
public:
    explicit B5_107Server(QObject *parent = nullptr);
    void startServer(int port);

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer* _server;
};

#endif // B5_107_SERVER_H
