#ifndef QTANKAPP_H
#define QTANKAPP_H

#include <QApplication>

class QTankApp : public QApplication
{
    Q_OBJECT
public:
    explicit QTankApp(int &argc, char **argv);
    virtual ~QTankApp();

signals:

public slots:
    void setLanguage();

private:
    QTranslator* language;
};

#endif // QTANKAPP_H
