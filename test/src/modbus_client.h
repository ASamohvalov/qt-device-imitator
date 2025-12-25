#ifndef MODBUS_CLIENT_H
#define MODBUS_CLIENT_H

#include <QThread>
#include <QModbusClient>
#include <QTimer>

class ModbusClient : public QObject
{
    Q_OBJECT
public:
    ModbusClient(QString address, int port, int serverAddress, QObject* parent = nullptr);

signals:
    void request(quint16 data[10]);

private slots:
    void onModbusStateChanged(QModbusDevice::State state);
    void onReadReady();

private:
    void startTest();
    void writeDataOnSp210(float data);
    void writeDataOnSp10(float data);
    void writeDataToRegister(int address, quint16 value);

    QModbusClient* _modbusClient;

    static constexpr int _timeout = 10000;
    const int _serverAddress;
};

#endif // MODBUS_CLIENT_H
