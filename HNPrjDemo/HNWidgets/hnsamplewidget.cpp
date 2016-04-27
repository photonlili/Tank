#include "hnsamplewidget.h"
#include "ui_hnsamplewidget.h"
#include "HNDefine.h"
#include "hngui-qt.h"

HNSampleWidget::HNSampleWidget(QWidget *parent) :
    HNSampleView(parent),
    ui(new Ui::HNSampleWidget)
{
    ui->setupUi(this);
    m_db = newDatabaseConn();
    m_model = new HNSampleModel(this, m_db);
    setModel(m_model);
    setItemDelegate(new QSqlRelationalDelegate(this));
}

HNSampleWidget::~HNSampleWidget()
{
    delete ui;
}

void HNSampleWidget::setDB(QString db)
{
    //setDatabaseName(m_db, QString("%1/%2").arg(DB_DATA_PATH).arg(DB_DATA));
    setDatabaseName(m_db, db);
}

void HNSampleWidget::setTable(QString table)
{
    //m_model->setTable(TABLE_YANGPINDATA);
    //m_model->setRelation(Event_Name, QSqlRelation(TABLE_EVTYPE, "id", "Type"));
    m_model->setTable(table);
}

void HNSampleWidget::query(QString excp)
{
    m_model->setFilter(excp);
    m_model->select();
    m_model->setHeaderData(0, Qt::Horizontal, tr("序号"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("样品名称"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("样品编号"));
    m_model->setHeaderData(3, Qt::Horizontal, tr("样品量"));
    m_model->setHeaderData(4, Qt::Horizontal, tr("结果"));
    m_model->setHeaderData(5, Qt::Horizontal, tr("结果单位"));
    m_model->setHeaderData(6, Qt::Horizontal, tr("测试人"));
    m_model->setHeaderData(7, Qt::Horizontal, tr("测试时间"));
}
