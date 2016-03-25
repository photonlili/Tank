#ifndef TEMPLATEWIDGET_H
#define TEMPLATEWIDGET_H

#include <QWidget>

namespace Ui {
class TemplateWidget;
}

class TemplateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateWidget(QWidget *parent = 0);
    ~TemplateWidget();

private:
    Ui::TemplateWidget *ui;
};

#endif // TEMPLATEWIDGET_H
