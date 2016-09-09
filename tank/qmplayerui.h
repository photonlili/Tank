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

    void stop()
    {
        on_btn_stop_clicked();
    }

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
    int m_startPos;
    int m_vol;
};

#endif // QMPLAYERUI_H
