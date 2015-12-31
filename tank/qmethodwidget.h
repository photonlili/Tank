#ifndef QMETHODWIDGET_H
#define QMETHODWIDGET_H

#include "qmethodview.h"
#include "qtankgui.h"
#include "qmethodmodel.h"
#include <QDataWidgetMapper>

namespace Ui {
class QMethodWidget;
}

class QMethodWidget : public QMethodView
{
    Q_OBJECT

public:
    explicit QMethodWidget(QWidget *parent = 0);
    ~QMethodWidget();

    inline QString lastdb() { return m_lastDB; }
    void selectMethod(int row = 0);
    void initdb(QString dbName = "", bool save = true);
    void initAll(QString db, bool save);
    void refresh(QString filter = "");
    inline int currentMethodId() { return m_model->record(currentIndex().row()).value(Method_Id).toInt(); }
    inline QString currentMethodName(){return m_model->record(currentIndex().row()).value(Method_Name).toString();}
    inline QString currentMethodVessel(){return m_model->record(currentIndex().row()).value(Method_Vessel).toString();}
    inline int currentMethodType(){return m_model->record(currentIndex().row()).value(Method_Type).toInt();}
    inline void addMap(QWidget* w, int section) { m_mapper->addMapping(w, section); }

    void openTransaction();
    void rollbackTransaction();
    void commitTransaction();
    void newMethod();
    void delMethod(int row = 0);
    void setMethodName(int row, QString name);
    void setMethodVessel(int row, int vessel);
    void setMethodType(int row, int type);

public slots:

    void prev();

    void next();

private:
    Ui::QMethodWidget *ui;
    QSettings *setting;
    QSqlDatabase m_db;
    QString m_lastDB;
    QMethodModel* m_model;
    QDataWidgetMapper* m_mapper;
};

#endif // QMETHODWIDGET_H
