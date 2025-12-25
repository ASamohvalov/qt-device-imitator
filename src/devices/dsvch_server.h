#ifndef DSVCH_SERVER_H
#define DSVCH_SERVER_H

#include <QObject>
#include <QModbusServer>

class DSVCHServer : public QObject
{
    Q_OBJECT
public:
    explicit DSVCHServer(QObject *parent = nullptr);

    bool startServer(const QString& address, int port, int serverAddress);

private slots:
    void onDataWritten(QModbusDataUnit::RegisterType table, int address, int size);

private slots:
    void onErrorOccurred(QModbusDevice::Error error);

private:
    void initRegisters();
    QModbusDataUnit getDefaultDataUnit();

    QModbusServer* _server;
};

#endif // DSVCH_SERVER_H
