/******************************************************************************
	Name: description
    Copyright (C) 2011-2015 Wang Bin <wbsecg1@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/

#ifndef QHOTPLUGWATCHER_H
#define QHOTPLUGWATCHER_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include "qdevicewatcher.h"

#ifndef __GNUC__
#define __PRETTY_FUNCTION__  __FUNCTION__
#endif

class QHotplugWatcher : public QThread
{
	Q_OBJECT
public:
    static QHotplugWatcher *Instance();

public slots:
    void slotDeviceAdded(const QString& dev);
    void slotDeviceRemoved(const QString& dev);
    void slotDeviceChanged(const QString& dev);
protected:
    virtual bool event(QEvent *e);

private:

private:
    QDeviceWatcher *watcher;
    explicit QHotplugWatcher(QObject *parent = 0);
    static QHotplugWatcher* _instance;
};

#endif // QHOTPLUGWATCHER_H
