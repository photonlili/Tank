#include "qmethodwidget.h"
#include "ui_qmethodwidget.h"

QMethodWidget::QMethodWidget(QWidget *parent) :
    QMethodView(parent),
    ui(new Ui::QMethodWidget)
{
    ui->setupUi(this);
    setting = new QSettings(QApplication::organizationName(), QApplication::applicationName(), this);
    m_db = newDatabaseConn();
    m_model = new QMethodModel(this, m_db);
    setModel(m_model);
    //m_mapper = new QDataWidgetMapper(this);
    //m_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    //m_mapper->setModel(m_model);
    //m_mapper->setItemDelegate(new QSqlRelationalDelegate(this));

    //connect(this->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), m_mapper, SLOT(setCurrentModelIndex(QModelIndex)));
    setItemDelegate(new QSqlRelationalDelegate(this));
}

QMethodWidget::~QMethodWidget()
{
    delete ui;
}

void QMethodWidget::selectMethod(int row)
{
    selectRow(row);
    setFocus(Qt::MouseFocusReason);
    //m_mapper->setCurrentIndex(row);
}

void QMethodWidget::refresh(QString filter)
{
    m_model->setFilter(filter);
    m_model->select();
    setColumnHidden(Method_Id, true);
    setColumnHidden(Method_Type, true);
    setColumnHidden(Method_Vessel, true);
}

void QMethodWidget::initdb(QString dbName, bool save)
{
    m_lastDB = setting->value(QString("%1/lastDB").arg(gUserName), gUserName).toString();
    //pline() << "predb" << gUserName << m_lastDB << "open" << m_db.isOpen();
    if(!dbName.isEmpty())
        m_lastDB = dbName;
    setDatabaseName(m_db, QString("Method/%1").arg(m_lastDB));
    //pline() << "curdb" << gUserName << m_lastDB << "open" << m_db.isOpen();
    m_model->setTable(TABLE_METHOD);
    if(!save)
        return;
    setting->setValue(QString("%1/lastDB").arg(gUserName), m_lastDB);
    setting->sync();
}

void QMethodWidget::openTransaction()
{
    m_db.transaction();
}

void QMethodWidget::rollbackTransaction()
{
    m_db.rollback();
}

void QMethodWidget::commitTransaction()
{
    m_db.commit();
}

void QMethodWidget::newMethod()
{
    int count = 0;

    QSqlQuery query(m_db);
    query.exec(QString("SELECT COUNT(*) FROM Method WHERE M_Name like '%%1%'").arg(tr("New Method")));
    if(query.next())
        if(query.record().value(0).toInt()>0)
            count = query.record().value(0).toInt();
    query.finish();

    QString name = tr("New Method (%1)").arg(count);

    int type = Type_Standard;
    int row = m_model->rowCount();
    m_model->insertRow(row);
    m_model->setData(m_model->index(row, Method_Name), name);
    m_model->setData(m_model->index(row, Method_Type), type);
    m_model->setData(m_model->index(row, Method_Vessel), 12);
    m_model->submit();

    selectMethod(row);
}

void QMethodWidget::delMethod(int row)
{
    m_model->removeRow(row);
    m_model->submit();
}

void QMethodWidget::setMethodName(int row, QString name)
{
    m_model->setData(m_model->index(row, Method_Name), name);
    m_model->submit();
    //selectMethod(row);
}

void QMethodWidget::setMethodVessel(int row, int vessel)
{
    m_model->setData(m_model->index(row, Method_Vessel), vessel);
    m_model->submit();
    //selectMethod(row);
}

void QMethodWidget::setMethodType(int row, int type)
{
    m_model->setData(m_model->index(row, Method_Type), type);
    m_model->submit();
    //selectMethod(row);
}

void QMethodWidget::prev()
{
    selectMethod(currentIndex().row()-1);
}

void QMethodWidget::next()
{
    selectMethod(currentIndex().row()+1);
}

void QMethodWidget::initAll(QString db, bool save)
{
    initdb(db, save);
    refresh();
    selectMethod();
}
