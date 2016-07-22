#ifndef QSETFORM_H
#define QSETFORM_H

#include <QWidget>
#include <QDateTime>
#include <QLineEdit>
#include "qfactorysetpassform.h"
#include "qprogresswindow.h"
#include "qtankpeerport.h"

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
    void sigUpgrade();

public slots:
    void timerSetTime();
    void slotSerialLock();
    void slotSerialUnlock();
    void slotInvokeWarning(QString msg);
    void slotStorageChanged(int stat);
    void slotCalibrate();
    void slotCalibrateAck(quint16,quint16,quint16,quint16);
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

    void on_scb_bcklight_valueChanged(int value);

    void on_btn_calibrate_clicked();

    void on_btn_saveip_clicked();

    void on_chk_dhcp_stateChanged(int arg1);

    void on_btnRestore_clicked();

    void on_btnCalibrate_clicked();

    void on_radioButton_turn0_toggled(bool checked);

    void on_radioButton_turn1_toggled(bool checked);

private:
    Ui::QSetForm *ui;
    QFactorySetPassForm* m_facPass;
    QProgressWindow* prog;
    QTankPeerPort* com0;
    QTimer* timer;

    // QObject interface
public:
    bool eventFilter(QObject *obj, QEvent *eve);
};

#endif // QSETFORM_H
