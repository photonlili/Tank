#include "wsndialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WSNDialog w;
    w.show();

    return a.exec();
}
