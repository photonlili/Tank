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

signals:
    void signalUpdateLabReport();

public slots:
    void showDebugWindow(int);
private slots:
    void prepareRunning(QString, int);

    void timeNewData();

    void on_btn_open_clicked();

    void on_btn_play_clicked();

    void startHeating();
    void pauseHeating();
    void stopHeating();
    void saveLabReport();
    void on_btn_stop_clicked();

    void on_btn_trans_clicked();

    void on_btn_open_2_clicked();

    void on_btn_play_2_clicked();

    void startHeatingExtract();

    void on_btn_stop_2_clicked();

    void stopHeatingExtract();

    void on_btn_trans_2_clicked();

    void on_btnStir_clicked();

    void on_btn_turn_clicked();

    void on_pushButton_4_clicked();
    void slotException(int);

private:
    Ui::QDispelForm *ui;

    quint8 m_currentStage;
    quint16 m_totalStageRamp;
    double m_initPointKey;
    double m_lastPointKey;

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

    QTimer* timer;

    QMethodForm* methodForm;
    QCPDocumentObject* m_plotObjectHandler;
    QTextEdit* m_text;
    QTankPeerPort* com0;
    QTankSerialPort* s2;
    QDebugWidget* m_debug;
};

#endif // QDISPELFORM_H
