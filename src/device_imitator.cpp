#include "device_imitator.h"
#include "config.h"

#include <QDebug>

DeviceImitator::DeviceImitator(QObject* parent)
    : QObject(parent)
{
    connect(&_modbusServer, &ModbusServer::dataWritten, this, &DeviceImitator::onDataWritten);
}

void DeviceImitator::imitate()
{
    if (!_modbusServer.startServer()) {
        qCritical() << "start server error";
        return;
    }
    qInfo() << "server successfully started on address:" << SERVER_NETWORK_ADDRESS << ":" << SERVER_NETWORK_PORT;
    _tempMeter.start();
}

void DeviceImitator::onDataWritten(QModbusDataUnit::RegisterType table, int address, int size)
{
}
