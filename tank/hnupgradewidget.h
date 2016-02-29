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

signals:
    void sigBackup();
    void sigDownload();
    void sigRestore();

private slots:
    void backup();
    void download();
    void downOK();
    void restore();
    void restart();

private:
    Ui::HNUpgradeWidget *ui;
    QTankClient* m_cli;
    QTimer* timer;
};

#endif // HNUPGRADEWIDGET_H
