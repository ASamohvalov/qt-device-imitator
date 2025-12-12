#ifndef TEMPERATURE_METER_H
#define TEMPERATURE_METER_H

#include <QObject>
#include <QThread>
#include <QMutex>

class TemperatureMeter : public QThread
{
    Q_OBJECT
public:
    explicit TemperatureMeter(QObject *parent = nullptr);

    double currentTemp();
    void setTargetTemp(double temp);

protected:
    void run() override;

private:
    double _currentTemp = 20;
    double _targetTemp = 20;

    bool _up = true;

    QMutex _mutex;
};

#endif // TEMPERATURE_METER_H
