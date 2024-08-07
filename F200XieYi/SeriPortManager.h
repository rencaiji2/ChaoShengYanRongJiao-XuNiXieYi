#ifndef SERIPORTMANAGER_H
#define SERIPORTMANAGER_H
#include <QSerialPort>
#include <QThread>
#include <QSerialPortInfo>
#include <QTimer>

class SeriPortManager : public QObject
{
    Q_OBJECT

public:
    SeriPortManager();

private:
    void initPort();

private:
    QSerialPort m_devicePort;
    QTimer m_handshaketimer;
    QTimer m_presstimer;

public slots:
    void onDeviceDataReady();
    void handshaketimer_slot();
    void presstimer_slot();

};

#endif // SERIPORTMANAGER_H
