#pragma once
#include <QDebug>
#include <QProcess>
#include <QtNetwork>

class Lan
{
public:
    Lan();
    void printHostAddress();
    void printLocalNetworkDevices();
    void networkDevices();
};
