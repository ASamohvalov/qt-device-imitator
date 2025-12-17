#include "trm10_server.h"

#include <QModbusTcpServer>

TRM10Server::TRM10Server(QObject* parent)
    : QObject(parent)
    , _server(new QModbusTcpServer(this))
{
    initRegisters();

    connect(_server, &QModbusServer::dataWritten, this, &TRM10Server::onDataWritten);
    connect(_server, &QModbusServer::errorOccurred, this, &TRM10Server::onErrorOccurred);
}

bool TRM10Server::startServer(QString address, int port, int serverAddress)
{
    _server->setConnectionParameter(QModbusDevice::NetworkAddressParameter, address);
    _server->setConnectionParameter(QModbusDevice::NetworkPortParameter, port);
    _server->setServerAddress(serverAddress);

    if (!_server->connectDevice()) {
        qCritical() << "[ERROR] failed to start Modbus server:"
                    << _server->errorString();
        return false;
    }
    qInfo() << "[TRM10] server successfully started on address:" << address << ":" << port ;
    return true;
}

void TRM10Server::onPwChanged(float data)
{
    quint32 rawdata;
    memcpy(&rawdata, &data, sizeof(data));
    quint16 hi = (rawdata >> 16) & 0xFFFF;
    quint16 lo = rawdata & 0xFFFF;
    // 0x1000 и 0x1001 значения после обработки
    // 0x1002 и 0x1003 сырые значение (тут они пока одинаковые)
    if (!_server->setData(QModbusDataUnit::HoldingRegisters, 0x0000, hi)
        && !_server->setData(QModbusDataUnit::HoldingRegisters, 0x0001, lo)
        && !_server->setData(QModbusDataUnit::HoldingRegisters, 0x0002, hi)
        && !_server->setData(QModbusDataUnit::HoldingRegisters, 0x0003, lo)) {
        qInfo() << "[ERROR] failed to set data in registers (0x1000-0x1001)";
    }
}

void TRM10Server::onDataWritten(QModbusDataUnit::RegisterType table, int address, int size)
{
    if (table != QModbusDataUnit::HoldingRegisters)
        return;

    QModbusDataUnit unit(table, address, size);
    if (!_server->data(&unit))
        return;

    // SP 0x0200 - 0x0201
    if (address == 0x0200 && size == 2) {
        quint16	hi = unit.value(0);
        quint16	lo = unit.value(1);
        quint32 rawdata = (hi << 16) | lo;
        float data;
        memcpy(&data, &rawdata, sizeof(float));
        emit spWritten(data);
    }
}

void TRM10Server::onErrorOccurred(QModbusDevice::Error error)
{
    qCritical() << "[ERROR] modbus server error:"
                << error
                << _server->errorString();
}

void TRM10Server::initRegisters()
{
    QModbusDataUnitMap registers;

    registers.insert(QModbusDataUnit::HoldingRegisters, QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 0x0803));

    // тип датчика (по дефолту C50)
    _server->setData(QModbusDataUnit::HoldingRegisters, 0x0005, 1);

    if (!_server->setMap(registers)) {
        qCritical() << "[ERROR] modbus failed to set register map:"
                    << _server->errorString();
    }
}
