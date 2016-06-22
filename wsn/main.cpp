#include "wsndialog.h"
#include <QApplication>
#include "hnapp.h"
#include "hngui-qt.h"
#include "version.h"
#include "HNDefine.h"

int main(int argc, char *argv[])
{
    HNApp a(argc, argv);

    QWidget w0;
    w0.show();
    w0.setFixedSize(1024, 768);

    WSNDialog w(&w0);
    w.show();
    moveCenter(&w);

    return a.exec();
}
