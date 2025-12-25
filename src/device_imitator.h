#ifndef DEVICE_IMITATOR_H
#define DEVICE_IMITATOR_H

#include "temperature_meter.h"
#include "devices/trm210_server.h"
#include "devices/trm10_server.h"
#include "devices/b5_100_server.h"
#include "devices/keysight_33510b_server.h"
#include "devices/dsvch_server.h"

#include <QObject>

class DeviceImitator : public QObject
{
    Q_OBJECT
public:
    explicit DeviceImitator(QObject* parent = nullptr);
    void imitate();

private slots:
    // data written by modbus client
    void onTargetTempSet(float data);
    void onTargetTempSet10(float data);

private:
    TemperatureMeter _tempMeter210;
    TRM210Server _trm210Server;
    TemperatureMeter _tempMeter10;
    TRM10Server _trm10Server;

    B5_100Server _b5_107Server;
    B5_100Server _b5_110Server;

    KeySight_33510BServer _keysight_33510BServer;

    DSVCHServer _dsvchServer;
};

#endif // DEVICE_IMITATOR_H
