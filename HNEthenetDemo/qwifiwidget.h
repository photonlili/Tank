#ifndef QWIFIWIDGET_H
#define QWIFIWIDGET_H

#include "qwifiview.h"
#include "qwifimodel.h"
#include "qtankgui.h"
#include "qwifipassform.h"

namespace Ui {
class QWIFIWidget;
}

class QWIFIWidget : public QWIFIView
{
    Q_OBJECT

public:
    explicit QWIFIWidget(QWidget *parent = 0);
    ~QWIFIWidget();

private slots:
    void clickWIFI();

private:
    Ui::QWIFIWidget *ui;
    QWIFIModel* m_model;
    QWIFIPassForm* m_pass;
};

#endif // QWIFIWIDGET_H
