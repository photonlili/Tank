#ifndef QSETFORM_H
#define QSETFORM_H

#include <QWidget>
#include <QDateTime>
#include <QLineEdit>
#include "qfactorysetpassform.h"

namespace Ui {
class QSetForm;
}

class QSetForm : public QWidget
{
    Q_OBJECT

public:
    explicit QSetForm(QWidget *parent = 0);
    ~QSetForm();
    void initAll();
    void initLanguage();

signals:
    void changeLanguage();
    void showDebugWindow(int show);

public slots:
    void timerSetTime();
    void slotSerialLock();
    void slotSerialUnlock();

private slots:
    void userRightsChanged(int bChecked);
    void englishPressed(bool bChecked);
    void chinesePressed(bool bChecked);
    void dateTimeChanged(QDateTime dt);
    void currentUserChanged();

    void newUser();
    void delUser();
    void saveUser();

    void netChanged();

    void clickedWIFI();
    void wifiPassDone(QString password);

    void on_scb_bcklight_valueChanged(int value);

    void on_btn_calibrate_clicked();

    void on_btn_saveip_clicked();

    void on_chk_dhcp_stateChanged(int arg1);

private:
    Ui::QSetForm *ui;
    QString wifiPassword;
    QFactorySetPassForm* m_facPass;

    // QObject interface
public:
    bool eventFilter(QObject *obj, QEvent *eve);
};

#endif // QSETFORM_H
