#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QSqlTableModel>
#include "qwifimanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initAll();

signals:
    void signalLogout();
    void changeLanguage();

public slots:
    void slotSerialLocked();
    void slotSerialUnlocked();
    void initFont(){};
    void initLanuage();
    void initTheme();
    void initPic();
    void wifiConnected();
    void wifiDisConnected();
    void wifiConnecting();

private slots:
    void timerSetTime();

private:
    Ui::MainWindow *ui;
    QTimer * timer;
};

#endif // MAINWINDOW_H
