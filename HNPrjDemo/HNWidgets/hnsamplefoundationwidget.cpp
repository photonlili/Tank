#include "hnsamplefoundationwidget.h"
#include "ui_hnsamplefoundationwidget.h"
#include "HNDefine.h"


HNSampleFoundationWidget::HNSampleFoundationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNSampleFoundationWidget)
{
    ui->setupUi(this);
    reporter = new HNReporter(this);
    connect(ui->btnLeft, SIGNAL(clicked()), ui->widgetSampleTable, SLOT(on_btnLeft_clicked()));
    connect(ui->btnRight, SIGNAL(clicked()), ui->widgetSampleTable, SLOT(on_btnRight_clicked()));
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

}

void HNSampleFoundationWidget::on_btnExport_clicked()
{
    QStringList text;
    text << "山东海能仪器股份有限公司";
    text << "页脚写什么？";
    //reporter->insertSamplePaper("K1160定氮仪结果报告", text, ui->widgetSampleTable);
    reporter->exportPdf("data.pdf");
    system("cp -f data.pdf /mnt/usb_sda1");
}
