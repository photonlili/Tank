#include "hnframe.h"
#include <QApplication>
#include "HNPub.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HNCloudForm w;
    w.show();

    //HNFrame w;
    //w.show();

    return a.exec();
}
