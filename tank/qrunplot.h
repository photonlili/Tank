#ifndef QRUNPLOT_H
#define QRUNPLOT_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class QRunPlot;
}

class QRunPlot : public QCustomPlot
{
    Q_OBJECT

public:
    explicit QRunPlot(QWidget *parent = 0);
    ~QRunPlot();

    void addTempture(double key, double tempture);
    void addPressure(double key, double pressure);

private:
    Ui::QRunPlot *ui;
    QCPGraph* tempratureGraph;
    QCPGraph* pressGraph;
};

#endif // QRUNPLOT_H
