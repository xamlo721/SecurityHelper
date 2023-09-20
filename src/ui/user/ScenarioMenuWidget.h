#ifndef SCENARIOMENU_WIDGET_H
#define SCENARIOMENU_WIDGET_H

#include <QWidget>

#include "src/ui/user/ScenarioWidget.h"

namespace Ui {
    class ScenarioMenuWidget;
}

class ScenarioMenuWidget : public QWidget {

    Q_OBJECT

    public:
        explicit ScenarioMenuWidget(QWidget *parent = nullptr);
        ~ScenarioMenuWidget();

        void clear();

        void addScenarioWidget(ScenarioWidget * widget);

    private:
        Ui::ScenarioMenuWidget *ui;
};

#endif // SCENARIOMENU_WIDGET_H
