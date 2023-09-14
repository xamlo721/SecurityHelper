#ifndef SCENARIO_WIDGET_H
#define SCENARIO_WIDGET_H

#include <QWidget>

namespace Ui {
    class ScenarioWidget;
}

class ScenarioWidget : public QWidget {

    Q_OBJECT

    public:
        explicit ScenarioWidget(quint32 id, QString text, QWidget *parent = nullptr);
        ~ScenarioWidget();

    signals:
        void signalScenarioOpen(quint32 incidentId);
        void signalClarify(quint32 incidentId);

    private slots:
        void onPuttonClicked();

    private:
        quint32 id;
        Ui::ScenarioWidget *ui;
};

#endif // SCENARIO_WIDGET_H
