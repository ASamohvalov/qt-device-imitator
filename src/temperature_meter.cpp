#include "temperature_meter.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QMutexLocker>

TemperatureMeter::TemperatureMeter(QObject *parent)
    : QThread{parent}
{}

float TemperatureMeter::currentTemp()
{
    QMutexLocker locker(&_mutex);
    return _currentTemp;
}

void TemperatureMeter::run()
{
    forever {
        {
            QMutexLocker locker(&_mutex);
            if (_up && _currentTemp < _targetTemp) {
                setCurrentTemp(_currentTemp + 0.1 + (QRandomGenerator::global()->bounded(0.2)));
                qInfo() << "current temperature -" << _currentTemp;
            } else if (!_up && _currentTemp > _targetTemp) {
                setCurrentTemp(_currentTemp - 0.1 + (QRandomGenerator::global()->bounded(0.2)));
                qInfo() << "current temperature -" << _currentTemp;
            }
        }
        sleep(1);
    }
}

void TemperatureMeter::setTargetTemp(float temp)
{
    QMutexLocker locker(&_mutex);
    _targetTemp = temp;
    _up = _currentTemp <= _targetTemp;
}

void TemperatureMeter::setCurrentTemp(float temp)
{
    _currentTemp = temp;
    emit tempChanged(temp);
}
