#include "SeriPortManager.h"
#include <QDebug>
SeriPortManager::SeriPortManager()
{
    initPort();
}

void SeriPortManager::initPort()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())//搜索串口，获取串口列表
    {
         if(info.portName()=="COM2")
         {
             m_devicePort.setPort(info);
         }
    }
    m_devicePort.open(QSerialPort::ReadWrite);
    connect(&m_devicePort,&QSerialPort::readyRead,this,&SeriPortManager::onDeviceDataReady,Qt::UniqueConnection);
    connect(&m_handshaketimer,&QTimer::timeout,this,&SeriPortManager::handshaketimer_slot,Qt::UniqueConnection);
    connect(&m_presstimer,&QTimer::timeout,this,&SeriPortManager::presstimer_slot,Qt::UniqueConnection);
    //m_handshaketimer.start(1000);
    m_presstimer.start(2000);
}

void SeriPortManager::onDeviceDataReady()
{
//    QByteArray source = m_devicePort.readAll();
//    qDebug()<<source;
//    QByteArray writebyte;
//    if(source == QByteArray::fromHex("ea 03 eb"))
//    {
//        writebyte = QByteArray::fromHex("ea 01 30 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 3c 01 01 00 00 00 65 19 00 03");
//        m_devicePort.write(writebyte);
//        writebyte = QByteArray::fromHex("00 8d eb");
//        m_devicePort.write(writebyte);
//    }
//    else
//    {
//        writebyte = QByteArray::fromHex("ea 02 01 eb");
//        writebyte[1] = source.at(1);
//        qDebug()<<"writebyte:"<<writebyte;
//        m_devicePort.write(writebyte);
//    }
}

void SeriPortManager::handshaketimer_slot()
{
//    QByteArray writebyte;
//    writebyte = QByteArray::fromHex("ea 01 30 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 3c 01 01 00 00 00 65 19 00 03 00");
//    QByteArray writebyte2 = QByteArray::fromHex("50 01 01 06 00 00 00 00 00 00 01 06 00 00 00 00 00 02 8d eb");
//    //writebyte.append(writebyte2);
//    m_devicePort.write(writebyte);
//    QTimer::singleShot(100, this, [=]()
//    {
//        m_devicePort.write(writebyte2);
//    });

        QByteArray writebyte;
        writebyte = QByteArray::fromHex("ea 01 42 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 05");
        m_devicePort.write(writebyte);
        QByteArray writebyte2=QByteArray::fromHex("00 00 00 3c 01 01 00 00 01 fe b5 02 00 00 48 01 01 06 00 00 04 79 4a e8 01 06 00 00 04 79 4a e8");
            QTimer::singleShot(50, this, [=]()
            {
                m_devicePort.write(writebyte2);
            });
        QByteArray writebyte3=QByteArray::fromHex("cc eb");
        QTimer::singleShot(100, this, [=]()
        {
            m_devicePort.write(writebyte3);
        });
}
void SeriPortManager::presstimer_slot()
{
//    QByteArray writebyte;
//    writebyte = QByteArray::fromHex("");
//    m_devicePort.write(writebyte);
}
