#include "qtankpublic.h"
#include "qtankdefine.h"
#include <QSqlQuery>
#include <QSettings>
#include <QUuid>
#include <QDebug>
#include "qserialwarning.h"
#include "qtanklinux.h"

QSqlDatabase managerDB;
QString gUserName;
QString gPassword;
int gAuthority;

QSqlDatabase newDatabaseConn()
{
    QUuid uuid = QUuid::createUuid();
    //qDebug() << uuid.toString();
    return QSqlDatabase::addDatabase(DB_TYPE, uuid.toString());
}

void moveCenter(QWidget *w)
{
#ifdef __MIPS_LINUX__
    QPoint topleft(0,0);
#else
    QPoint topleft(QApplication::desktop()->availableGeometry().width()-WINDOW_WIDTH,
                   QApplication::desktop()->availableGeometry().top());
#endif
    w->move(topleft.x() + ( WINDOW_WIDTH - w->width()) / 2,
           topleft.y() + ( WINDOW_HEIGHT - w->height()) / 2);
}

//opened
void setDatabaseName(QSqlDatabase &db, QString dbName)
{
    if(db.isOpen())
        db.close();

    db.setDatabaseName(QString("%1/%2.db").arg(DB_PATH).arg(dbName));

    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("QSQLITE %1 Error").arg(db.databaseName()),
                             db.lastError().text());
        return;
    }
}


void openDatabase(QSqlDatabase &db)
{
    if(db.isOpen())
        return;

    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("QSQLITE %1 Error").arg(db.databaseName()),
                             db.lastError().text());
        return;
    }
}


void closeDatabase(QSqlDatabase &db)
{
    db.close();
}


void moveRight(QWidget *w)
{
    w->move((QApplication::desktop()->width() - w->width()), 0);
}


void msgHandler(QtMsgType type, const char * msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug");
        break;

    case QtWarningMsg:
        text = QString("Warning");
        break;

    case QtCriticalMsg:
        text = QString("Critical");
        break;

    case QtFatalMsg:
        text = QString("Fatal");
    }

    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString message = QString("%1 %2 %3").arg(current_date_time).arg(text).arg(msg);
    QString current_date = QDateTime::currentDateTime().toString("yyyy-MM-dd");

    //检查文件数量 启动时检查 保留30天
    //检查文件大小，超过最大值输出到最新的文件，一天一个文件
    QString filename = QString("./log/log-%1.txt").arg(current_date);
#ifdef __MIPS_LINUX__
    system(QString("touch %1").arg(filename).toAscii().data());
#endif
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();

    fprintf(stderr, "%s\n", msg);
}

/**
 * @brief systemChild 返回后，进入两个进程空间
 * @param cmd
 * @return
 */
int systemChild(const char *cmd)
{
    if(!cmd)
        return -1;
    __pid_t pid = fork();
    if(pid > 0)
    {
        return 0;
    }
    else if(0 == pid)
    {
        return execv(cmd, NULL);
    }
}
