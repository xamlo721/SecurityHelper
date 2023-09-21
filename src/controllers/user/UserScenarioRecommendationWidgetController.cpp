#include "UserScenarioRecommendationWidgetController.h"

UserScenarioRecommendationWidgetController::UserScenarioRecommendationWidgetController(QObject *parent) : QObject{parent} {

}

void UserScenarioRecommendationWidgetController::init(ScenarioMenuWidget *scenarioWidget) {
    scenarioMenuWidget = scenarioWidget;
}

void UserScenarioRecommendationWidgetController::setScenariesList(QList<SecurityScenario> scenaries) {
    emit signalOpenScenarioMenu();

    for (SecurityScenario sc : scenaries) {
        ScenarioWidget * widget = new ScenarioWidget(sc.getId(), sc.getText());
        QObject::connect(widget, &ScenarioWidget::signalScenarioOpen, this, &UserScenarioRecommendationWidgetController::signalOpenScenario);
        QObject::connect(widget, &ScenarioWidget::signalClarify, this, &UserScenarioRecommendationWidgetController::signalOnClarifyEvents);
        this->scenarioMenuWidget->addScenarioWidget(widget);
    }
}

void UserScenarioRecommendationWidgetController::setRecommendationsList(QList<SecurityRecommendations> scenaries) {
    emit signalOpenRecommendationMenu();
    SecurityRecommendations rec = scenaries.at(0);
    RecommendationsWidget * widget = new RecommendationsWidget(rec.getTextContainment(), rec.getTextFixes(), rec.getTextRestore());
    emit signalSetRecommentationWidget(widget);
}
