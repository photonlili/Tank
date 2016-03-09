#include "hnupgradewidget.h"
#include <QApplication>
#include "qtankclient.h"
#include "qtankapp.h"

int main(int argc, char *argv[])
{
    QTankApp *a = new QTankApp(argc, argv);

    QTankClient* cli = HNSingleClient(a);

    HNUpgradeWidget w;
    w.show();
    w.initAll();

    return a->exec();
}
