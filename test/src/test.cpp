#include "modbus_client.h"
#include "tcp_socket_client.h"

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpSocketClient tcpClient("127.0.0.1", 8080);
    ModbusClient client("127.0.0.1", 1501, 2);
    return a.exec();
}
