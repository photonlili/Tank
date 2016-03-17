#include "qhotplugapp.h"
#include "qhotplugwatcher.h"
#include <stdlib.h>

QHotPlugApp::QHotPlugApp(int &argc, char **argv) :
    QCoreApplication(argc, argv)
{
}

void QHotPlugApp::slotUPanAutoRun(int status)
{
    if(QHotplugConsoleWatcher::E_ADD == status)
    {
        QString mP = QHotplugConsoleWatcher::Instance()->devMountPath();
        QString auth = QString("chmod +x %1/autorun.sh").arg(mP);
        system(auth.toAscii().constData());
        QString app = QString("%1/autorun.sh").arg(mP);
        system(app.toAscii().constData());
    }
    else
    {

    }
}
