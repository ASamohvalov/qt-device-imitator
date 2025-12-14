#include "modbus_server.h"
#include "config.h"

#include <QModbusTcpServer>
#include <QDebug>

ModbusServer::ModbusServer(QObject* parent)
    : QObject(parent)
    , _server(new QModbusTcpServer(this))
{
    initRegisters();

    connect(_server, &QModbusServer::dataWritten, this, &ModbusServer::dataWritten);
    connect(_server, &QModbusServer::errorOccurred, this, &ModbusServer::onErrorOccurred);
}

bool ModbusServer::startServer()
{
    _server->setConnectionParameter(QModbusDevice::NetworkAddressParameter, SERVER_NETWORK_ADDRESS);
    _server->setConnectionParameter(QModbusDevice::NetworkPortParameter, SERVER_NETWORK_PORT);
    _server->setServerAddress(SERVER_ADDRESS_NUMBER);
    return _server->connectDevice();
}

void ModbusServer::onErrorOccurred(QModbusDevice::Error error)
{
    qCritical() << "server error, message - " << error.errorString();
}

void ModbusServer::initRegisters()
{
    QModbusDataUnitMap registers;

    registers.insert(QModbusDataUnit::Coils,
               QModbusDataUnit(QModbusDataUnit::Coils, 0, 10));
    registers.insert(QModbusDataUnit::DiscreteInputs,
               QModbusDataUnit(QModbusDataUnit::DiscreteInputs, 0, 10));
    registers.insert(QModbusDataUnit::InputRegisters,
               QModbusDataUnit(QModbusDataUnit::InputRegisters, 0, 10));
    registers.insert(QModbusDataUnit::HoldingRegisters,
               QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 10));

    _server->setMap(registers);
}
