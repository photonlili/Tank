#ifndef QCLOUDTREEVIEW_H
#define QCLOUDTREEVIEW_H

#include "qctreeview.h"

namespace Ui {
class QCloudTreeView;
}

class QCloudTreeView : public QCTreeView
{
    Q_OBJECT

public:
    explicit QCloudTreeView(QWidget *parent = 0);
    ~QCloudTreeView();

private:
    Ui::QCloudTreeView *ui;
};

#endif // QCLOUDTREEVIEW_H
