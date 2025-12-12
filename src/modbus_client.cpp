#include "modbus_client.h"

#include <QModbusTcpClient>
#include <QVariant>
#include <QDebug>

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
    qInfo() << "modbus connection success, on port" << port << ":" << address;

    connect(_timer, &QTimer::timeout, this, &ModbusClient::readRequest);
    _timer->setInterval(1000);

    if (!_modbusClient->connectDevice()) {
        qCritical() << "Modbus connection error";
    } else {
        qInfo() << "Connecting to" << address << ":" << port;
    }
}

void ModbusClient::onModbusStateChanged(QModbusDevice::State state)
{
    if (state == QModbusDevice::ConnectedState) {
        qCritical() << "device is connected";
        _timer->start();
    } else if (state == QModbusDevice::UnconnectedState) {
        qCritical() << "device is unconnected";
        _timer->stop();
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
    } else {
        qCritical() << "read data error";
    }
    reply->deleteLater();
}

void ModbusClient::readRequest()
{
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0, 10);
    QModbusReply* reply = _modbusClient->sendReadRequest(readUnit, _serverAddress);
    if (!reply) {
        qCritical() << "get data failed";
        return;
    }

    if (!reply->isFinished()) {
        connect(reply, &QModbusReply::finished, this, &ModbusClient::onReadReady);
    } else {
        reply->deleteLater();
    }
}

#if 0
void ModbusClient::run()
{
    while (_connected) {
        sleep(1);

        QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0, 10);
        QModbusReply* reply = _modbusClient->sendReadRequest(readUnit, _serverAddress);
        if (!reply) {
            qCritical() << "get data failed";
            continue;
        }

        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &ModbusClient::onReadReady);
        } else {
            reply->deleteLater();
        }
    }
}
#endif
