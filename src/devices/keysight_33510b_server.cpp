#include "keysight_33510b_server.h"

#include <QTcpSocket>

KeySight_33510BServer::KeySight_33510BServer(QObject *parent)
    : QObject{parent}
    , _server(new QTcpServer(this))
{
    connect(_server, &QTcpServer::newConnection, this, &KeySight_33510BServer::onNewConnection);
}

void KeySight_33510BServer::startServer(int port)
{
    if (!_server->listen(QHostAddress::Any, port)) {
        qDebug() << "[KeySight 33510B] failed to start tcp server on port:" << port;
        return;
    }
    qDebug() << "[KeySight 33510B] server successfully started on port:" << port;
}

void KeySight_33510BServer::onNewConnection()
{
    QTcpSocket* client = _server->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, this, &KeySight_33510BServer::onReadyRead);
    connect(client, &QTcpSocket::disconnected, _server, &QTcpServer::deleteLater);
    qDebug() << "[KeySight 33510B] new connection";
}

void KeySight_33510BServer::onReadyRead()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = client->readAll();
    qDebug() << "[KeySight 33510B] received data -" << data;
    parse(client, data);
}

void KeySight_33510BServer::parse(QTcpSocket* client, const QString& str)
{
    QString cmd = str.simplified().toLower();

    // symmetry
    if (cmd.startsWith("func:ramp:symm")) {
        QString rest = cmd.mid(14).trimmed();
        if (rest == '?') {
            qDebug() << "[KeySight 33510B] symmetry get" << funcRampSymm;
            QByteArray response = QString::number(funcRampSymm, 'f', 6).toUtf8();
            client->write(response);
            return;
        }

        bool ok;
        float val = rest.toFloat(&ok);
        if (ok) {
            // add minmax checker!
            funcRampSymm = val;
            qDebug() << "[KeySight 33510B] symmetry set to" << val;
            return;
        }
        qCritical() << "[KeySight 33510B] ERROR set value is not a number";
    }

    // decycle
    if (cmd.startsWith("func:squ:dcyc")) {
        QString rest = cmd.mid(13).trimmed();
        if (rest == '?') {
            qDebug() << "[KeySight 33510B] decycle get" << funcSquDcyc;
            QByteArray response = QString::number(funcSquDcyc, 'f', 6).toUtf8();
            client->write(response);
            return;
        }

        bool ok;
        float val = rest.toFloat(&ok);
        if (ok) {
            // add minmax checker!
            funcSquDcyc = val;
            qDebug() << "[KeySight 33510B] decycle set to" << val;
            return;
        }
        qCritical() << "[KeySight 33510B] ERROR set value is not a number";
    }

    // function ??
    else if (cmd.startsWith("func")) {
        int cmdLength = cmd.startsWith("function") ? 7 : 4;
        QString rest = cmd.mid(cmdLength).trimmed();

        if (rest == '?') {
            qDebug() << "[KeySight 33510B] funciton get" << function;
            client->write(function.toLatin1());
            return;
        }

        function = rest.simplified().toUpper();
        qDebug() << "[KeySight 33510B] funciton set to" << rest;

        /*
        else if (rest == "SIG") {
        } else if (rest == "SQU") {
        } else if (rest == "TRI") {
        } else if (rest == "RAMP") {
        } else if (rest == "PULS") {
        } else if (rest == "NOIS") {
        } else if (rest == "ARB") {
        } else if (rest == "DC") {
        } else {
            qCritical() << "[KeySight 33510B] ERROR no such func" << rest;
        }
        */
    }

    // frequency
    else if (cmd.startsWith("freq")) {
        int cmdLength = cmd.startsWith("frequency") ? 7 : 4;
        QString rest = cmd.mid(cmdLength).trimmed();

        if (rest == '?') {
            qDebug() << "[KeySight 33510B] frequency get" << frequency;
            QByteArray response = QString::number(frequency, 'f', 6).toUtf8();
            client->write(response);
            return;
        }

        bool ok;
        float val = rest.toFloat(&ok);
        if (ok) {
            // add minmax checker!
            frequency = val;
            qDebug() << "[KeySight 33510B] frequency set to" << val;
            return;
        }
        qCritical() << "[KeySight 33510B] ERROR set value is not a number";
    }

    // amplitude and amplitude fact ??
    else if (cmd.startsWith("volt")) {
        int cmdLength = cmd.startsWith("voltage") ? 7 : 4;
        QString rest = cmd.mid(cmdLength).trimmed();

        if (rest == '?') {
            qDebug() << "[KeySight 33510B] voltage get" << voltage;
            QByteArray response = QString::number(voltage, 'f', 6).toUtf8();
            client->write(response);
            return;
        }

        bool ok;
        float val = rest.toFloat(&ok);
        if (ok) {
            // add minmax checker!
            voltage = val;
            qDebug() << "[KeySight 33510B] voltage set to" << val;
            return;
        }
        qCritical() << "[KeySight 33510B] ERROR set value is not a number";
    }

    // offset ??
    else if (cmd.startsWith("volt:offs")) {
        int cmdLength = 9;
        QString rest = cmd.mid(cmdLength).trimmed();

        if (rest == '?') {
            qDebug() << "[KeySight 33510B] offset get" << voltageOffset;
            QByteArray response = QString::number(voltageOffset, 'f', 6).toUtf8();
            client->write(response);
            return;
        }

        bool ok;
        float val = rest.toFloat(&ok);
        if (ok) {
            // add minmax checker!
            voltageOffset = val;
            qDebug() << "[KeySight 33510B] offset set to" << val;
            return;
        }
        qCritical() << "[KeySight 33510B] ERROR set value is not a number";
    }

    // load ??
    else if (cmd.startsWith("outp:load")) {
        int cmdLength = 9;
        QString rest = cmd.mid(cmdLength).trimmed();

        if (rest == '?') {
            qDebug() << "[KeySight 33510B] load get" << outputLoad;
            QByteArray response = QString::number(outputLoad, 'f', 6).toUtf8();
            client->write(response);
            return;
        }

        bool ok;
        float val = rest.toFloat(&ok);
        if (ok) {
            // add minmax checker!
            voltageOffset = val;
            qDebug() << "[KeySight 33510B] offset set to" << val;
            return;
        }
        qCritical() << "[KeySight 33510B] ERROR set value is not a number";
    }

    // output
    else if (cmd.startsWith("outp")) {
        int cmdLength = cmd.startsWith("output") ? 6 : 4;
        QString rest = cmd.mid(cmdLength).trimmed();

        if (rest == "on") {
            output = true;
            qDebug() << "[KeySight 33510B] output set to ON";
        } else if (rest == "off") {
            output = false;
            qDebug() << "[KeySight 33510B] output set to OFF";
        } else {
            qDebug() << "[KeySight 33510B] ERROR output syntax error";
        }
    }
}
