#include "UserScenarioRecommendationWidgetController.h"

UserRecommendationController::UserRecommendationController(QObject *parent) : QObject{parent} {

}

void UserRecommendationController::init(ScenarioMenuWidget *scenarioWidget) {
    scenarioMenuWidget = scenarioWidget;
}

void UserRecommendationController::setScenariesList(QList<SecurityScenario> scenaries) {
    closeShownScenariesWidget();
    emit signalOpenScenarioMenu();
    for (SecurityScenario sc : scenaries) {
            ScenarioWidget * widget = new ScenarioWidget(sc.getId(), sc.getText(), sc.getName());
            QObject::connect(widget, &ScenarioWidget::signalScenarioOpen, this, &UserRecommendationController::signalOpenScenario);
            QObject::connect(widget, &ScenarioWidget::signalClarify, this, &UserRecommendationController::signalOnClarifyEvents);
            if (!shownScenariesWidget.contains(widget)) {
                shownScenariesWidget << widget;
            }
            scenarioMenuWidget->addScenarioWidget(widget);
    }
}

void UserRecommendationController::setRecommendationsList(QList<SecurityRecommendations> scenaries) {
    emit signalOpenRecommendationMenu();
    SecurityRecommendations rec = scenaries.at(0);
    RecommendationsWidget * widget = new RecommendationsWidget(rec.getTextContainment(), rec.getTextFixes(), rec.getTextRestore());
    emit signalSetRecommentationWidget(widget);
}

void UserRecommendationController::closeShownScenariesWidget() {
    for (ScenarioWidget * widget : shownScenariesWidget) {
        scenarioMenuWidget->closeScenarioWidget(widget);
    }
    shownScenariesWidget.clear();
}

