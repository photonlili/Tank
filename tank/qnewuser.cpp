#include "qnewuser.h"
#include "ui_qnewuser.h"
#include "qtankpublic.h"
#include "qtankdefine.h"

QNewUser::QNewUser(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::QNewUser)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭 show的功能强大起来 可以使用输入法
    QSqlQuery query(managerDB);
    query.exec(QString("SELECT * FROM User WHERE Name = '%1'").arg(gUserName));
    if(query.next())
    {
        int auth = query.record().value(Auth_Authrity).toInt();
        switch(auth)
        {
        case 0:
            {
                ui->comb_auth->addItem("Manager");
                ui->comb_auth->addItem("User");
            }
            break;
        case 1:
            {
                ui->comb_auth->addItem("User");
            }
            break;
        default:
            {
                query.finish();
            }
            return;
        }
    }
    query.finish();
    connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->btn_sure, SIGNAL(clicked()), this, SLOT(accept()));
    ui->le_pwd->setEchoMode(QLineEdit::Password);
    ui->le_confirm->setEchoMode(QLineEdit::Password);
}

QNewUser::~QNewUser()
{
    delete ui;
}

void QNewUser::initAll()
{
    setFocus(Qt::MouseFocusReason);
}

void QNewUser::userInfo(QString &name, QString &password, QString &confirm, QString &authority, QString &comment)
{
    name = ui->le_name->text();
    password = ui->le_pwd->text();
    confirm = ui->le_confirm->text();
    authority = ui->comb_auth->currentText();
    comment = ui->text_commnet->toPlainText();
}
