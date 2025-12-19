#ifndef TRM10_SERVER_H
#define TRM10_SERVER_H

#include <QModbusServer>
#include <QObject>

class TRM10Server : public QObject
{
    Q_OBJECT
public:
    TRM10Server(QObject* parent = nullptr);
    bool startServer(const QString& address, int port, int serverAddress);

signals:
    void spWritten(float data);

public slots:
    void onPwChanged(float data);

private slots:
    void onDataWritten(QModbusDataUnit::RegisterType table, int address, int size);

private slots:
    void onErrorOccurred(QModbusDevice::Error error);

private:
    void initRegisters();

    QModbusServer* _server;
};

#endif // TRM10_SERVER_H
