#ifndef ADMINSCENARIESWIDGET_H
#define ADMINSCENARIESWIDGET_H

#include <QWidget>

namespace Ui {
class AdminScenariesWidget;
}

class AdminScenariesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminScenariesWidget(QWidget *parent = nullptr);
    ~AdminScenariesWidget();

private:
    Ui::AdminScenariesWidget *ui;
};

#endif // ADMINSCENARIESWIDGET_H
