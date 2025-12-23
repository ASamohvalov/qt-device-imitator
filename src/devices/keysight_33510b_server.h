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
    void parse(QTcpSocket* client, QString str);

    QTcpServer* _server;

    float frequency = 1;
    float voltage = 0;
    bool output = true;
};

#endif // KEYSIGHT_33510B_SERVER_H
