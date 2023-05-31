#ifndef SCENARIOMENU_WIDGET_H
#define SCENARIOMENU_WIDGET_H

#include <QWidget>

namespace Ui {
    class ScenarioMenuWidget;
}

class ScenarioMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScenarioMenuWidget(QWidget *parent = nullptr);
    ~ScenarioMenuWidget();

private:
    Ui::ScenarioMenuWidget *ui;
};

#endif // SCENARIOMENU_WIDGET_H
