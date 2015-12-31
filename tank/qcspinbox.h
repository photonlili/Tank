#ifndef QCSPINBOX_H
#define QCSPINBOX_H

#include <QWidget>

namespace Ui {
class QCSpinBox;
}

class QCSpinBox : public QWidget
{
    Q_OBJECT

public:
    explicit QCSpinBox(QWidget *parent = 0);
    ~QCSpinBox();
signals:
    void valueChanged(int arg1);

public slots:
    void setRange(int min, int max);
    void setValue(int value);

private slots:
    void on_btn_next_clicked();

    void on_btn_pre_clicked();

    void on_le_value_textChanged(const QString &arg1);

private:
    Ui::QCSpinBox *ui;
    int m_min;
    int m_max;
    int m_value;

    void setText();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // QCSPINBOX_H
