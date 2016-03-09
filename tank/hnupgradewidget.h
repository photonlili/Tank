#ifndef HNUPGRADEWIDGET_H
#define HNUPGRADEWIDGET_H

#include <QWidget>
#include "qtankclient.h"

class QBackupLocalThread : public QThread
{
public:
    explicit QBackupLocalThread(QObject *parent = 0) : QThread(parent){}

    // QThread interface
protected:
    void run();
};

class QUpgradeThread : public QThread
{
public:
    explicit QUpgradeThread(QObject *parent = 0) : QThread(parent){}
    // QThread interface
protected:
    void run();
};

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
    void setText(QString text);
    void setValue(int value);
    void download();
    void downOK();
    void restart();

private:
    Ui::HNUpgradeWidget *ui;
    QTankClient* m_cli;
    QTimer* timer;
    QBackupLocalThread* m_backupT;
    QUpgradeThread* m_upgradeT;
};

#endif // HNUPGRADEWIDGET_H
