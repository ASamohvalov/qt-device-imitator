#ifndef DEVICE_IMITATOR_H
#define DEVICE_IMITATOR_H

#include "temperature_meter.h"
#include "modbus_server.h"

#include <QObject>

class DeviceImitator : public QObject
{
    Q_OBJECT
public:
    explicit DeviceImitator(QObject* parent = nullptr);
    void imitate();

private slots:
    // data written by modbus client
    void onDataWritten(QModbusDataUnit::RegisterType table, int address, int size);

private:
    TemperatureMeter _tempMeter;
    ModbusServer _modbusServer;
};

#endif // DEVICE_IMITATOR_H
