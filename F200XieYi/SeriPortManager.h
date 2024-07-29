#ifndef SERIPORTMANAGER_H
#define SERIPORTMANAGER_H
#include <QSerialPort>
#include <QThread>
#include <QSerialPortInfo>

class SeriPortManager : public QObject
{
    Q_OBJECT

public:
    SeriPortManager();

private:
    void initPort();

private:
    QSerialPort m_devicePort;

private slots:
    void onDeviceDataReady();

};

#endif // SERIPORTMANAGER_H
