#ifndef QUSERFORM_H
#define QUSERFORM_H

#include <QWidget>

namespace Ui {
class QUserForm;
}

class QUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit QUserForm(QWidget *parent = 0);
    ~QUserForm();

    void initAll();
    void initLanguage();

signals:
    void signalLogout();
    void setTheme();
    void setPic();

public slots:
    void themeToggled(bool bChecked);
    void theme1Toggled(bool bChecked);
    void theme2Toggled(bool bChecked);
    void theme3Toggled(bool bChecked);
    void userPicToggled(bool bChecked);
    void user1PicToggled(bool bChecked);
    void user2PicToggled(bool bChecked);
    void user3PicToggled(bool bChecked);

private slots:
    void on_btn_saveuser_clicked();

private:
    Ui::QUserForm *ui;
};

#endif // QUSERFORM_H
