#include "MainWindowController.h"

void MainWindowController::setIncidentList(QList<SecurityIncident> incidents) {
    this->w->clearIncidentList();

    for (SecurityIncident inc : incidents) {
        IncidentWidget * widget = new IncidentWidget(inc.getId(), inc.getText());
        QObject::connect(widget, &IncidentWidget::signalIncidentOpen, this, &MainWindowController::signalOpenIncident);
        this->w->addIncidentWidget(widget);
    }

}

void MainWindowController::setScenariesList(QList<SecurityScenario> scenaries) {
    this->w->openScenarioMenu();

    for (SecurityScenario sc : scenaries) {
        ScenarioWidget * widget = new ScenarioWidget(sc.getId(), sc.getText());
        QObject::connect(widget, &ScenarioWidget::signalScenarioOpen, this, &MainWindowController::signalOpenScenario);
        QObject::connect(widget, &ScenarioWidget::signalClarify, this, &MainWindowController::onClarifyEvents);
        this->w->addScenarioWidget(widget);
    }
}

void MainWindowController::setRecommendationsList(QList<SecurityRecommendations> scenaries) {
    this->w->openRecommendationMenu();
    SecurityRecommendations rec = scenaries.at(0);
    RecommendationsWidget * widget = new RecommendationsWidget(rec.getTextContainment(), rec.getTextFixes(), rec.getTextRestore());
    this->w->setRemmendationWidget(widget);

}

void MainWindowController::onClarifyEvents() {
    this->w->openMainMenu();
}
