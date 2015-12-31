#include "qrunplot.h"
#include "ui_qrunplot.h"

QRunPlot::QRunPlot(QWidget *parent) :
    QCustomPlot(parent),
    ui(new Ui::QRunPlot)
{
    ui->setupUi(this);

    tempratureGraph = addGraph(xAxis, yAxis);
    pressGraph = addGraph(xAxis, yAxis2);
    pressGraph->setPen(QPen(Qt::blue));
    tempratureGraph->setPen(QPen(Qt::red));

    xAxis->setTickLabelType(QCPAxis::ltNumber);
    xAxis->setAutoTickStep(false);
    xAxis->setTickStep(1);
    xAxis->setRange(0, 20);
    yAxis->setRange(0, 300);
    yAxis2->setVisible(true);
    yAxis2->setTickLabels(true);
    yAxis2->setRange(0, 800);
    yAxis->setBasePen(QPen(QColor(Qt::red)));
    yAxis->setTickPen(QPen(QColor(Qt::red)));
    yAxis->setSubTickPen(QPen(QColor(Qt::red)));
    yAxis->setTickLabelColor(QColor(Qt::red));
    yAxis2->setBasePen(QPen(QColor(Qt::blue)));
    yAxis2->setTickPen(QPen(QColor(Qt::blue)));
    yAxis2->setSubTickPen(QPen(QColor(Qt::blue)));
    yAxis2->setTickLabelColor(QColor(Qt::blue));
    QPalette plt = ui->labelC->palette();
    plt.setColor(QPalette::WindowText, QColor(Qt::red));
    ui->labelC->setPalette(plt);
    plt = ui->labelPSI->palette();
    plt.setColor(QPalette::WindowText, QColor(Qt::blue));
    ui->labelPSI->setPalette(plt);

    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

QRunPlot::~QRunPlot()
{
    delete ui;
}

void QRunPlot::addTempture(double key, double tempture)
{
    tempratureGraph->addData(key, tempture);
    //tempratureGraph->rescaleValueAxis();
}

void QRunPlot::addPressure(double key, double pressure)
{
    pressGraph->addData(key, pressure);
    //pressGraph->rescaleValueAxis();
}

