#ifndef QEXCEPTIONWIDGET_H
#define QEXCEPTIONWIDGET_H

#include "hnexceptionview.h"
#include "hnexceptionmodel.h"

namespace Ui {
class QExceptionWidget;
}

class QExceptionWidget : public HNExceptionView
{
    Q_OBJECT

public:
    explicit QExceptionWidget(QWidget *parent = 0);
    ~QExceptionWidget();

private:
    Ui::QExceptionWidget *ui;
    HNExceptionModel* m_model;
    QSqlDatabase m_db;
};

#endif // QEXCEPTIONWIDGET_H
