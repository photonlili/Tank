#ifndef QUSERLIBRARYWIDGET_H
#define QUSERLIBRARYWIDGET_H

#include "quserlibraryview.h"
#include "quserlibrarymodel.h"
#include <QDataWidgetMapper>

namespace Ui {
class QUserLibraryWidget;
}

class QUserLibraryWidget : public QUserLibraryView
{
    Q_OBJECT

public:
    explicit QUserLibraryWidget(QWidget *parent = 0);
    ~QUserLibraryWidget();
    void refresh(QString filter = "");
    void selectdb(int id = 0);
    void selectdb(QString dbname);
    QString currentdb();
    QString currentDBDisplayed();
    QString lastDBDisplayed();
    void setdbname(QString newName, bool withMapper = false);
    inline void addMap(QWidget* w, int section) { m_mapper->addMapping(w, section); }

public slots:
    void newDB();
    void delDB();
    void prev();
    void next();

private:
    inline QDataWidgetMapper* mapper() { return m_mapper; }
    Ui::QUserLibraryWidget *ui;
    QUserLibraryModel* m_model;
    QDataWidgetMapper* m_mapper;
};

#endif // QUSERLIBRARYWIDGET_H
