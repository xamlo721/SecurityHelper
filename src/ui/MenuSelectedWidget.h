#ifndef MENUSELECTEDWIDGET_H
#define MENUSELECTEDWIDGET_H

#include <QWidget>

namespace Ui {
class MenuSelectedWidget;
}

class MenuSelectedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuSelectedWidget(QWidget *parent = nullptr);
    ~MenuSelectedWidget();

private:
    Ui::MenuSelectedWidget *ui;
};

#endif // MENUSELECTEDWIDGET_H
