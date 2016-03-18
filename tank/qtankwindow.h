#ifndef QTANKWINDOW_H
#define QTANKWINDOW_H

#include <QStackedWidget>

namespace Ui {
class QTankWindow;
}

class QTankWindow : public QStackedWidget
{
    Q_OBJECT

public:
    explicit QTankWindow(QWidget *parent = 0);
    ~QTankWindow();

signals:
    void changeLanguage();

public slots:
    void slotLogout();
    void slotSerialLock();
    void slotSerialUnLock();
    void slotUpgrade();
    void slotCancelUpgrade();

private slots:
    void slotStatus(int index);

private:
    Ui::QTankWindow *ui;
};

#endif // QTANKWINDOW_H
