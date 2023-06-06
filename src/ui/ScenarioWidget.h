#ifndef SCENARIO_WIDGET_H
#define SCENARIO_WIDGET_H

#include <QWidget>

namespace Ui {
    class ScenarioWidget;
}

class ScenarioWidget : public QWidget {

    Q_OBJECT

    public:
        explicit ScenarioWidget(int id, QString text, QWidget *parent = nullptr);
        ~ScenarioWidget();

    signals:
        void signalScenarioOpen(int incidentId);
        void signalClarify(int incidentId);

    private slots:
        void onPuttonClicked();

    private:
        int id;
        Ui::ScenarioWidget *ui;
};

#endif // SCENARIO_WIDGET_H
