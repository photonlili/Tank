#ifndef QHOTPLUGAPP_H
#define QHOTPLUGAPP_H

#include <QCoreApplication>

class QHotPlugApp : public QCoreApplication
{
    Q_OBJECT
public:
    explicit QHotPlugApp(int &argc, char **argv);

signals:

public slots:
    void slotUPanAutoRun(int status);
};

#endif // QHOTPLUGAPP_H
