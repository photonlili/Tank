#include "qstagewidget.h"
#include "ui_qstagewidget.h"

QStageWidget::QStageWidget(QWidget *parent) :
    QStageView(parent),
    ui(new Ui::QStageWidget)
{
    ui->setupUi(this);
    setting = new QSettings(QApplication::organizationName(), QApplication::applicationName(), this);
    m_db = newDatabaseConn();
    m_model = new QStageModel(this, m_db);
    setModel(m_model);
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    m_mapper->setModel(m_model);
    m_mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    connect(this->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), m_mapper, SLOT(setCurrentModelIndex(QModelIndex)));
}

QStageWidget::~QStageWidget()
{
    delete ui;
}

void QStageWidget::refresh(QString filter)
{
    m_model->setFilter(filter);
    m_model->select();
    setColumnHidden(Stage_Id, true);
    setColumnHidden(Stage_MethodId, true);
    m_model->setHeaderData(Stage_Index, Qt::Horizontal, tr("Stage"));
    m_model->setHeaderData(Stage_Vessel, Qt::Horizontal, tr("Vessel"));
    m_model->setHeaderData(Stage_Timeramp, Qt::Horizontal, tr("TimeRAMP"));
    m_model->setHeaderData(Stage_Presspsi, Qt::Horizontal, tr("PressPSI"));
    m_model->setHeaderData(Stage_Tempture, Qt::Horizontal, tr("Tempture"));
    m_model->setHeaderData(Stage_Hold, Qt::Horizontal, tr("Hold"));
}

void QStageWidget::refresh(int methodid)
{
    m_model->setFilter(QString("M_Id = %1").arg(methodid));
    m_model->select();
    setColumnHidden(Stage_Id, true);
    setColumnHidden(Stage_MethodId, true);
    m_model->setHeaderData(Stage_Index, Qt::Horizontal, tr("Stage"));
    m_model->setHeaderData(Stage_Vessel, Qt::Horizontal, tr("Vessel"));
    m_model->setHeaderData(Stage_Timeramp, Qt::Horizontal, tr("TimeRAMP"));
    m_model->setHeaderData(Stage_Presspsi, Qt::Horizontal, tr("PressPSI"));
    m_model->setHeaderData(Stage_Tempture, Qt::Horizontal, tr("Tempture"));
    m_model->setHeaderData(Stage_Hold, Qt::Horizontal, tr("Hold"));
}

void QStageWidget::initdb(QString dbName, bool save)
{
    m_lastDB = setting->value(QString("%1/lastDB").arg(gUserName), gUserName).toString();
    //pline() << "predb" << gUserName << m_lastDB << "opened" << m_db.isOpen();
    if(!dbName.isEmpty())
        m_lastDB = dbName;
    setDatabaseName(m_db, QString("Method/%1").arg(m_lastDB));
    m_model->setTable(TABLE_STAGE);
    //pline() << "curdb" << gUserName << m_lastDB << "opened" << m_db.isOpen();
    if(!save)
        return;
    setting->setValue(QString("%1/lastDB").arg(gUserName), m_lastDB);
    setting->sync();
}

void QStageWidget::selectStage(int row)
{
    selectRow(row);
    setFocus(Qt::MouseFocusReason);
    //m_mapper->setCurrentIndex(row);
}

void QStageWidget::currentStageParam(quint8 &stage, quint8 &vessel, quint16 &ramp, quint16 &press, quint16 &tempture, quint16 &hold)
{
    QModelIndex index = currentIndex();
    stage = m_model->index(index.row(), Stage_Index).data().toUInt();
    vessel = m_model->index(index.row(), Stage_Vessel).data().toUInt();
    ramp = m_model->index(index.row(), Stage_Timeramp).data().toUInt();
    press = m_model->index(index.row(), Stage_Presspsi).data().toUInt();
    tempture = m_model->index(index.row(), Stage_Tempture).data().toUInt();
    hold = m_model->index(index.row(), Stage_Hold).data().toUInt();
}

void QStageWidget::openTransaction()
{
    m_db.transaction();
}

void QStageWidget::rollbackTransaction()
{
    m_db.rollback();
}

void QStageWidget::commitTransaction()
{
    m_db.commit();
}

void QStageWidget::newStage()
{
    int row = 0;
    row = m_model->rowCount();
    m_model->insertRow(row);
    m_model->setData(m_model->index(row, Stage_Index), row+1);
    m_model->setData(m_model->index(row, Stage_Vessel), 20);
    m_model->setData(m_model->index(row, Stage_Timeramp), 5);
    m_model->setData(m_model->index(row, Stage_Presspsi), 500);
    m_model->setData(m_model->index(row, Stage_Tempture), 200);
    m_model->setData(m_model->index(row, Stage_Hold), 5);
    m_model->setData(m_model->index(row, Stage_MethodId), m_methodid);
    m_model->submit();
}

void QStageWidget::delStage()
{
    int row = 0;
    row = m_model->rowCount();

    if(row <= 1)
        return;

    m_model->removeRow(row-1);
    m_model->submit();
}

void QStageWidget::delAllStage()
{
    int row = 0;
    row  = m_model->rowCount();

    m_model->removeRows(0, row);
    m_model->submit();
}

void QStageWidget::cleanStage()
{
    int row = 0;

    m_model->setData(m_model->index(row, Stage_Index), row+1);
    m_model->setData(m_model->index(row, Stage_Vessel), 20);
    m_model->setData(m_model->index(row, Stage_Timeramp), 5);
    m_model->setData(m_model->index(row, Stage_Presspsi), 500);
    m_model->setData(m_model->index(row, Stage_Tempture), 200);
    m_model->setData(m_model->index(row, Stage_Hold), 5);
    m_model->setData(m_model->index(row, Stage_MethodId), m_methodid);

    row  = m_model->rowCount();
    m_model->removeRows(1, row);
    m_model->submit();
}

void QStageWidget::saveStage()
{
    int row = currentIndex().row();
    m_mapper->submit();
    selectStage(row);
}

void QStageWidget::prev()
{
    selectRow(currentIndex().row()-1);
    setFocus(Qt::MouseFocusReason);
}

void QStageWidget::next()
{
    selectRow(currentIndex().row()+1);
    setFocus(Qt::MouseFocusReason);
}
