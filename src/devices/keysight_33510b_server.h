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
    void parse(QTcpSocket* client, const QString& str);

    QTcpServer* _server;

    float frequency = 1;
    float voltage = 1;
    float voltageOffset = 0;
    bool output = true;
    int outputLoad = 50;
    QString function = "SIN";
    float funcSquDcyc = 50;
    float funcRampSymm = 50;
};

#endif // KEYSIGHT_33510B_SERVER_H
