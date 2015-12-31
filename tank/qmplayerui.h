#ifndef QMPLAYERUI_H
#define QMPLAYERUI_H

#include <QWidget>
#include <QProcess>
#include <QTimer>
#include "qmplayermodel.h"

namespace Ui {
class QMPlayerUI;
}

class QMPlayerUI : public QWidget
{
    Q_OBJECT

public:
    explicit QMPlayerUI(QWidget *parent = 0);
    ~QMPlayerUI();

private slots:
    void on_toolButton_mute_clicked();

    void posChanged();

    void on_btn_play_clicked();

    void on_btn_stop_clicked();

    void on_sliderVol_valueChanged(int value);

private:
    Ui::QMPlayerUI *ui;
    QMPlayerModel* app;
    QTimer* timer;
    quint8 m_bplayed;
};

#endif // QMPLAYERUI_H
