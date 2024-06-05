#include <QCoreApplication>
#include "lan.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Lan lan;
    lan.printHostAddress();
    lan.printLocalNetworkDevices();

    // return a.exec();
    return 0;
}
