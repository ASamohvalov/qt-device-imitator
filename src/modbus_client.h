#ifndef MODBUS_CLIENT_H
#define MODBUS_CLIENT_H

#include <QThread>
#include <QModbusClient>
#include <QTimer>

class ModbusClient : public QObject
{
    Q_OBJECT
public:
    ModbusClient(QString address, int port, QObject* parent = nullptr);

signals:
    void request(quint16 data[10]);

private slots:
    void onModbusStateChanged(QModbusDevice::State state);
    void onReadReady();
    void readRequest();

private:
    QModbusClient* _modbusClient;
    QTimer* _timer;
    bool _connected = false;

    static constexpr int _timeout = 10000;
    static constexpr int _serverAddress = 1;
};

#endif // MODBUS_CLIENT_H
