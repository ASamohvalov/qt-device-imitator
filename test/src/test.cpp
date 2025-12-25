#include "modbus_client.h"
#include "tcp_socket_client.h"

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // TcpSocketClient tcpClient("127.0.0.1", 5025);
    ModbusClient client("127.0.0.1", 1503, 3);
    return a.exec();
}
