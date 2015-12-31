#ifndef QOPENLIBRARY_H
#define QOPENLIBRARY_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class QOpenLibrary;
}

class QUserLibraryDialog : public QFileDialog
{
    Q_OBJECT

public:
    explicit QUserLibraryDialog(QWidget *parent = 0);
    ~QUserLibraryDialog();

    void initAll();

private:
    Ui::QOpenLibrary *ui;
};

#endif // QOPENLIBRARY_H
