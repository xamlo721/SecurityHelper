#ifndef USERSCENARIORECOMMENDATIONWIDGETCONTROLLER_H
#define USERSCENARIORECOMMENDATIONWIDGETCONTROLLER_H

#include <QObject>

#include "src/ui/user/ScenarioMenuWidget.h"

#include "src/items/SecurityScenario.h"

class UserScenaryController : public QObject {

    Q_OBJECT

    public:
        explicit UserScenaryController(QObject *parent = nullptr);

        void init(ScenarioMenuWidget *scenarioWidget);

    public slots:
        void setScenariesList(QList<SecurityScenario> scenaries);

    private:
        ScenarioMenuWidget *scenarioMenuWidget;
        ///Лист с виджетами сценариев, которые уже показаны
        QList<ScenarioWidget*> shownScenariesWidget;
        ///Закрывает все виджеты сценариев из листа shownScenariesWidget
        void clearScenaries();

    private slots:
        void slotOnScenaryClicked(quint32 id);


    signals:
        void signalScenarySelected();
        void signalOpenScenario(quint32 id);
        void signalOnClarifyEvents();
};

#endif // USERSCENARIORECOMMENDATIONWIDGETCONTROLLER_H
