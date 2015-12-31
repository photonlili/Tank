#ifndef QUSERSETWIDGET_H
#define QUSERSETWIDGET_H

#include "qusersetview.h"
#include "qusersetmodel.h"
#include <QDataWidgetMapper>

namespace Ui {
class QUserSetWidget;
}

class QUserSetWidget : public QUserSetView
{
    Q_OBJECT

public:
    explicit QUserSetWidget(QWidget *parent = 0);
    ~QUserSetWidget();

    void refresh();
    void selectUser(int id = 0);
    void selectUser(QString userName);
    QString currentUser();
    QString currentUserAuthority();
    QString currentUserPassword();
    void setUserName(QString newName);
    inline QDataWidgetMapper* mapper() { return m_mapper; }
    inline QUserSetModel* model() { return m_model; }
    inline void addMap(QWidget* w, int section) { m_mapper->addMapping(w, section); }
    void initLanguage();

public slots:
    void newUser(QString name, QString pwd, QString auth, QString comt);
    void delUser();
    void updateMap();
    void saveMap();

private slots:
    void currentItemChanged(QModelIndex,QModelIndex);
private:
    Ui::QUserSetWidget *ui;

    QUserSetModel* m_model;
    QDataWidgetMapper* m_mapper;
};

#endif // QUSERSETWIDGET_H
