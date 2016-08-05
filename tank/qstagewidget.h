#ifndef QSTAGEWIDGET_H
#define QSTAGEWIDGET_H

#include "qstageview.h"
#include "qstagemodel.h"
#include <QDataWidgetMapper>

namespace Ui {
class QStageWidget;
}

class QStageWidget : public QStageView
{
    Q_OBJECT

public:
    explicit QStageWidget(QWidget *parent = 0);
    ~QStageWidget();

    inline QString lastdb() { return m_lastDB; }
    inline void setMethodId(int methodid) { m_methodid = methodid; }
    inline int methodId() { return m_methodid; }
    void refresh(QString filter = "");
    void refresh(int methodid, int type = Type_Temprature);
    void initdb(QString dbName = "", bool save = true);
    void selectStage(int row = 0);
    int currentStage() { return currentIndex().row(); }
    int totalStageTimeRamp();
    int totalStageHold();
    void setRamp(qint16 ramp);
    void setHold(qint16 hold);
    void stageParam(qint8& stage, qint8& vessel,
                    qint16 &ramp, qint16 &press, qint16 &tempture, qint16 &hold);
    void currentStageParam(qint8 &stage, qint8 &vessel, qint16 &ramp, qint16 &press, qint16 &tempture, qint16 &hold);
    int countStage() { return m_model->rowCount(); }
    inline void addMap(QWidget* w, int section) { m_mapper->addMapping(w, section); }

    void openTransaction();
    void rollbackTransaction();
    void commitTransaction();

public slots:
    void newStage();
    void delStage();
    void delAllStage();
    void cleanStage();
    void saveStage(quint8 stage, quint8 vessel, quint16 ramp, quint16 press, quint16 tempture, quint16 hold);
    void prev();
    void next();

private:
    Ui::QStageWidget *ui;
    QSettings *setting;
    QSqlDatabase m_db;
    QString m_lastDB;
    QStageModel* m_model;
    QDataWidgetMapper* m_mapper;
    int m_methodid;
};

#endif // QSTAGEWIDGET_H
