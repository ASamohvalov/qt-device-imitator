#include "modbus_server.h"
#include "config.h"

#include <QModbusTcpServer>
#include <QDebug>

ModbusServer::ModbusServer(QObject* parent)
    : QObject(parent)
    , _server(new QModbusTcpServer(this))
{
    initRegisters();

    connect(_server, &QModbusServer::dataWritten, this, &ModbusServer::onDataWritten);
    connect(_server, &QModbusServer::errorOccurred, this, &ModbusServer::onErrorOccurred);
}

bool ModbusServer::startServer()
{
    _server->setConnectionParameter(QModbusDevice::NetworkAddressParameter, SERVER_NETWORK_ADDRESS);
    _server->setConnectionParameter(QModbusDevice::NetworkPortParameter, SERVER_NETWORK_PORT);
    _server->setServerAddress(SERVER_ADDRESS_NUMBER);

    if (!_server->connectDevice()) {
        qCritical() << "failed to start Modbus server:"
                    << _server->errorString();
        return false;
    }
    qInfo() << "server successfully started on address:" << SERVER_NETWORK_ADDRESS << ":" << SERVER_NETWORK_PORT;
    return true;
}

void ModbusServer::onDataWritten(QModbusDataUnit::RegisterType table, int address, int size)
{
    if (table != QModbusDataUnit::HoldingRegisters)
        return;

    QModbusDataUnit unit(table, address, size);
    if (!_server->data(&unit))
        return;

    // SP 0x100B - 0x100C
    if (address == 0x100B && size == 2) {
        quint16	hi = unit.value(0);
        quint16	lo = unit.value(1);
        quint32 rawdata = (hi << 16) | lo;
        float data;
        memcpy(&data, &rawdata, sizeof(float));
        emit spWritten(data);
    }
}

void ModbusServer::onErrorOccurred(QModbusDevice::Error error)
{
    qCritical() << "modbus server error:"
                << error
                << _server->errorString();
}

void ModbusServer::initRegisters()
{
    QModbusDataUnitMap registers;

    registers.insert(QModbusDataUnit::HoldingRegisters, QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 0x100C + 1));

    if (!_server->setMap(registers)) {
        qCritical() << "modbus failed to set register map:"
                    << _server->errorString();
    }
}
