#include <QCoreApplication>
#include "qhotplugwatcher.h"
#include "qhotplugapp.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    QHotPlugApp *a = new QHotPlugApp(argc, argv);

    QHotplugConsoleWatcher* watcher = QHotplugConsoleWatcher::Instance();

    QObject::connect(watcher, SIGNAL(storageChanged(int)), a, SLOT(slotUPanAutoRun(int)));

    daemon(0, 0);

    return a->exec();
}
