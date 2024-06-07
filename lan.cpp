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

void pingDevice(const QString &ipAddress)
{
    QProcess process;
    process.start("ping",
                  QStringList() << "-c"
                                << "1" << ipAddress);
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    if (output.contains("bytes from")) {
        qDebug() << "Device found at IP:" << ipAddress;
    }
}

void Lan::networkDevices()
{
    QProcess process;
    process.start("arp", QStringList() << "-n");
    process.waitForFinished();

    if (process.exitStatus() == QProcess::NormalExit) {
        QString output = process.readAllStandardOutput();
        // https://regexr.com/
        QRegularExpression re("(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})\\s+\\S+\\s+([0-9a-fA-f]{"
                              "2}(?::[0-9a-fA-F]{2}){5})\\s+\\S\\s+(\\S+)");

        QRegularExpressionMatchIterator matches = re.globalMatch(output);

        while (matches.hasNext()) {
            QRegularExpressionMatch match = matches.next();

            if (match.hasMatch()) {
                QString ipAddress = match.captured(1);
                QString macAddress = match.captured(2);
                QString iface = match.captured(3);

                qDebug() << "IP Address:" << ipAddress << ", MAC Address:" << macAddress
                         << ", Interface:" << iface;
            }
        }

    } else {
        qDebug() << "arp command not found. Network scanning might not work.";
    }
}
