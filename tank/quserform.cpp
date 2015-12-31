#include "quserform.h"
#include "ui_quserform.h"
#include <QSettings>
#include "qtankpublic.h"
#include "qmsgbox.h"
#include "qtankdefine.h"
#include "qtankgui.h"
#include "hnmsgbox.h"

QUserForm::QUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QUserForm)
{
    ui->setupUi(this);

    ui->le_confirmpwd->setEchoMode(QLineEdit::Password);
    ui->le_newpwd->setEchoMode(QLineEdit::Password);
    ui->le_oldpwd->setEchoMode(QLineEdit::Password);

    connect(ui->radioButton_theme, SIGNAL(toggled(bool)), this, SLOT(themeToggled(bool)));
    connect(ui->radioButton_theme1, SIGNAL(toggled(bool)), this, SLOT(theme1Toggled(bool)));
    connect(ui->radioButton_theme2, SIGNAL(toggled(bool)), this, SLOT(theme2Toggled(bool)));
    connect(ui->radioButton_theme3, SIGNAL(toggled(bool)), this, SLOT(theme3Toggled(bool)));
    connect(ui->radioButton_userpic, SIGNAL(toggled(bool)), this, SLOT(userPicToggled(bool)));
    connect(ui->radioButton_user1pic, SIGNAL(toggled(bool)), this, SLOT(user1PicToggled(bool)));
    connect(ui->radioButton_user2pic, SIGNAL(toggled(bool)), this, SLOT(user2PicToggled(bool)));
    connect(ui->radioButton_user3pic, SIGNAL(toggled(bool)), this, SLOT(user3PicToggled(bool)));
    connect(ui->pushButton_logout, SIGNAL(clicked()), this, SIGNAL(signalLogout()));

    pline() << rect();
    int iconSize = 79;
    int iconSizeHeight = 59;
    ui->radioButton_userpic->setFixedSize(iconSize, iconSizeHeight);
    ui->radioButton_userpic->setPixmap("://theme/basic/bk_user_normal.png", "://theme/basic/bk_user_press.png");
    ui->radioButton_user1pic->setFixedSize(iconSize, iconSizeHeight);
    ui->radioButton_user1pic->setPixmap("://theme/basic/bk_user1_normal.png", "://theme/basic/bk_user1_press.png");
    ui->radioButton_user2pic->setFixedSize(iconSize, iconSizeHeight);
    ui->radioButton_user2pic->setPixmap("://theme/basic/bk_user2_normal.png", "://theme/basic/bk_user2_press.png");
    ui->radioButton_user3pic->setFixedSize(iconSize, iconSizeHeight);
    ui->radioButton_user3pic->setPixmap("://theme/basic/bk_user3_normal.png", "://theme/basic/bk_user3_press.png");
    ui->radioButton_theme->setFixedSize(iconSize, iconSizeHeight);
    ui->radioButton_theme->setPixmap("://theme/blue/bk_theme_normal.png", "://theme/blue/bk_theme_press.png");
    ui->radioButton_theme1->setFixedSize(iconSize, iconSizeHeight);
    ui->radioButton_theme1->setPixmap("://theme/green/bk_theme_normal.png", "://theme/green/bk_theme_press.png");
    ui->radioButton_theme2->setFixedSize(iconSize, iconSizeHeight);
    ui->radioButton_theme2->setPixmap("://theme/red/bk_theme_normal.png", "://theme/red/bk_theme_press.png");
    ui->radioButton_theme3->setFixedSize(iconSize, iconSizeHeight);
    ui->radioButton_theme3->setPixmap("://theme/yellow/bk_theme_normal.png", "://theme/yellow/bk_theme_press.png");

    ui->label_setheader->setFixedHeight(30);
    ui->label_setpassword->setFixedHeight(30);
    ui->label_settheme->setFixedHeight(30);
}

QUserForm::~QUserForm()
{
    delete ui;
}

void QUserForm::initAll()
{
    QSettings setting;
    QString themeName = setting.value(QString("/%1/Theme").arg(gUserName)).toString();
    if(themeName.isEmpty())
        themeName = "blue";
    QString picName = setting.value(QString("/%1/Pic").arg(gUserName)).toString();
    if(picName.isEmpty())
        picName = "user";

    if("blue" == themeName)
        ui->radioButton_theme->setChecked(true);
    else if("green" == themeName)
        ui->radioButton_theme1->setChecked(true);
    else if("red" == themeName)
        ui->radioButton_theme2->setChecked(true);
    else if("yellow" == themeName)
        ui->radioButton_theme3->setChecked(true);

    if("user" == picName)
        ui->radioButton_userpic->setChecked(true);
    else if("user1" == picName)
        ui->radioButton_user1pic->setChecked(true);
    else if("user2" == picName)
        ui->radioButton_user2pic->setChecked(true);
    else if("user3" == picName)
        ui->radioButton_user3pic->setChecked(true);
}

void QUserForm::initLanguage()
{
    ui->retranslateUi(this);
}

void QUserForm::themeToggled(bool bChecked)
{
    if(!bChecked)
        return;
    QSettings setting;
    setting.setValue(QString("/%1/Theme").arg(gUserName), "blue");
    setting.sync();
    emit setTheme();
}

void QUserForm::theme1Toggled(bool bChecked)
{
    if(!bChecked)
        return;
    QSettings setting;
    setting.setValue(QString("/%1/Theme").arg(gUserName), "green");
    setting.sync();
    emit setTheme();
}

void QUserForm::theme2Toggled(bool bChecked)
{
    if(!bChecked)
        return;
    QSettings setting;
    setting.setValue(QString("/%1/Theme").arg(gUserName), "red");
    setting.sync();
    emit setTheme();
}

void QUserForm::theme3Toggled(bool bChecked)
{
    if(!bChecked)
        return;
    QSettings setting;
    setting.setValue(QString("/%1/Theme").arg(gUserName), "yellow");
    setting.sync();
    emit setTheme();

}

void QUserForm::userPicToggled(bool bChecked)
{
    if(!bChecked)
        return;
    QSettings setting;
    setting.setValue(QString("/%1/Pic").arg(gUserName), "user");
    setting.sync();
    emit setPic();
}

void QUserForm::user1PicToggled(bool bChecked)
{
    if(!bChecked)
        return;
    QSettings setting;
    setting.setValue(QString("/%1/Pic").arg(gUserName), "user1");
    setting.sync();
    emit setPic();
}

void QUserForm::user2PicToggled(bool bChecked)
{
    if(!bChecked)
        return;
    QSettings setting;
    setting.setValue(QString("/%1/Pic").arg(gUserName), "user2");
    setting.sync();
    emit setPic();

}

void QUserForm::user3PicToggled(bool bChecked)
{
    if(!bChecked)
        return;
    QSettings setting;
    setting.setValue(QString("/%1/Pic").arg(gUserName), "user3");
    setting.sync();
    emit setPic();

}

void QUserForm::on_btn_saveuser_clicked()
{
    QString password;
    QSqlQuery query(managerDB);
    query.exec(QString("SELECT * FROM User WHERE Name = '%1'").arg(gUserName));
    if(query.next())
        password = query.record().value(Auth_Passwd).toString();

    if(password != ui->le_oldpwd->text())
    {
        HNMsgBox::warning(this, tr("Old password error"));
        return;
    }

    if(ui->le_confirmpwd->text() != ui->le_newpwd->text())
    {
        //QMsgBox::warning(this, "Warning", "UnConfirmed new password");
        HNMsgBox::warning(this, tr("UnConfirmed new password"));
        return;
    }

    query.exec(QString("UPDATE User SET Password = '%1' WHERE Name = '%2'").arg(ui->le_newpwd->text()).arg(gUserName));
    query.finish();

    HNMsgBox::warning(this, tr("Update password OK"));
    //QMsgBox::information(this, "Notice", "Update password OK.", QMsgBox::Ok);
}
