#include "device_imitator.h"

#include <QDebug>

DeviceImitator::DeviceImitator(QObject* parent)
    : QObject(parent)
{
    connect(&_modbusServer, &ModbusServer::spWritten, this, &DeviceImitator::onTargetTempSet);
}

void DeviceImitator::imitate()
{
    _modbusServer.startServer();
    _tempMeter.start();
}

void DeviceImitator::onTargetTempSet(float data)
{
    _tempMeter.setTargetTemp(data);
}
