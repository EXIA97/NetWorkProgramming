#include <QCoreApplication>
#include <iostream>
#include <QNetworkAddressEntry>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QHostInfo>
#include <QList>

int main(int argc, char *argv[])
{
    using namespace std;
    QCoreApplication a(argc, argv);


    //QHostInfo类作用，获取主机名，也可以通过主机名来查找IP地址，或者通过IP地址来反向查找主机名。
    QString localHostName = QHostInfo::localHostName();
    cout << "LocalHostName:" << localHostName.toStdString() << endl;

    //获取IP地址
    QHostInfo info = QHostInfo::fromName(localHostName);

    foreach(QHostAddress address, info.addresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
            cout << "IPv4 Address:" << address.toString().toStdString() << endl;
    }

    foreach (QHostAddress address, QNetworkInterface::allAddresses())
    {
        cout << "Address:" << address.toString().toStdString() << endl;
    }

    //获取所有网络接口的列表
    foreach (QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        //设备名
        cout << "Device:" << netInterface.name().toStdString() << endl;

        cout << "HardwareAddress:" << netInterface.hardwareAddress().toStdString() << endl;

        QList<QNetworkAddressEntry> entryList = netInterface.addressEntries();

        foreach(QNetworkAddressEntry entry, entryList)
        {
            //IP地址
            cout << "IP Address:" << entry.ip().toString().toStdString() << endl;

            //子网掩码
            cout << "Netmask:" << entry.netmask().toString().toStdString() << endl;

            //广播地址
            cout << "Broadcast:" << entry.broadcast().toString().toStdString() << endl;
        }

    return a.exec();
    }
}
