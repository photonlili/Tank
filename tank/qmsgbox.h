#ifndef QMSGBOX_H
#define QMSGBOX_H

#include <QMessageBox>

namespace Ui {
class QMsgBox;
}

class QMsgBox : public QMessageBox
{
    Q_OBJECT

public:
    explicit QMsgBox(QWidget *parent = 0);
    ~QMsgBox();

    static StandardButton warning(QWidget *parent, const QString &title,
         const QString &text, StandardButtons buttons = Ok,
         StandardButton defaultButton = NoButton);

private:
    Ui::QMsgBox *ui;
};

#endif // QMSGBOX_H
