#include "qeditform.h"
#include "ui_qeditform.h"
#include <QDebug>
#include "qtankpublic.h"
#include "qtankdefine.h"
#include <QSqlQuery>
#include <QItemSelection>
#include "hnmsgbox.h"

QEditForm::QEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QEditForm)
{
    ui->setupUi(this);

    openLib = new QUserLibraryDialog(this);
    tbvStage = new QStageWidget(this);
    tbvStage->setHidden(true);

    //tbvStage->addMap(ui->le_timeramp, Stage_Timeramp);
    //tbvStage->addMap(ui->le_tempture, Stage_Tempture);
    //tbvStage->addMap(ui->le_press, Stage_Presspsi);
    //tbvStage->addMap(ui->le_hold, Stage_Hold);

    QRegExp regExp("[0-9]{1,2}[:][0-9]{0,2}");
    QRegExpValidator *pValidator = new QRegExpValidator(regExp, this);
    ui->le_timeramp->setValidator(pValidator);
    ui->le_timeramp->setInputMask("00:00");
    ui->le_hold->setValidator(pValidator);
    ui->le_hold->setInputMask("00:00");
    libForm = new QLibraryForm(this);

    connect(ui->tableView_method->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentMethodChanged(QModelIndex,QModelIndex)));

    connect(ui->pushButton_method_add, SIGNAL(clicked()), this, SLOT(newM()));
    connect(ui->pushButton_method_del, SIGNAL(clicked()), this, SLOT(delM()));
    connect(ui->pushButton_method_save, SIGNAL(clicked()), this, SLOT(saveM()));
    connect(libForm, SIGNAL(libSelectedDisplayed(QString)), ui->label_method_libname, SLOT(setText(QString)));
    connect(libForm, SIGNAL(libSelected(QString)), this, SLOT(libGetted(QString)));

    ui->label_12->setHidden(true);
    ui->le_vessel->setHidden(true);
}

QEditForm::~QEditForm()
{
    delete ui;
}

void QEditForm::initAll()
{
    QSettings set;
    QString db = set.value(QString("%1/lastDBEdited").arg(gUserName)).toString();
    int mid = set.value(QString("%1/lastMethodIdEdited").arg(gUserName)).toInt();
    int stageid = set.value(QString("%1/lastStageEdited").arg(gUserName)).toInt();
    if(db.isEmpty())
        libGetted(DB_USER);
    else
        libGetted(db);
}

void QEditForm::libGetted(QString name)
{
    if(DB_EXTRACT == name)
    {
        ui->lb_pressBuddy->setHidden(true);
        ui->lb_timerampBuddy->setHidden(true);
        ui->lbTypeBuddy->setHidden(true);
        ui->le_press->setHidden(true);
        ui->le_timeramp->setHidden(true);
        ui->comboBox_method_type->setHidden(true);
    }
    else
    {
        ui->lb_pressBuddy->setHidden(false);
        ui->lb_timerampBuddy->setHidden(false);
        ui->lbTypeBuddy->setHidden(false);
        ui->le_press->setHidden(false);
        ui->le_timeramp->setHidden(false);
        ui->comboBox_method_type->setHidden(false);
    }

    ui->tableView_method->initdb(name, false);
    tbvStage->initdb(name, false);

    ui->tableView_method->refresh();
    ui->tableView_method->selectMethod();

    QSettings set;
    set.setValue(QString("%1/lastDBEdited").arg(gUserName), name);
    set.sync();
}

void QEditForm::currentMethodChanged(QModelIndex, QModelIndex)
{
    ui->lineEdit_methodname->setText(ui->tableView_method->currentMethodName());
    ui->comboBox_method_type->setCurrentIndex(ui->tableView_method->currentMethodType());
    ui->le_vessel->setText(ui->tableView_method->currentMethodVessel());

    tbvStage->setMethodId(ui->tableView_method->currentMethodId());
    tbvStage->refresh(ui->tableView_method->currentMethodId());
    tbvStage->selectStage();

    qint8 stage, vessel;
    qint16 ramp, press, tempture, hold;

    tbvStage->currentStageParam(stage, vessel, ramp, press, tempture, hold);

    qint32 time = ramp;
    qint32 hour = time / 60;
    qint32 minute = time % 60;
    QString tmStr = QString("%1:%2")
            .arg(hour, 2, 10, QLatin1Char('0'))
            .arg(minute, 2, 10, QLatin1Char('0'));
    ui->le_timeramp->setText(tmStr);

    ui->le_press->setText(QString::number(press));
    ui->le_tempture->setText(QString::number(tempture));

    time = hold;
    hour = time / 60;
    minute = time % 60;
    tmStr = QString("%1:%2")
            .arg(hour, 2, 10, QLatin1Char('0'))
            .arg(minute, 2, 10, QLatin1Char('0'));
    ui->le_hold->setText(tmStr);


    if(Type_Extract == ui->tableView_method->currentMethodType())
    {
        ui->lb_timerampBuddy->setHidden(true);
        ui->le_timeramp->setHidden(true);
        ui->lb_pressBuddy->setHidden(true);
        ui->le_press->setHidden(true);
        ui->lb_temptureBuddy->setHidden(false);
        ui->le_tempture->setHidden(false);
    }
    else if(Type_Standard == ui->tableView_method->currentMethodType())
    {
        ui->lb_timerampBuddy->setHidden(true);
        ui->le_timeramp->setHidden(true);
        ui->lb_pressBuddy->setHidden(true);
        ui->le_press->setHidden(true);
        ui->lb_temptureBuddy->setHidden(false);
        ui->le_tempture->setHidden(false);
    }
    else if(Type_Stressure == ui->tableView_method->currentMethodType())
    {
        ui->lb_timerampBuddy->setHidden(true);
        ui->le_timeramp->setHidden(true);
        ui->lb_pressBuddy->setHidden(false);
        ui->le_press->setHidden(false);
        ui->lb_temptureBuddy->setHidden(true);
        ui->le_tempture->setHidden(true);
    }
    else if(Type_Temprature == ui->tableView_method->currentMethodType())
    {
        ui->lb_timerampBuddy->setHidden(false);
        ui->le_timeramp->setHidden(false);
        ui->lb_pressBuddy->setHidden(false);
        ui->le_press->setHidden(false);
        ui->lb_temptureBuddy->setHidden(false);
        ui->le_tempture->setHidden(false);
    }


    ui->spin_stage->setRange(1, tbvStage->countStage());
    ui->spin_stage->setValue(1);
    ui->le_stagenum->setText(QString::number(tbvStage->countStage()));

    QSettings set;
    set.setValue(QString("%1/lastMethodIdEdited").arg(gUserName), ui->tableView_method->currentMethodId());
    set.sync();
}

void QEditForm::saveM()
{
    QStringList rampList = ui->le_timeramp->text().split(":");
    quint16 ramp = rampList[0].toUInt() * 60 + rampList[1].toUInt();
    pline() << ui->le_timeramp->text() << ramp;

    quint16 press = ui->le_press->text().toUInt();
    quint16 tempture = ui->le_tempture->text().toUInt();

    QStringList holdList = ui->le_hold->text().split(":");
    quint16 hold = holdList[0].toUInt() * 60 + holdList[1].toUInt();
    pline() << ui->le_hold->text() << hold;

    int stage = ui->spin_stage->value();
    int vessel = ui->le_vessel->text().toInt();
    pline() << stage << ramp << press << tempture << hold;

    if(stage <0 || stage > 42)
    {
        HNMsgBox::warning(this, tr("The field of stage is 1 - 42"));
        return;
    }

    switch(ui->comboBox_method_type->currentIndex())
    {
    case Type_Temprature:
        if(ramp < 0 || ramp > 9999)
        {
            HNMsgBox::warning(this, tr("The field of ramp is 00:01 - 20:00"));
            return;
        }
        break;
    case Type_Standard:
    case Type_Stressure:
    case Type_Extract:
        ramp = 0;
        break;
    }

    switch(ui->comboBox_method_type->currentIndex())
    {
    case Type_Temprature:
    case Type_Stressure:
        if(press < 0 || press > 2800)
        {
            HNMsgBox::warning(this, tr("The field of press is 00:01 - 20:00"));
            return;
        }
        break;
    case Type_Extract:
    case Type_Standard:
        press = 0;
        break;
    }


    switch(ui->comboBox_method_type->currentIndex())
    {
    case Type_Stressure:
        tempture = 0;
        break;
    case Type_Temprature:
    case Type_Standard:
    case Type_Extract:
        if(tempture < 0 || tempture > 300)
        {
            HNMsgBox::warning(this, tr("The field of tempture is 00:01 - 20:00"));
            return;
        }

        break;
    }

    if(hold < 0 || hold > 9999)
    {
        HNMsgBox::warning(this, tr("The field of HOLD is 00:01 - 20:00"));
        return;
    }



    tbvStage->saveStage(stage, vessel, ramp, press, tempture, hold);

    int type = ui->comboBox_method_type->currentIndex();
    QString newName = ui->lineEdit_methodname->text();
    QModelIndex index = ui->tableView_method->currentIndex();
    pline() << index.row() << type << newName;
    ui->tableView_method->setMethodType(index.row(), type);
    ui->tableView_method->setMethodName(index.row(), newName);
    ui->tableView_method->setMethodVessel(index.row(), vessel);
    pline() << index.row() << type << newName;

    ui->tableView_method->selectMethod(index.row());
    ui->spin_stage->setValue(stage);

    emit signalSaved(ui->tableView_method->currentMethodId(), ui->tableView_method->currentMethodType(), ui->tableView_method->currentMethodName());

}

void QEditForm::delM()
{
    int ret = HNMsgBox::question(this, tr("que ren shanchu method?"));
    if(HNMsgBox::Rejected == ret)
        return;

    int row = ui->tableView_method->currentIndex().row();
    tbvStage->delAllStage();
    ui->tableView_method->delMethod(row);
    ui->tableView_method->selectMethod(row>0?row-1:0);

    HNMsgBox::warning(this, tr("del success!"));
}

void QEditForm::newM()
{
    ui->tableView_method->newMethod();
    tbvStage->setMethodId(ui->tableView_method->currentMethodId());
    tbvStage->newStage();
}

void QEditForm::initLanguage()
{
    ui->retranslateUi(this);
    ui->comboBox_method_type->clear();
    QStringList methodType;
    methodType << tr("Standard");
    methodType << tr("Tempture");
    methodType << tr("Pressure");
    ui->comboBox_method_type->addItems(methodType);
    ui->comboBox_method_type->setCurrentIndex(0);
}

void QEditForm::on_btn_open_clicked()
{
    libForm->initAll();
    static QPropertyAnimation* ani = new QPropertyAnimation(libForm, "geometry", this);
    ani->setStartValue(QRect(140, 0, 520, 245));
    ani->setEndValue(QRect(140, 120, 520, 245));
    ani->setDuration(500);
    ani->setEasingCurve(QEasingCurve::OutCurve);
    ani->start();
    libForm->exec();
}

void QEditForm::on_spin_stage_valueChanged(int arg1)
{
    pline() << tbvStage->currentStage() << arg1;
    tbvStage->selectStage(arg1-1);
    pline() << tbvStage->currentStage();
    qint8 stage, vessel;
    qint16 ramp, press, tempture, hold;

    tbvStage->currentStageParam(stage, vessel, ramp, press, tempture, hold);

    qint32 time = ramp;
    qint32 hour = time / 60;
    qint32 minute = time % 60;
    QString tmStr = QString("%1:%2")
            .arg(hour, 2, 10, QLatin1Char('0'))
            .arg(minute, 2, 10, QLatin1Char('0'));
    ui->le_timeramp->setText(tmStr);

    ui->le_press->setText(QString::number(press));
    ui->le_tempture->setText(QString::number(tempture));

    time = hold;
    hour = time / 60;
    minute = time % 60;
    tmStr = QString("%1:%2")
            .arg(hour, 2, 10, QLatin1Char('0'))
            .arg(minute, 2, 10, QLatin1Char('0'));
    ui->le_hold->setText(tmStr);

    QSettings set;
    set.setValue(QString("%1/lastStageEdited").arg(gUserName), tbvStage->currentStage());
    set.sync();

}

void QEditForm::on_btn_stage_clear_clicked()
{
    tbvStage->cleanStage();
    ui->spin_stage->setRange(1, 1);
    ui->spin_stage->setValue(1);
    ui->le_stagenum->setText("1");
}

void QEditForm::on_btn_stage_del_clicked()
{
    tbvStage->delStage();
    ui->spin_stage->setRange(1, tbvStage->countStage());
    ui->spin_stage->setValue(tbvStage->countStage());
    ui->le_stagenum->setText(QString::number(tbvStage->countStage()));
}

void QEditForm::on_btn_stage_add_clicked()
{
    tbvStage->newStage();
    ui->spin_stage->setRange(1, tbvStage->countStage());
    ui->spin_stage->setValue(tbvStage->countStage());
    ui->le_stagenum->setText(QString::number(tbvStage->countStage()));
}


void QEditForm::on_comboBox_method_type_currentIndexChanged(int index)
{
    if(Type_Extract == index)
    {
        ui->lb_timerampBuddy->setHidden(true);
        ui->le_timeramp->setHidden(true);
        ui->lb_pressBuddy->setHidden(true);
        ui->le_press->setHidden(true);
        ui->lb_temptureBuddy->setHidden(false);
        ui->le_tempture->setHidden(false);
    }
    else if(Type_Standard == index)
    {
        ui->lb_timerampBuddy->setHidden(true);
        ui->le_timeramp->setHidden(true);
        ui->lb_pressBuddy->setHidden(true);
        ui->le_press->setHidden(true);
        ui->lb_temptureBuddy->setHidden(false);
        ui->le_tempture->setHidden(false);
    }
    else if(Type_Stressure == index)
    {
        ui->lb_timerampBuddy->setHidden(true);
        ui->le_timeramp->setHidden(true);
        ui->lb_pressBuddy->setHidden(false);
        ui->le_press->setHidden(false);
        ui->lb_temptureBuddy->setHidden(true);
        ui->le_tempture->setHidden(true);
    }
    else if(Type_Temprature == index)
    {
        ui->lb_timerampBuddy->setHidden(false);
        ui->le_timeramp->setHidden(false);
        ui->lb_pressBuddy->setHidden(false);
        ui->le_press->setHidden(false);
        ui->lb_temptureBuddy->setHidden(false);
        ui->le_tempture->setHidden(false);
    }

    if(Type_Stressure == index)
    {
        ui->lb_pressBuddy->setText(tr("gonglv"));
    }
    else
    {
        ui->lb_pressBuddy->setText(tr("press"));
    }
}
