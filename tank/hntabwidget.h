#ifndef HNTABWIDGET_H
#define HNTABWIDGET_H

#include <QTabWidget>

namespace Ui {
class HNTabWidget;
}

class HNTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit HNTabWidget(QWidget *parent = 0);
    ~HNTabWidget();

    QTabBar* tabBar() { return QTabWidget::tabBar(); }

private:
    Ui::HNTabWidget *ui;
};

#endif // HNTABWIDGET_H
