#ifndef QCTABLEVIEW_H
#define QCTABLEVIEW_H

#include <QTableView>
#include "qcheaderview.h"

namespace Ui {
class QCTableView;
}

class QCTableView : public QTableView
{
    Q_OBJECT

public:
    explicit QCTableView(QWidget *parent = 0);
    ~QCTableView();

    QCHeaderView* chorizontalHeader() { return m_header; }
    QCHeaderView* cverticalHeader() { return m_vheader; }

    void setObjectName(const QString &name);
private:
    Ui::QCTableView *ui;

    QCHeaderView* m_vheader;
    QCHeaderView* m_header;
};

#endif // QCTABLEVIEW_H
