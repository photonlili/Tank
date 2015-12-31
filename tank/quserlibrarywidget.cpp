#include "quserlibrarywidget.h"
#include "ui_quserlibrarywidget.h"

QUserLibraryWidget::QUserLibraryWidget(QWidget *parent) :
    QUserLibraryView(parent),
    ui(new Ui::QUserLibraryWidget)
{
    ui->setupUi(this);
    m_model = new QUserLibraryModel(this, managerDB);
    setModel(m_model);
    m_model->setTable(TABLE_LIBRARY);
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    m_mapper->setModel(m_model);
}

QUserLibraryWidget::~QUserLibraryWidget()
{
    delete ui;
}

void QUserLibraryWidget::refresh(QString filter)
{
    //name != hanon
    m_model->setFilter(filter);
    m_model->select();
    setColumnHidden(Lib_Id, true);
    setColumnHidden(Lib_Creater, true);
    setColumnHidden(Lib_CreateTime, true);
    setColumnHidden(Lib_Comment, true);
}

void QUserLibraryWidget::selectdb(int id)
{
    selectRow(id);
    setFocus(Qt::MouseFocusReason);
    m_mapper->setCurrentIndex(id);
}

void QUserLibraryWidget::selectdb(QString dbname)
{
    if(dbname == currentdb())
    {
        selectdb(currentIndex().row());
        return;
    }

    for(int i = 0; i < m_model->rowCount(); i++)
    {
        if(m_model->record(i).value(Lib_Name).toString() == dbname)
        {
            selectdb(i);
            return;
        }
    }
}

QString QUserLibraryWidget::currentdb()
{
    QModelIndex index = currentIndex();
    return m_model->record(index.row()).value(Lib_Name).toString();
}

QString QUserLibraryWidget::currentDBDisplayed()
{
    QModelIndex index = currentIndex();
    QString text = m_model->record(index.row()).value(Lib_Name).toString();

    QString txt = text;
    if(text == DB_EXTRACT)
        txt = tr("Extract");
    else if(text == DB_HANON)
        txt = tr("System");
    else if(text == DB_USER)
        txt = tr("User");

    return txt;
}

void QUserLibraryWidget::setdbname(QString newName, bool withMapper)
{
    QModelIndex index = currentIndex();
    if(false == withMapper)
    {
        m_model->setData(index, newName);
        m_model->submit();
    }
    else
        m_mapper->submit();

    //xuanzhong
    selectdb(index.row());
}

void QUserLibraryWidget::newDB()
{
    QString name = tr("New Library");

    int count = 0;
    QSqlQuery query(managerDB);
    query.exec(QString("SELECT COUNT(*) FROM %1 WHERE Library like '%%2%'").arg(TABLE_LIBRARY).arg(name));
    if(query.next())
        if(query.value(0).toInt()>0)
            count = query.record().value(0).toInt();
    query.finish();
    if(count > 0)
        name += QString(" (%1)").arg(count);

    int row = 0;
    m_model->insertRow(row);
    m_model->setData(m_model->index(row, Lib_Name), name);
    m_model->setData(m_model->index(row, Lib_Creater), gUserName);
    m_model->setData(m_model->index(row, Lib_CreateTime), gPassword);
    m_model->setData(m_model->index(row, Lib_Comment), "");
    m_model->submit();

    QSqlDatabase idb = newDatabaseConn();
    setDatabaseName(idb, QString("Method/%1").arg(name));
    QSqlQuery iquery(idb);
    iquery.exec(QString("CREATE TABLE Method ( id  INTEGER NOT NULL, M_Name  TEXT, Type  INTEGER, PRIMARY KEY (id) )"));
    iquery.exec(QString("CREATE TABLE Stage (id  INTEGER NOT NULL, Stage  INTEGER, Vessel  INTEGER, TimeRAMP  INTEGER, PressPSI  INTEGER, Tempture  INTEGER, Hold  INTEGER, M_Id  INTEGER, PRIMARY KEY (id ASC), CONSTRAINT fkey0 FOREIGN KEY (M_Id) REFERENCES Method (id) )"));
    iquery.exec(QString("INSERT INTO Method VALUES (1, 'New Method (0)', 0)"));
    iquery.exec(QString("INSERT INTO Stage VALUES (1, 1, 12, 600, 500, 800, 600, 1)"));
    iquery.finish();
    closeDatabase(idb);

    //初始化完成表格之后，选中db，激发changed消息，method和stage初始化才会成功。
    selectdb(name);
}

void QUserLibraryWidget::delDB()
{
    QString curdb = currentdb();
    QModelIndex index = currentIndex();
    m_model->removeRow(index.row());
    m_model->submit();
    selectdb(index.row()-1);
    QFile::remove(QString("%1/%2.db").arg(DB_METHOD).arg(curdb));
}

void QUserLibraryWidget::prev()
{
    selectRow(currentIndex().row()-1);
    setFocus(Qt::MouseFocusReason);
}

void QUserLibraryWidget::next()
{
    selectRow(currentIndex().row()+1);
    setFocus(Qt::MouseFocusReason);
}

