#ifndef TRM210_SERVER_H
#define TRM210_SERVER_H

#include <QModbusServer>
#include <QObject>

class TRM210Server : public QObject
{
    Q_OBJECT
public:
    TRM210Server(QObject* parent = nullptr);
    bool startServer(QString address, int port, int serverAddress);

signals:
    void spWritten(float data);

public slots:
    void onPwChanged(float data);

private slots:
    void onDataWritten(QModbusDataUnit::RegisterType table, int address, int size);

private slots:
    void onErrorOccurred(QModbusDevice::Error error);

private:
    void initRegisters();

    QModbusServer* _server;
};

#endif // TRM210_SERVER_H
