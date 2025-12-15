#include "modbus_client.h"

#include <QModbusTcpClient>
#include <QVariant>
#include <QDebug>
#include <QThread>
// for std::cin
#include <iostream>

ModbusClient::ModbusClient(QString address, int port, QObject* parent)
    : QObject{parent}
    , _modbusClient(new QModbusTcpClient(this))
{
    _modbusClient->setConnectionParameter(QModbusDevice::NetworkAddressParameter, QVariant(address));
    _modbusClient->setConnectionParameter(QModbusDevice::NetworkPortParameter, QVariant(port));
    _modbusClient->setTimeout(_timeout);

    if (!_modbusClient->connectDevice()) {
        qCritical() << "modbus connection error";
        return;
    }
    qInfo() << "modbus connection with server success, on port" << port << ":" << address;

    connect(_modbusClient, &QModbusClient::stateChanged, this, &ModbusClient::onModbusStateChanged);
}

void ModbusClient::onModbusStateChanged(QModbusDevice::State state)
{
    if (state == QModbusDevice::ConnectedState) {
        qInfo() << "[State changed] device is connected";
        startTest();
    } else if (state == QModbusDevice::UnconnectedState) {
        qCritical() << "[State changed] device is unconnected";
    }
}

void ModbusClient::onReadReady()
{
    QModbusReply* reply = qobject_cast<QModbusReply*>(sender());
    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        for (qsizetype i = 0; i < unit.valueCount(); ++i) {
            quint16 value = unit.value(i);
            qInfo() << QString("address %1: value %2").arg(i).arg(value);
        }
        qInfo() << "INFO: read data success";
    } else {
        qCritical() << "ERROR: read data failed";
    }
    reply->deleteLater();
}

void ModbusClient::startTest()
{
    qInfo() << "set target temp data:";
    float temp;
    std::cin >> temp;
    writeDataOnSp(temp);
}

void ModbusClient::writeDataOnSp(float data)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 0x100B, 2);
    quint32 rawdata;
    memcpy(&rawdata, &data, sizeof(float));
    quint16 hi = (rawdata >> 16) & 0xFFFF;
    quint16 lo = rawdata & 0xFFFF;
    writeUnit.setValue(0, hi);
    writeUnit.setValue(1, lo);
    if (QModbusReply* reply = _modbusClient->sendWriteRequest(writeUnit, _serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::NoError) {
                    qInfo() << "INFO: data is write successfully";
                } else {
                    qInfo() << "ERROR: data is write failed";
                }
            });
        }
    }
}
