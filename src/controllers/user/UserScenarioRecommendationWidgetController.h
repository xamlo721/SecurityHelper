#ifndef USERSCENARIORECOMMENDATIONWIDGETCONTROLLER_H
#define USERSCENARIORECOMMENDATIONWIDGETCONTROLLER_H

#include <QObject>

#include "src/ui/user/ScenarioMenuWidget.h"
#include "src/ui/user/RecommendationsWidget.h"

#include "src/items/SecurityScenario.h"
#include "src/items/SecurityRecommendations.h"

class UserScenarioRecommendationWidgetController : public QObject {

    Q_OBJECT

    public:
        explicit UserScenarioRecommendationWidgetController(QObject *parent = nullptr);

        void init(ScenarioMenuWidget *scenarioWidget);

    public slots:
        void setScenariesList(QList<SecurityScenario> scenaries);
        void setRecommendationsList(QList<SecurityRecommendations> scenaries);

    private:
        ScenarioMenuWidget *scenarioMenuWidget;

    private slots:


    signals:
        void signalOpenScenarioMenu();
        void signalOpenScenario(quint32 id);
        void signalOnClarifyEvents();
        void signalOpenRecommendationMenu();
        void signalSetRecommentationWidget(RecommendationsWidget * widget);
};

#endif // USERSCENARIORECOMMENDATIONWIDGETCONTROLLER_H
