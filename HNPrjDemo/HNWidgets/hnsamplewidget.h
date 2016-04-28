#ifndef HNSAMPLEWIDGET_H
#define HNSAMPLEWIDGET_H

#include "hnsampleview.h"
#include "hnsamplemodel.h"

namespace Ui {
class HNSampleWidget;
}

class HNSampleWidget : public HNSampleView
{
    Q_OBJECT

public:
    explicit HNSampleWidget(QWidget *parent = 0);
    ~HNSampleWidget();

    void setDB(QString db);
    void setTable(QString table);
    void query(QString excp = "");

    void selectedItems(QVector<QStringList> &ids);

private:
    Ui::HNSampleWidget *ui;
    HNSampleModel* m_model;
    QSqlDatabase m_db;
};

#endif // HNSAMPLEWIDGET_H
