#ifndef HNSAMPLEMUTIPAGEWIDGET_H
#define HNSAMPLEMUTIPAGEWIDGET_H

#include <QWidget>
#include <QSqlRelationalTableModel>

namespace Ui {
class HNSampleMutiPageWidget;
}

class HNSampleMutiPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNSampleMutiPageWidget(QWidget *parent = 0);
    ~HNSampleMutiPageWidget();

    void setDB(QString db);
    void setTable(QString table);
    void setRecordNumPerPage(int num);
    void query();

private slots:
    void on_btnLeft_clicked();

    void on_btnRight_clicked();

    void on_btnJump_clicked();

    void on_btnLeftHead_clicked();

    void on_btnRightHead_clicked();

private:
    Ui::HNSampleMutiPageWidget *ui;
    QSqlDatabase m_db;
    QString m_name;
    QString m_table;
    int m_numPerPage ;
};

#endif // HNSAMPLEMUTIPAGEWIDGET_H
