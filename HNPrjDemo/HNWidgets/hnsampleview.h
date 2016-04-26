#ifndef HNSAMPLEVIEW_H
#define HNSAMPLEVIEW_H

#include "hntableview.h"

namespace Ui {
class HNSampleView;
}

class HNSampleView : public HNTableView
{
    Q_OBJECT

public:
    explicit HNSampleView(QWidget *parent = 0);
    ~HNSampleView();

private:
    Ui::HNSampleView *ui;
};

#endif // HNSAMPLEVIEW_H
