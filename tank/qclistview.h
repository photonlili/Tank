#ifndef QCLISTVIEW_H
#define QCLISTVIEW_H

#include <QListView>

namespace Ui {
class QCListView;
}

class QCListView : public QListView
{
    Q_OBJECT

public:
    explicit QCListView(QWidget *parent = 0);
    ~QCListView();

private:
    Ui::QCListView *ui;
};

#endif // QCLISTVIEW_H
