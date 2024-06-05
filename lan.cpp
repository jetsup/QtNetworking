#include "lan.h"

Lan::Lan() {}

void Lan::printHostAddress()
{
    qDebug() << "-------------Q HOST Address-------------";
    for (const QHostAddress &address : QNetworkInterface::allAddresses()) {
        qDebug() << "IP Address: " << address.toString();
        qDebug() << "Link Local: " << address.isLinkLocal();
        qDebug() << "-------------------------------------------------------------";
    }
}

void Lan::printLocalNetworkDevices()
{
    qDebug() << "***************Network Interface***************";
    for (const QNetworkInterface &eth : QNetworkInterface::allInterfaces()) {
        qDebug() << "IName: " << eth.name();
        qDebug() << "MAC A: " << eth.hardwareAddress();
        qDebug() << "IHName: " << eth.humanReadableName();
        qDebug() << "Valid: " << eth.isValid();
        qDebug() << "IType: " << eth.type();
        qDebug() << "TCount: " << eth.maximumTransmissionUnit();
        for (const QNetworkAddressEntry &entity : eth.addressEntries()) {
            qDebug() << "***IpAddr : " << entity.ip();
            qDebug() << "***BdAddr : " << entity.broadcast();
            qDebug() << "***Permnt : " << entity.isPermanent();
            qDebug() << "***NetMsk : " << entity.netmask();
            qDebug() << "\n";
        }
        qDebug() << "***************************************************************************";
    }
}
