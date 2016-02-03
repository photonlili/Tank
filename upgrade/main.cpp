#include "hnupgradewidget.h"
#include <QApplication>
#include "qtankclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTankClient* cli = HNSingleClient(&a);

    HNUpgradeWidget w;
    w.show();

    return a.exec();
}
