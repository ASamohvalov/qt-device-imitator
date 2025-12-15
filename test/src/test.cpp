#include "modbus_client.h"

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ModbusClient client("127.0.0.1", 1502);
    return a.exec();
}
