#include "hnframe.h"
#include <QApplication>
#include "HNPub.h"

int main(int argc, char *argv[])
{
    HNApp a(argc, argv);

    HNFrame w;
    //w.setFixedHeight(340);
    QVBoxLayout l;
    w.setLayout(&l);
    w.show();

    HNProgressDialog w0;
    HNProgressDialog w1;
    HNProgressDialog w2;
    //l.addWidget(&w0);
    //l.addWidget(&w1);
    //l.addWidget(&w2);

    int value = 100;
    w0.setFixedWidth(800);
    w0.initAll();
    w0.setValue(value);

    w1.setFixedWidth(400);
    w1.initAll();
    w1.setValue(value);

    w2.setFixedWidth(260);
    w2.initAll();
    w2.setValue(value);

    HNCloudWidget w3;
    //l.addWidget(&w3);

    HNManageEthenetWidget w4;
    //l.addWidget(&w4);

    HNInput *im = HNInput::Instance();
    //im->Init("min", "control", "hanon", 14, 14);

    HNLineEditWithSearch w5;
    //l.addWidget(&w5);

    HNCheckBox w6;
    //l.addWidget(&w6);


    HNMainForm w7;
    w7.setFixedSize(HN_SCRN_WIDTH, HN_SCRN_HEIGHT);
    l.addWidget(&w7);

    HNProgressDialog w9;
    //l.addWidget(&w9);

    return a.exec();
}
