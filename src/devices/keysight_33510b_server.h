#ifndef KEYSIGHT_33510B_SERVER_H
#define KEYSIGHT_33510B_SERVER_H

#include <QObject>
#include <QTcpServer>

class KeySight_33510BServer : public QObject
{
    Q_OBJECT
public:
    explicit KeySight_33510BServer(QObject* parent = nullptr);
    void startServer(int port);

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    void parse(QTcpSocket* client, QString data);

    QTcpServer* _server;
};

#endif // KEYSIGHT_33510B_SERVER_H
