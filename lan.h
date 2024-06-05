#pragma once
#include <QDebug>
#include <QtNetwork>

class Lan
{
public:
    Lan();
    void printHostAddress();
    void printLocalNetworkDevices();
};
