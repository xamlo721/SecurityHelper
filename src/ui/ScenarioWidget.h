#ifndef SCENARIO_WIDGET_H
#define SCENARIO_WIDGET_H

#include <QWidget>

namespace Ui {
    class ScenarioWidget;
}

class ScenarioWidget : public QWidget {

    Q_OBJECT

    public:
        explicit ScenarioWidget(QWidget *parent = nullptr);
        ~ScenarioWidget();

    private:
        Ui::ScenarioWidget *ui;
};

#endif // SCENARIO_WIDGET_H
