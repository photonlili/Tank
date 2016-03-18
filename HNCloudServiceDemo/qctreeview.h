#ifndef QCTREEVIEW_H
#define QCTREEVIEW_H

#include <QTreeView>

namespace Ui {
class QCTreeView;
}

class QCTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit QCTreeView(QWidget *parent = 0);
    ~QCTreeView();

private:
    Ui::QCTreeView *ui;
};

#endif // QCTREEVIEW_H
