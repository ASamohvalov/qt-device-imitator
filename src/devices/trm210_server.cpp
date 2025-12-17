#include "trm210_server.h"

#include <QModbusTcpServer>

TRM210Server::TRM210Server(QObject* parent)
    : QObject(parent)
    , _server(new QModbusTcpServer(this))
{
    initRegisters();

    connect(_server, &QModbusServer::dataWritten, this, &TRM210Server::onDataWritten);
    connect(_server, &QModbusServer::errorOccurred, this, &TRM210Server::onErrorOccurred);
}

bool TRM210Server::startServer(QString address, int port, int serverAddress)
{
    _server->setConnectionParameter(QModbusDevice::NetworkAddressParameter, address);
    _server->setConnectionParameter(QModbusDevice::NetworkPortParameter, port);
    _server->setServerAddress(serverAddress);

    if (!_server->connectDevice()) {
        qCritical() << "[ERROR] failed to start Modbus server:"
                    << _server->errorString();
        return false;
    }
    qInfo() << "[TRM210] server successfully started on address:" << address << ":" << port ;
    return true;
}

void TRM210Server::onPwChanged(float data)
{
    quint32 rawdata;
    memcpy(&rawdata, &data, sizeof(data));
    quint16 hi = (rawdata >> 16) & 0xFFFF;
    quint16 lo = rawdata & 0xFFFF;
    if (!_server->setData(QModbusDataUnit::HoldingRegisters, 0x1009, hi)
        && !_server->setData(QModbusDataUnit::HoldingRegisters, 0x100A, lo)) {
        qInfo() << "[ERROR] failed to set data in registers (0x1009-0x100A)";
    }

    // set to 0x0001
    quint16 value = static_cast<quint16>(data);
    if (!_server->setData(QModbusDataUnit::HoldingRegisters, 0x0001, value)) {
        qInfo() << "[ERROR] failed to set data in register (0x0001)";
    }
}

void TRM210Server::onDataWritten(QModbusDataUnit::RegisterType table, int address, int size)
{
    if (table != QModbusDataUnit::HoldingRegisters)
        return;

    QModbusDataUnit unit(table, address, size);
    if (!_server->data(&unit))
        return;

    // SP 0x0002
    if (address == 0x0002 && size == 1) {
        quint16 data = unit.value(0);
        emit spWritten(data);
    }

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

void TRM210Server::onErrorOccurred(QModbusDevice::Error error)
{
    qCritical() << "[ERROR] modbus server error:"
                << error
                << _server->errorString();
}

void TRM210Server::initRegisters()
{
    QModbusDataUnitMap registers;

    registers.insert(QModbusDataUnit::HoldingRegisters, QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 0x100C + 1));

    if (!_server->setMap(registers)) {
        qCritical() << "[ERROR] modbus failed to set register map:"
                    << _server->errorString();
    }
}
