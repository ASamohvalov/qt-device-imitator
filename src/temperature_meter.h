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

    float currentTemp();
    void setTargetTemp(float temp);

signals:
    void tempChanged(float temp);

protected:
    void run() override;

private:
    // no mutex here
    void setCurrentTemp(float temp);

    float _currentTemp = 20;
    float _targetTemp = 20;

    bool _up = true;

    QMutex _mutex;
};

#endif // TEMPERATURE_METER_H
