#ifndef HNUPGRADEWIDGET_H
#define HNUPGRADEWIDGET_H

#include <QWidget>
#include "qtankclient.h"

namespace Ui {
class HNUpgradeWidget;
}

class HNUpgradeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNUpgradeWidget(QWidget *parent = 0);
    ~HNUpgradeWidget();

    void initAll();

private slots:
    void download();
    void downOK();
    void backup();
    void restore();

private:
    Ui::HNUpgradeWidget *ui;
    QTankClient* m_cli;
};

#endif // HNUPGRADEWIDGET_H
