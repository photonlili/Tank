#ifndef QEXCEPTIONWIDGET_H
#define QEXCEPTIONWIDGET_H

#include "qexceptionview.h"
#include "qexceptionmodel.h"

namespace Ui {
class QExceptionWidget;
}

class QExceptionWidget : public QExceptionView
{
    Q_OBJECT

public:
    explicit QExceptionWidget(QWidget *parent = 0);
    ~QExceptionWidget();

private:
    Ui::QExceptionWidget *ui;
    QExceptionModel* m_model;
    QSqlDatabase m_db;
};

#endif // QEXCEPTIONWIDGET_H
