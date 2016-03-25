#ifndef HNTREEVIEW_H
#define HNTREEVIEW_H

#include <QTreeView>

namespace Ui {
class HNTreeView;
}

class HNTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit HNTreeView(QWidget *parent = 0);
    ~HNTreeView();

private:
    Ui::HNTreeView *ui;
};

#endif // HNTREEVIEW_H
