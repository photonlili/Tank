#ifndef QDISPELFORM_H
#define QDISPELFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include "qtankdefine.h"
#include "qtankpublic.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QItemSelection>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "qcustomplot.h"
#include "qrunplot.h"
#include "qopenlibrary.h"
#include "qmethodwidget.h"
#include "qmethodform.h"
#include "qcpdocumentobject.h"
#include "qreportviewdialog.h"
#include "qtankpeerport.h"
#include "qdebugwidget.h"
#include "qtankserialport.h"
#include "qtankexception.h"

namespace Ui {
class QDispelForm;
}

class QDispelForm : public QWidget
{
    Q_OBJECT

public:
    explicit QDispelForm(QWidget *parent = 0);
    ~QDispelForm();

    void initAll();
    void initLanguage();

    void startStat();
    void stopStat();

signals:
    void signalUpdateLabReport();
    void signalLockPage(bool block);

public slots:
    void showDebugWindow(int);
private slots:
    void prepareRunning(QString, int, QString name, int type);
    void prepareExtractRunning(QString db, int mid, QString name, int type);


    void timeNewData();
    void timeStatus();
    void slotTankNum(quint8);

    void timeNewData2();

    void startHeating();
    void pauseHeating();
    void continueHeating();
    void stopHeating();
    void slotStat(qint16,qint16,qint8);


    void on_btnStir_clicked();
    void startHeatingExtract();
    void pauseHeatingExtract();
    void continueHeatingExtract();
    void stopHeatingExtract();

    void slotException(quint16);
    void saveLabReport();

    void on_btn_open_clicked();

    void on_btn_play_clicked();

    void on_btn_stop_clicked();

    void on_btn_trans_clicked();
    void on_btn_turn_clicked();

    void on_btn_turn_2_clicked();

    void on_btn_open_2_clicked();

    void on_btn_play_2_clicked();

    void on_btn_stop_2_clicked();

    void on_btn_trans_2_clicked();

    void on_btnStirD_clicked();

    void refreshMethodForm(int mid, int type);
private:
    Ui::QDispelForm *ui;

    QTankException* excp;

    QString serialNo;
    QReportViewDialog* m_dlg;

    QUserLibraryDialog * userlibdialog;
    enum {
        eStop,
        ePause,
        ePlay,
    };
    int bRunning;
    int funcType;
    QTimer* timerStatus;
    qint32 m_testTime;

    QTimer* timer;
    qint8 m_stageIndex;
    qint32 m_totalStageRamp;
    qint32 m_totalStageHold;
    qint32 m_initPointKey;
    qint32 m_lastPointKey;
    qint32 m_pauseTime;
    qint16 m_curRamp;
    qint16 m_curHold;
    qint16 m_curTemprature;
    qint16 m_curPressure;
    qint8  m_workstat;

    QTimer* timer2;
    qint32 m_initPointKey2;
    qint32 m_lastPointKey2;
    qint32 m_totalStageHold2;
    qint32 m_pauseTime2;
    qint16 m_curHold2;

    QMethodForm* methodForm;
    QMethodForm* methodForm2;

    QCPDocumentObject* m_plotObjectHandler;
    QTextEdit* m_text;
    QTankPeerPort* com0;
    QTankSerialPort* s2;
    QDebugWidget* m_debug;

    int m_methodid;
    int m_methodidextract;

    // QObject interface
public:
    bool eventFilter(QObject *, QEvent *);
};

#endif // QDISPELFORM_H
