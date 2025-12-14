#include "device_imitator.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DeviceImitator imitator;
    imitator.imitate();

    return a.exec();
}
