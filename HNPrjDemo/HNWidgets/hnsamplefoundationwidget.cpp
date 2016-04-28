#include "hnsamplefoundationwidget.h"
#include "ui_hnsamplefoundationwidget.h"
#include "HNDefine.h"
#include "hnsamplewidget.h"
#include "hnmsgbox.h"
#include "hnprinter.h"

HNSampleFoundationWidget::HNSampleFoundationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNSampleFoundationWidget)
{
    ui->setupUi(this);
    reporter = new HNReportEngine(this);
    connect(ui->btnLeft, SIGNAL(clicked()), ui->widgetSampleTable, SLOT(on_btnLeft_clicked()));
    connect(ui->btnRight, SIGNAL(clicked()), ui->widgetSampleTable, SLOT(on_btnRight_clicked()));
    ui->widgetBottom->setFixedHeight(100);
}

HNSampleFoundationWidget::~HNSampleFoundationWidget()
{
    delete ui;
}

void HNSampleFoundationWidget::initAll()
{
    ui->widgetSampleTable->setDB(QString("%1/%2").arg(DB_DATA_PATH).arg(DB_DATA));
    ui->widgetSampleTable->setTable(TABLE_YANGPINDATA);
    ui->widgetSampleTable->query();
}

void HNSampleFoundationWidget::on_btnPrint_clicked()
{
    HNPrinter::print("data.pdf");
    HNMsgBox::warning(this, tr("正在打印，请等待..."));
}

void HNSampleFoundationWidget::on_btnExport_clicked()
{
    QVector<QStringList> lid;
    ui->widgetSampleTable->selectedItems(lid);
    static HNMsgBox* box = new HNMsgBox(this);
    if(lid.size() <= 0)
    {
        box->warning(tr("没有选中的项目"));
        return;
    }
    box->warning(tr("正在导出..."));
    static HNSampleWidget w;
    w.setDB(QString("%1/%2").arg(DB_DATA_PATH).arg(DB_DATA));
    w.setTable(TABLE_YANGPINDATA);
    QString excp;
    for(int i = 0; i < lid.count() - 1; i++)
        excp += QString("id = %1 or ").arg(lid[i].at(ESampleId));
    excp += QString("id = %1").arg(lid.last().at(ESampleId));
    w.query(excp);
    //w.show();
    //w.resizeColumnsToContents();
    w.horizontalHeader()->stretchLastSection();
    w.horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    w.resizeColumnsToContents();
    QStringList text;
    text << "山东海能仪器股份有限公司";
    text << "页脚写什么？";
    reporter->insertSamplePaper("K1160定氮仪结果报告", text, &w);
    reporter->exportPdf("data.pdf");
    system("cp -f data.pdf /mnt/usb_sda1");
    box->warning(tr("导出完成"));
}
