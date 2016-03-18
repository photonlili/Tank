#include <QApplication>
#include "qtankclient.h"
#include "qtankapp.h"
#include "qcloudform.h"

int main(int argc, char *argv[])
{
    QTankApp *a = new QTankApp(argc, argv);

    QTankClient* cli = HNSingleClient(a);

    QCloudForm* form = new QCloudForm();
    form->slotConnect();
    form->show();

    return a->exec();
}
