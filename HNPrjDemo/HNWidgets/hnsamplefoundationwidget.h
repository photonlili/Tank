#ifndef HNSAMPLEFOUNDATIONWIDGET_H
#define HNSAMPLEFOUNDATIONWIDGET_H

#include <QWidget>
#include "hnreporter.h"

namespace Ui {
class HNSampleFoundationWidget;
}

class HNSampleFoundationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNSampleFoundationWidget(QWidget *parent = 0);
    ~HNSampleFoundationWidget();

public slots:
    void initAll();

private slots:
    void on_btnPrint_clicked();

    void on_btnExport_clicked();

private:
    Ui::HNSampleFoundationWidget *ui;
    HNReportEngine* reporter;
};

#endif // HNSAMPLEFOUNDATIONWIDGET_H
