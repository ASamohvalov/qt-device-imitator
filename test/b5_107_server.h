#ifndef B5_107_SERVER_H
#define B5_107_SERVER_H

#include <QObject>

class B5_107Server : public QObject
{
    Q_OBJECT
public:
    explicit B5_107Server(QObject *parent = nullptr);

signals:
};

#endif // B5_107_SERVER_H
