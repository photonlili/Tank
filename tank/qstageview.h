#ifndef QSTAGEVIEW_H
#define QSTAGEVIEW_H

#include <QTableView>
#include "qctableview.h"

namespace Ui {
class QStageView;
}

class QStageView : public QCTableView
{
    Q_OBJECT

public:
    explicit QStageView(QWidget *parent = 0);
    ~QStageView();

private:
    Ui::QStageView *ui;
};

#endif // QSTAGEVIEW_H
