#include "b5_107_server.h"

B5_107Server::B5_107Server(QObject *parent)
    : QObject{parent}
    , _server(new QTcpServer())
{
    connect(_server, &QTcpServer::newConnection, this, &B5_107Server::onNewConnection);
}

void B5_107Server::startServer(int port)
{
    if (!_server->listen(QHostAddress::Any, port)) {
        qDebug() << "[B5-107] failed to start tcp server on port:" << port;
        return;
    }
    qDebug() << "[B5-107] server successfully started on port:" << port;
}

void B5_107Server::onNewConnection()
{
    QTcpSocket* client = _server->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, this, &B5_107Server::onReadyRead);
    connect(client, &QTcpSocket::disconnected, client, &QTcpSocket::deleteLater);
    qDebug() << "[B5-107] new connection";
}

void B5_107Server::onReadyRead()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = client->readAll();
    qDebug() << "[B5-107] received data -" << data;
    parse(client, data);
}

void B5_107Server::parse(QTcpSocket* client, const QString& str)
{
    /*
    QString aliases[5][2] = {
        { "current", "curr" },
        { "voltage", "volt" },
        { "current_out", "meas:curr" },
        { "voltage_out", "meas:volt" },
        { "output", "outp" }
    };
    */
    qDebug() << "[B5-107] parse started";
    QString cmd = str.simplified().toLower();
    qDebug() << cmd;

    if (cmd.startsWith("current") || cmd.startsWith("curr")) {
        int cmdLength = cmd.startsWith("current") ? 7 : 4;
        QString rest = cmd.mid(cmdLength).trimmed();

        if (rest.endsWith('?')) {
            qDebug() << "[B5-107] current get" << current;
            QByteArray response = QString::number(current, 'f', 6).toUtf8();
            client->write(response);
            return;
        }

        bool ok;
        float val = rest.toFloat(&ok);
        if (ok) {
            // emit currentChanged(val);
            current = val;
            qDebug() << "[B5-107] current set to" << val;
            return;
        }
        qCritical() << "[ERROR] set value is not a number";
    }

    else if (cmd.startsWith("voltage") || cmd.startsWith("volt")) {
        int cmdLength = cmd == "volt" ? 4 : 7;
        QString rest = cmd.mid(cmdLength).trimmed();

        if (rest.endsWith('?')) {
            qDebug() << "[B5-107] voltage get" << voltage;
            QByteArray response = QString::number(voltage, 'f', 6).toUtf8();
            client->write(response);
            return;
        }

        bool ok;
        float val = rest.toFloat(&ok);
        if (ok) {
            // emit voltageChanged(val);
            voltage = val;
            qDebug() << "[B5-107] voltage set to" << val;
            return;
        }
        qCritical() << "[ERROR] set value is not a number";
    }
}
