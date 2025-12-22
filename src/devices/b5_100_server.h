#ifndef B5_100_SERVER_H
#define B5_100_SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

// for B5-107 and B5-110
class B5_100Server : public QObject
{
    Q_OBJECT
public:
    explicit B5_100Server(QObject *parent = nullptr);
    void startServer(int port);

    QString logDeviceName = "[B5-100]";
    float minCurr = 0, maxCurr = 0;
    float minVolt = 0, maxVolt = 0;

signals:
    void currentChanged(float curr);
    void voltageChanged(float curr);

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    void parse(QTcpSocket* client, const QString& str);

    QTcpServer* _server;

    float current = 0;
    float voltage = 0;
    bool output = true;
};

#endif // B5_100_SERVER_H
