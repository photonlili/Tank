#include <QApplication>
#include "HNPub.h"
#include "hnapp.h"
#include "hnwindow.h"
#include "hnmainform.h"

int main(int argc, char *argv[])
{
    HNApp a(argc, argv);

    QWidget w;
    w.setMinimumSize(500, 300);
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
    im->Init("min", "control", "hanon", 14, 14);

    HNLineEditWithSearch w5;
    //l.addWidget(&w5);

    HNCheckBox w6;
    //l.addWidget(&w6);


    HNMainForm w7;
    w7.setFixedSize(HN_SCRN_WIDTH, HN_SCRN_HEIGHT);
    //l.addWidget(&w7);

    HNProgressDialog w9;
    //l.addWidget(&w9);

    HNSampleMutiPageWidget w10;
    //l.addWidget(&w10);

    HNSampleWidget w11;
    w11.setDB(QString("%1/%2").arg(DB_DATA_PATH).arg(DB_DATA));
    w11.setTable(TABLE_YANGPINDATA);
    w11.query();
    //l.addWidget(&w11);

    HNSampleMutiPageWidget w12;
    w12.setDB(QString("%1/%2").arg(DB_DATA_PATH).arg(DB_DATA));
    w12.setTable(TABLE_YANGPINDATA);
    w12.query();
    //l.addWidget(&w12);

    QGraphicsView v;
    HNReporter r;
    QStringList text;
    text << "山东海能仪器股份有限公司";
    text << "页脚写什么？";

    w11.setFixedWidth(700);
    w11.resizeColumnsToContents();
    w11.setFixedWidth(700);
    r.insertSamplePaper("K1160定氮仪结果报告", text, &w11);
    pline() << r.pageNum();
    QGraphicsScene* pageScene = r.getPage(1);
    pageScene->addRect(0,0,pageScene->width(),pageScene->height(),QPen(Qt::black, 2.0));
    v.setScene(pageScene);
    //v.scale(1/1.5, 1/1.5);
    //v.scale(1/1.5, 1/1.5);
    v.show();
    //r.exportPdf("data.pdf");

    HNSampleFoundationWidget w13;
    w13.initAll();
    //l.addWidget(&w13);

    return a.exec();
}
