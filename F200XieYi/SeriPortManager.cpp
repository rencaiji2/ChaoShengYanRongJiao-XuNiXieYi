#include "SeriPortManager.h"
#include <QDebug>
#include <QDateTime>
SeriPortManager::SeriPortManager()
{
    initPort();
    m_is = false;
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
    connect(&m_presstimer2,&QTimer::timeout,this,&SeriPortManager::presstimer_slot2,Qt::UniqueConnection);
    //m_handshaketimer.start(1000);
    //m_presstimer2.start(20000);
}

void SeriPortManager::onDeviceDataReady()
{
    QByteArray source = m_devicePort.readAll();
    QByteArray writebyte;
    if(source == QByteArray::fromHex("ea 10 05 ea eb"))
    {
        handshaketimer_slot();
    }
    else
    {
        writebyte = QByteArray::fromHex("ea 02 01 eb");
        writebyte[1] = source.at(1);
//        if(source.at(1) == (char)0x0b)
//        {
//            return;
//            writebyte[2] = (char)0x00;
//        }
        qDebug()<<"writebyte:"<<writebyte<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        m_devicePort.write(writebyte);
    }
}
QByteArray writebyte3=QByteArray::fromHex("ea 01 42 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 05 00 00 00 3c 01 01 00 00 ff ff ff ff 00 00 48 01 01 06 00 00 04 79 4a e8 01 06 00 00 04 79 4a e8 cc eb");
;
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
//        static char capacity_l = (char)0x00;
//        QByteArray writebyte;
//        writebyte = QByteArray::fromHex("ea 01 43 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 05");
//        m_devicePort.write(writebyte);
//        qDebug()<<writebyte.size();
//        QByteArray writebyte2=QByteArray::fromHex("00 00 00 3c 01 01 00 00 ff ff ff ff 00 00 48 01 01 06 00 00 04 79 4a e8 01 06 00 00 04 79 4a e8");
//        if(m_is == true)
//        {
//            m_is = false;
//            writebyte2=QByteArray::fromHex("00 00 00 3c 01 01 00 00 ff ff ff ff 00 00 48 01 01 06 00 00 04 79 4a e8 01 06 00 00 04 79 4a e8");
//        }
//        qDebug()<<"writebyte2.size"<<writebyte2.size();
//        QTimer::singleShot(50, this, [=]()
//            {
//                m_devicePort.write(writebyte2);
//            });
//        QByteArray writebyte3=QByteArray::fromHex("cc eb");
//        QTimer::singleShot(100, this, [=]()
//        {
//            m_devicePort.write(writebyte3);
//        });
    m_devicePort.write(writebyte3);
    writebyte3=QByteArray::fromHex("ea 01 42 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 05 00 00 00 3d 02 02 00 00 ff ff ff ff 00 00 48 01 01 06 00 00 04 79 4a e8 01 06 00 00 04 79 4a e8 cc eb");

}
void SeriPortManager::presstimer_slot()
{
//    QByteArray writebyte;
//    writebyte = QByteArray::fromHex("");
//    m_devicePort.write(writebyte);
}

void SeriPortManager::presstimer_slot2()
{
    writebyte3=QByteArray::fromHex("ea 01 42 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 05 00 00 00 ff 01 03 00 00 ff ff ff ff 00 e1 48 01 01 06 00 00 04 79 4a e8 01 06 00 00 04 79 4a e8 cc eb");

}
