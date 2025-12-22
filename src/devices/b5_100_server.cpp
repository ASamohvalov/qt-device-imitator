#include "b5_100_server.h"

B5_100Server::B5_100Server(QObject *parent)
    : QObject{parent}
    , _server(new QTcpServer(this))
{
    connect(_server, &QTcpServer::newConnection, this, &B5_100Server::onNewConnection);
}

void B5_100Server::startServer(int port)
{
    if (!_server->listen(QHostAddress::Any, port)) {
        qDebug() << logDeviceName << "failed to start tcp server on port:" << port;
        return;
    }
    qDebug() << logDeviceName << "server successfully started on port:" << port;
}

void B5_100Server::onNewConnection()
{
    QTcpSocket* client = _server->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, this, &B5_100Server::onReadyRead);
    connect(client, &QTcpSocket::disconnected, client, &QTcpSocket::deleteLater);
    qDebug() << logDeviceName << "new connection";
}

void B5_100Server::onReadyRead()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = client->readAll();
    qDebug() << logDeviceName << "received data -" << data;
    parse(client, data);
}

void B5_100Server::parse(QTcpSocket* client, const QString& str)
{
    QString cmd = str.simplified().toLower();

    if (cmd.startsWith("curr")) {
        int cmdLength = cmd.startsWith("current") ? 7 : 4;
        QString rest = cmd.mid(cmdLength).trimmed();

        if (rest == '?') {
            qDebug() << logDeviceName << "current get" << current;
            QByteArray response = QString::number(current, 'f', 6).toUtf8();
            client->write(response);
            return;
        }

        bool ok;
        float val = rest.toFloat(&ok);
        if (ok) {
            // minmax checker
            if (val < minCurr || val > maxCurr) {
                qCritical() << logDeviceName << "ERROR value is not in the range";
                return;
            }
            current = val;
            qDebug() << logDeviceName << "current set to" << val;
            return;
        }
        qCritical() << logDeviceName << "ERROR set value is not a number";
    }

    else if (cmd.startsWith("volt")) {
        int cmdLength = cmd.startsWith("voltage") ? 7 : 4;
        QString rest = cmd.mid(cmdLength).trimmed();

        if (rest == '?') {
            qDebug() << logDeviceName << "voltage get" << voltage;
            QByteArray response = QString::number(voltage, 'f', 6).toUtf8();
            client->write(response);
            return;
        }

        bool ok;
        float val = rest.toFloat(&ok);
        if (ok) {
            // minmax checker
            if (val < minVolt || val > maxVolt) {
                qCritical() << logDeviceName << "ERROR value is not in the range";
                return;
            }
            voltage = val;
            qDebug() << logDeviceName << "voltage set to" << val;
            return;
        }
        qCritical() << logDeviceName << "ERROR set value is not a number";
    }

    else if (cmd.startsWith("outp")) {
        int cmdLength = cmd.startsWith("output") ? 6 : 4;
        QString rest = cmd.mid(cmdLength).trimmed();

        if (rest == "on") {
            output = true;
            qDebug() << logDeviceName << "output set to ON";
        } else if (rest == "off") {
            output = false;
            qDebug() << logDeviceName << "output set to OFF";
        } else {
            qDebug() << logDeviceName << "ERROR output syntax error";
        }
    }

    else if (cmd.startsWith("current_out") || cmd.startsWith("meas:curr")) {
        int cmdLength = cmd.startsWith("current_out") ? 11 : 9;
        QString rest = cmd.mid(cmdLength).trimmed();

        float vol = output ? current : 0;
        if (rest == '?') {
            qDebug() << logDeviceName << "current_out get" << vol;
            QByteArray response = QString::number(vol, 'f', 6).toUtf8();
            client->write(response);
        }
    }

    else if (cmd.startsWith("voltage_out") || cmd.startsWith("meas:volt")) {
        int cmdLength = cmd.startsWith("voltage_out") ? 11 : 9;
        QString rest = cmd.mid(cmdLength).trimmed();

        float vol = output ? voltage : 0;
        if (rest == '?') {
            qDebug() << logDeviceName << "voltage_out get" << vol;
            QByteArray response = QString::number(vol, 'f', 6).toUtf8();
            client->write(response);
        }
    }
}
