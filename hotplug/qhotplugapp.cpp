#include "qhotplugapp.h"
#include "qhotplugwatcher.h"
#include <QProcess>

QHotPlugApp::QHotPlugApp(int &argc, char **argv) :
    QCoreApplication(argc, argv)
{
}

void QHotPlugApp::slotUPanAutoRun(int status)
{
    if(QHotplugConsoleWatcher::E_ADD == status)
    {
        QString mP = QHotplugConsoleWatcher::Instance()->devMountPath();
        QString app = QString("%1/autorun.sh").arg(mP);
        QProcess* p = new QProcess(this);
        p->setWorkingDirectory(mP);
        p->start(app);
        p->waitForStarted();
        p->waitForFinished();
        delete p;
    }
}
