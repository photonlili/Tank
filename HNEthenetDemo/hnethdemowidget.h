#ifndef HNETHDEMOWIDGET_H
#define HNETHDEMOWIDGET_H

#include <QWidget>

namespace Ui {
class HNEthDemoWidget;
}

class HNEthDemoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNEthDemoWidget(QWidget *parent = 0);
    ~HNEthDemoWidget();

private slots:
    void netChanged();
    void wifiConnected();
    void wifiDisConnected();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::HNEthDemoWidget *ui;
};

#endif // HNETHDEMOWIDGET_H
