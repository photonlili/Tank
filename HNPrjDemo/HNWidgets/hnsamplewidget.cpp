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
    m_model->setHeaderData(ESampleId, Qt::Horizontal, tr("序号"));
    m_model->setHeaderData(ESampleMingcheng, Qt::Horizontal, tr("样品名称"));
    m_model->setHeaderData(ESampleBianhao, Qt::Horizontal, tr("样品编号"));
    m_model->setHeaderData(ESampleYangpinliang, Qt::Horizontal, tr("样品量"));
    m_model->setHeaderData(ESampleYangpindanwei, Qt::Horizontal, tr("样品量单位"));
    m_model->setHeaderData(ESampleJieguo, Qt::Horizontal, tr("结果"));
    m_model->setHeaderData(ESampleJieguodanwei, Qt::Horizontal, tr("结果单位"));
    m_model->setHeaderData(ESampleCeshiren, Qt::Horizontal, tr("测试人"));
    m_model->setHeaderData(ESampleCeshishijian, Qt::Horizontal, tr("测试时间"));

}

void HNSampleWidget::selectedItems(QVector<QStringList> &ids)
{
    QModelIndexList l = m_model->selectedRows();
    QModelIndex idx;
    foreach (idx, l) {
        QStringList l;
        l << m_model->index(idx.row(), ESampleId).data().toString();
        l << m_model->index(idx.row(), ESampleMingcheng).data().toString();
        l << m_model->index(idx.row(), ESampleBianhao).data().toString();
        l << m_model->index(idx.row(), ESampleYangpinliang).data().toString();
        l << m_model->index(idx.row(), ESampleYangpindanwei).data().toString();
        l << m_model->index(idx.row(), ESampleJieguo).data().toString();
        l << m_model->index(idx.row(), ESampleJieguodanwei).data().toString();
        l << m_model->index(idx.row(), ESampleCeshiren).data().toString();
        l << m_model->index(idx.row(), ESampleCeshishijian).data().toString();
        ids.push_back(l);
    }
}
