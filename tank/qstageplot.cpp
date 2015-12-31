#include "qstageplot.h"
#include "ui_qstageplot.h"

QStagePlot::QStagePlot(QWidget *parent) :
    QCustomPlot(parent),
    ui(new Ui::QStagePlot)
{
    ui->setupUi(this);

    m_db = newDatabaseConn();
    m_model = new QStageModel(this, m_db);

    tempratureGraph = addGraph(xAxis, yAxis);
    pressGraph = addGraph(xAxis, yAxis2);
    pressGraph->setPen(QPen(Qt::blue));
    tempratureGraph->setPen(QPen(Qt::red));

    xAxis->setTickLabelType(QCPAxis::ltNumber);
    xAxis->setAutoTickStep(false);
    xAxis->setTickStep(5);
    xAxis->setRange(0, 30);
    yAxis->setRange(0, 300);
    yAxis2->setVisible(true);
    yAxis2->setTickLabels(true);
    yAxis2->setRange(0, 1500);
}

QStagePlot::~QStagePlot()
{
    delete ui;
}

void QStagePlot::refresh(int methodid)
{
    m_model->setFilter(QString("M_Id = '%1'").arg(methodid));
    m_model->select();

    tempratureGraph->clearData();
    pressGraph->clearData();

    tempratureGraph->addData(0, 0);
    pressGraph->addData(0, 0);

    double key = 0;
    for(int i = 0; i < m_model->rowCount(); i++)
    {

        key += m_model->record(i).value(Stage_Timeramp).toDouble();
        double tempture = m_model->record(i).value(Stage_Tempture).toDouble();
        double pressure = m_model->record(i).value(Stage_Presspsi).toDouble();

        tempratureGraph->addData(key, tempture);
        pressGraph->addData(key, pressure);

        //tempratureGraph->rescaleValueAxis();
        //pressGraph->rescaleValueAxis();

        key += m_model->record(i).value(Stage_Hold).toDouble();

        tempratureGraph->addData(key, tempture);
        pressGraph->addData(key, pressure);

        //tempratureGraph->rescaleValueAxis();
        //pressGraph->rescaleValueAxis();

        replot();
    }
}

void QStagePlot::initdb(QString dbName)
{
    if(dbName.isEmpty())
        return;
    setDatabaseName(m_db, QString("Method/%1").arg(dbName));
    m_model->setTable(TABLE_STAGE);
}

