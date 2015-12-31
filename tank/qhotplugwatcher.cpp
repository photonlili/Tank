
#include "qhotplugwatcher.h"
#include <QWSServer>
#include <QMouseDriverFactory>

QHotplugWatcher* QHotplugWatcher::_instance = NULL;
QHotplugWatcher::QHotplugWatcher(QObject *parent) :
    QThread(parent)
{
    //qDebug("tid=%#x %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__);
    start();

    moveToThread(this); //Let bool event(QEvent *e) be in another thread
    watcher = new QDeviceWatcher;
    watcher->moveToThread(this);
    watcher->appendEventReceiver(this);
    connect(watcher, SIGNAL(deviceAdded(QString)), this, SLOT(slotDeviceAdded(QString)), Qt::DirectConnection);
    connect(watcher, SIGNAL(deviceChanged(QString)), this, SLOT(slotDeviceChanged(QString)), Qt::DirectConnection);
    connect(watcher, SIGNAL(deviceRemoved(QString)), this, SLOT(slotDeviceRemoved(QString)), Qt::DirectConnection);
    watcher->start();
}

QHotplugWatcher *QHotplugWatcher::Instance()
{
    if(_instance)
        return _instance;
    _instance = new QHotplugWatcher();
    return _instance;
}

void QHotplugWatcher::slotDeviceAdded(const QString &dev)
{
#ifdef __MIPS_LINUX__
    QWSServer::setCursorVisible(true);
#endif
    qDebug("tid=%#x %s: add %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));
}

void QHotplugWatcher::slotDeviceRemoved(const QString &dev)
{
#ifdef __MIPS_LINUX__
    QWSServer::setCursorVisible(false);
#endif
    qDebug("tid=%#x %s: remove %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));
}

void QHotplugWatcher::slotDeviceChanged(const QString &dev)
{
    qDebug("tid=%#x %s: change %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));
}

bool QHotplugWatcher::event(QEvent *e) {
    if (e->type() == QDeviceChangeEvent::registeredType()) {
        QDeviceChangeEvent *event = (QDeviceChangeEvent*)e;
        QString action("Change");
        if (event->action() == QDeviceChangeEvent::Add)
            action = "Add";
        else if (event->action() == QDeviceChangeEvent::Remove)
            action = "Remove";

        //qDebug("tid=%#x event=%d %s: %s %s", (quintptr)QThread::currentThreadId(), e->type(), __PRETTY_FUNCTION__, qPrintable(action), qPrintable(event->device()));
        event->accept();
        return true;
    }
    return QObject::event(e);
}
