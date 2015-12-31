#ifndef QEXCEPTIONVIEW_H
#define QEXCEPTIONVIEW_H

#include "qctableview.h"

namespace Ui {
class QExceptionView;
}

class QExceptionView : public QCTableView
{
    Q_OBJECT

public:
    explicit QExceptionView(QWidget *parent = 0);
    ~QExceptionView();

private:
    Ui::QExceptionView *ui;
};

#endif // QEXCEPTIONVIEW_H
