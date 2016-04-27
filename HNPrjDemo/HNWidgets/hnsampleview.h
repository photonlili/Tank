#ifndef HNSAMPLEVIEW_H
#define HNSAMPLEVIEW_H

#include <QTableView>

namespace Ui {
class HNSampleView;
}

class HNSampleView : public QTableView
{
    Q_OBJECT

public:
    explicit HNSampleView(QWidget *parent = 0);
    ~HNSampleView();

private:
    Ui::HNSampleView *ui;
};

#endif // HNSAMPLEVIEW_H
