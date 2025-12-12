#include "temperature_meter.h"
#include "modbus_client.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TemperatureMeter tempMeter;
    tempMeter.start();

    ModbusClient client("127.0.0.1", 1502);

    return a.exec();
}
