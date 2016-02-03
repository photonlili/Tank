#ifndef HNUPGRADEWIDGET_H
#define HNUPGRADEWIDGET_H

#include <QWidget>

namespace Ui {
class HNUpgradeWidget;
}

class HNUpgradeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNUpgradeWidget(QWidget *parent = 0);
    ~HNUpgradeWidget();

private:
    Ui::HNUpgradeWidget *ui;
};

#endif // HNUPGRADEWIDGET_H
