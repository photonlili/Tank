#include "qmethodform.h"
#include "ui_qmethodform.h"

QMethodForm::QMethodForm(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::QMethodForm)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModal);

    connect(ui->tbv_lib->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(libChanged()));
    connect(ui->tbv_method->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(methodChanged()));

    ui->btn_up->iconTable()[BTN_NORMAL] = "://theme/basic/bt_up.png";
    ui->btn_up->iconTable()[BTN_PRESS] = "://theme/basic/bt_up_press.png";
    ui->btn_down->iconTable()[BTN_NORMAL] = "://theme/basic/bt_down.png";
    ui->btn_down->iconTable()[BTN_PRESS] = "://theme/basic/bt_down_press.png";
    ui->btn_sure->iconTable()[BTN_NORMAL] = "://theme/basic/bt_sure.png";
    ui->btn_sure->iconTable()[BTN_PRESS] = "://theme/basic/bt_sure_press.png";

    ui->btn_up->setFixedSize(80, 30);
    ui->btn_down->setFixedSize(80, 30);
    ui->btn_sure->setFixedSize(80, 30);
    ui->btnClose->iconTable()[BTN_NORMAL] = "://theme/basic/bt_close.png";
    ui->btnClose->iconTable()[BTN_PRESS] = "://theme/basic/bt_close_press.png";
    ui->btnClose->setFixedSize(27, 27);
}

QMethodForm::~QMethodForm()
{
    delete ui;
}

void QMethodForm::initAll(QString filter)
{
    ui->tbv_lib->refresh(filter);
    ui->tbv_lib->selectdb();
}

QString QMethodForm::currentLibrary()
{
    return ui->tbv_lib->currentdb();
}

QString QMethodForm::currentMethodName()
{
    return ui->tbv_method->currentMethodName();
}

int QMethodForm::currentMethodType()
{
    return ui->tbv_method->currentMethodType();
}

int QMethodForm::currentMethodId()
{
    return ui->tbv_method->currentMethodId();
}

void QMethodForm::libChanged()
{
    QString curDB = ui->tbv_lib->currentdb();

    ui->tbv_method->initdb(curDB, false);
    //ui->wid_stage->initdb(curDB);

    ui->tbv_method->refresh();
    ui->tbv_method->selectMethod();
}

void QMethodForm::methodChanged()
{
    int mid = ui->tbv_method->currentMethodId();
    //ui->wid_stage->refresh(mid);
    QString method = ui->tbv_method->currentMethodName();
    int type = ui->tbv_method->currentMethodType();
    QString strType;
    switch(type)
    {
    case Type_Standard:
        strType = tr("Standard");
        break;
    case Type_Stressure:
        strType = tr("Press");
        break;
    case Type_Temprature:
        strType = tr("RAMP");
        break;
    case Type_Extract:
        strType = tr("Extract");
        break;
    }

    emit tellMethod(method);
    emit tellType(strType);
}

void QMethodForm::on_btn_up_clicked()
{
    ui->tbv_method->prev();
}

void QMethodForm::on_btn_down_clicked()
{
    ui->tbv_method->next();
}

void QMethodForm::on_btn_sure_clicked()
{
    QString curDB = ui->tbv_lib->currentdb();
    int mid = ui->tbv_method->currentMethodId();
    QString method = ui->tbv_method->currentMethodName();
    int type = ui->tbv_method->currentMethodType();
    QString curDBDisplayed = ui->tbv_lib->currentDBDisplayed();

    pline() << curDB << curDBDisplayed << mid;
    emit tellLibrary(curDB);
    emit tellLibraryDisplayed(curDBDisplayed);
    emit selMethod(curDB, mid, method, type);

    accept();
}

void QMethodForm::on_le_search_btnClicked()
{
    ui->tbv_method->refresh(QString("M_Name like '%%1%'").arg(ui->le_search->text()));
    ui->tbv_method->selectMethod();
}

void QMethodForm::on_btnClose_clicked()
{
    reject();
}
