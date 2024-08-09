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
}

void SeriPortManager::onDeviceDataReady()
{
    QByteArray source = m_devicePort.readAll();
    qDebug()<<source;
    QByteArray writebyte;
    if(source == QByteArray::fromHex("ea 10 05 ea eb"))
    {
        qDebug()<<"Send Handshake";
        writebyte = QByteArray::fromHex("ea 01 30 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 3c 01 01 00 00 00 65 19 00 03");
        m_devicePort.write(writebyte);
        writebyte = QByteArray::fromHex("00 8d eb");
        m_devicePort.write(writebyte);
    }
    else
    {
        writebyte = QByteArray::fromHex("ea 02 01 eb");
        writebyte[1] = source.at(1);
        qDebug()<<"writebyte:"<<writebyte;
        m_devicePort.write(writebyte);
    }

}
