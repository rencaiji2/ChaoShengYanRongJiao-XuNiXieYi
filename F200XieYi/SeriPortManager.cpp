#include "SeriPortManager.h"

SeriPortManager::SeriPortManager()
{
    initPort();
}

void SeriPortManager::initPort()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())//搜索串口，获取串口列表
    {
         if(info.portName()=="COM3")
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
    QByteArray writebyte = QByteArray::fromHex("ea 01 30 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 3c 01 01 00 00 00 65 19 00 03 00 8d eb");
    m_devicePort.write(writebyte);
}
