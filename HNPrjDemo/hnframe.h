#ifndef HNFRAME_H
#define HNFRAME_H

#include <QWidget>

namespace Ui {
class HNFrame;
}

class HNFrame : public QWidget
{
    Q_OBJECT

public:
    explicit HNFrame(QWidget *parent = 0);
    ~HNFrame();

private:
    Ui::HNFrame *ui;
};

#endif // HNFRAME_H
