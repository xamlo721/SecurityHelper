#ifndef ADMINCATEGORIESWIDGET_H
#define ADMINCATEGORIESWIDGET_H

#include <QWidget>

namespace Ui {
class AdminCategoriesWidget;
}

class AdminCategoriesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminCategoriesWidget(QWidget *parent = nullptr);
    ~AdminCategoriesWidget();

private:
    Ui::AdminCategoriesWidget *ui;
};

#endif // ADMINCATEGORIESWIDGET_H
