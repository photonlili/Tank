#include "hnframe.h"
#include <QApplication>
#include "HNPub.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HNProgressDialog w;
    HNProgressDialog w1;
    HNProgressDialog w2;
    HNFrame w0;
    //w0.setFixedHeight(600);
    QVBoxLayout l;
    //l.addWidget(&w);
    //l.addWidget(&w1);
    //l.addWidget(&w2);
    w0.setLayout(&l);
    w0.show();

    int value = 70;
    w.setFixedWidth(800);
    w.initAll();
    w.setValue(value);

    w1.setFixedWidth(400);
    w1.initAll();
    w1.setValue(value);

    w2.setFixedWidth(600);
    w2.initAll();
    w2.setValue(value);

    HNCloudWidget w3;
    l.addWidget(&w3);

    return a.exec();
}
