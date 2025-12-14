#ifndef MODBUS_SERVER_H
#define MODBUS_SERVER_H

#include <QModbusServer>
#include <QUrl>

class ModbusServer : public QObject
{
public:
    ModbusServer(QObject* parent = nullptr);
    bool startServer();

signals:
    void dataWritten(QModbusDataUnit::RegisterType type, int address, int size);

private slots:
    void onErrorOccurred(QModbusDevice::Error error);

private:
    void initRegisters();

    QModbusServer* _server;
};

#endif // MODBUS_SERVER_H
