#include "hnsamplefoundationwidget.h"
#include "ui_hnsamplefoundationwidget.h"
#include "hngui-qt.h"
#include "HNDefine.h"

HNSampleFoundationWidget::HNSampleFoundationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNSampleFoundationWidget)
{
    ui->setupUi(this);
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
    QPrinter printer(QPrinter::HighResolution);
    printer.setColorMode(QPrinter::Color);
    printer.setFullPage(true);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("data.pdf");

#ifdef _MIPS_LINUX_ENV_
    QFontDatabase db;
    int fontId = db.addApplicationFont("/usr/lib/fonts/wenquanyi.ttf");
    QString wenquanyi = db.applicationFontFamilies ( fontId ).at(0);
    QFont font(wenquanyi,11);
#else
    QFontDatabase db;
    int fontId = db.addApplicationFont("/usr/lib/fonts/wenquanyi.ttf");
    QString wenquanyi = db.applicationFontFamilies ( fontId ).at(0);
    QFont font(wenquanyi,11);
#endif

    static QTextEdit* m_text = new QTextEdit(this);
    m_text->clear();
    QTextCursor c = m_text->textCursor();
    QTextCharFormat format;
    format.setFont(font);
    c.setCharFormat(format);
    c.insertTable(1, 5);
    QTextTable* t = c.currentTable();
    m_text->setTextCursor(c);

    m_text->print(&printer);


    QPainter painter;
    painter.setFont(font);
    painter.begin(&printer);

    //QDateTime current_date_time = QDateTime::currentDateTime();
    //QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");

    /*
    QPoint point(10, 10);
    int irow = m_querymodel->rowCount();


    for(int i = 0; i < irow; i++)
    {
        QSqlRecord strRecord= m_querymodel->record(i);
        //QString message = strRecord.value(0).toString();
        QString message = QString("       %1   %2               %3               %4               %5               %6               %7              %8").arg(QString::number(i)).arg(strRecord.value(0).toString()).arg(strRecord.value(1).toString()).arg(strRecord.value(02).toString()).arg(strRecord.value(3).toString()).arg(strRecord.value(4).toString()).arg(strRecord.value(5).toString()).arg(strRecord.value(06).toString());
        int y = point.y();
        point.setY(y + 40);
        painter.drawText(point, message);
        message.clear();
    }

    //printer_text.newPage();  //生成新的一页，可继续插入
    */
    painter.end();
}
