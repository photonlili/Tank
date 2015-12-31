#ifndef QSTAGEPLOT_H
#define QSTAGEPLOT_H

#include "qcustomplot.h"
#include "qstagemodel.h"

namespace Ui {
class QStagePlot;
}

class QStagePlot : public QCustomPlot
{
    Q_OBJECT

public:
    explicit QStagePlot(QWidget *parent = 0);
    ~QStagePlot();

    void refresh(int methodid);
    void initdb(QString dbName = "");
private:
    Ui::QStagePlot *ui;
    QStageModel* m_model;
    QSqlDatabase m_db;
    QCPGraph* tempratureGraph;
    QCPGraph* pressGraph;
};

#endif // QSTAGEPLOT_H
