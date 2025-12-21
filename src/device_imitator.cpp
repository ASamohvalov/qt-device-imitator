#include "device_imitator.h"

#include <QDebug>

DeviceImitator::DeviceImitator(QObject* parent)
    : QObject(parent)
{
    connect(&_trm210Server, &TRM210Server::spWritten, this, &DeviceImitator::onTargetTempSet);
    connect(&_tempMeter210, &TemperatureMeter::tempChanged, &_trm210Server, &TRM210Server::onPwChanged);

    connect(&_trm10Server, &TRM10Server::spWritten, this, &DeviceImitator::onTargetTempSet10);
    connect(&_tempMeter10, &TemperatureMeter::tempChanged, &_trm10Server, &TRM10Server::onPwChanged);
}

void DeviceImitator::imitate()
{
    _trm210Server.startServer("127.0.0.1", 1502, 1);
    _tempMeter210.start();

    _trm10Server.startServer("127.0.0.1", 1501, 2);
    _tempMeter10.start();

    _b5_107Server.startServer(8080);
    _b5_107Server.logDeviceName = "[B5-107]";
    _b5_110Server.startServer(8081);
    _b5_110Server.logDeviceName = "[B5-110]";
}

void DeviceImitator::onTargetTempSet(float data)
{
    _tempMeter210.setTargetTemp(data);
}

void DeviceImitator::onTargetTempSet10(float data)
{
    _tempMeter10.setTargetTemp(data);
}
