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

#endif // B5_107_SERVER_H
