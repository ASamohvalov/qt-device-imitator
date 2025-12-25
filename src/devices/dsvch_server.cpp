#include "dsvch_server.h"

#include <QModbusTcpServer>

DSVCHServer::DSVCHServer(QObject *parent)
    : QObject{parent}
    , _server(new QModbusTcpServer(this))
{
    initRegisters();

    connect(_server, &QModbusServer::dataWritten, this, &DSVCHServer::onDataWritten);
    connect(_server, &QModbusServer::errorOccurred, this, &DSVCHServer::onErrorOccurred);
}

bool DSVCHServer::startServer(const QString& address, int port, int serverAddress)
{
    _server->setConnectionParameter(QModbusDevice::NetworkAddressParameter, address);
    _server->setConnectionParameter(QModbusDevice::NetworkPortParameter, port);
    _server->setServerAddress(serverAddress);

    if (!_server->connectDevice()) {
        qCritical() << "[ERROR] failed to start Modbus server:"
                    << _server->errorString();
        return false;
    }
    qInfo() << "[DSVCH] server successfully started on address:" << address << ":" << port ;
    return true;
}

void DSVCHServer::onDataWritten(QModbusDataUnit::RegisterType table, int address, int size)
{
    if (table != QModbusDataUnit::HoldingRegisters)
        return;

    QModbusDataUnit unit(table, address, size);
    if (!_server->data(&unit))
        return;

    /*
    if (address == 15 && size == 1 && unit.value(0) == 0xFFFF) {
        _server->setData(getDefaultDataUnit());
    }
    */
}

void DSVCHServer::onErrorOccurred(QModbusDevice::Error error)
{
    qCritical() << "[ERROR] modbus server error:"
                << error
                << _server->errorString();
}

void DSVCHServer::initRegisters()
{
    QModbusDataUnitMap registers;

    registers.insert(QModbusDataUnit::HoldingRegisters, getDefaultDataUnit());

    if (!_server->setMap(registers)) {
        qCritical() << "[ERROR] modbus failed to set register map:";
    }
}

QModbusDataUnit DSVCHServer::getDefaultDataUnit()
{
    QList<quint16> values;
    values.resize(68);

    // ip_addr
    values[0] = 192;
    values[1] = 168;
    values[2] = 1;
    values[3] = 55;

    // subnet
    values[4] = 255;
    values[5] = 255;
    values[6] = 0;
    values[7] = 0;

    values[8]  = 0x01;
    values[9] = 0x23;
    values[10] = 0x45;
    values[11] = 0x67;
    values[12] = 0x89;
    values[13] = 0xAB;

    QModbusDataUnit dataUnit(QModbusDataUnit::HoldingRegisters, 0, 68);
    dataUnit.setValues(values);

    return dataUnit;
}
