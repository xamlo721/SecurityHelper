#include "UserScenarioController.h"

UserScenaryController::UserScenaryController(QObject *parent) : QObject{parent} {

}

void UserScenaryController::init(ScenarioMenuWidget *scenarioWidget) {
    scenarioMenuWidget = scenarioWidget;
}

void UserScenaryController::setScenariesList(QList<SecurityScenario> scenaries) {
    clearScenaries();
    for (SecurityScenario sc : scenaries) {
            ScenarioWidget * widget = new ScenarioWidget(sc.getId(), sc.getText(), sc.getName());
            QObject::connect(widget, &ScenarioWidget::signalScenarioOpen, this, &UserScenaryController::slotOnScenaryClicked);
            QObject::connect(widget, &ScenarioWidget::signalClarify, this, &UserScenaryController::signalOnClarifyEvents);
            if (!shownScenariesWidget.contains(widget)) {
                shownScenariesWidget << widget;
            }
            scenarioMenuWidget->addScenarioWidget(widget);
    }
}


void UserScenaryController::clearScenaries() {
    for (ScenarioWidget * widget : shownScenariesWidget) {
        scenarioMenuWidget->closeScenarioWidget(widget);
    }
    shownScenariesWidget.clear();
}

void UserScenaryController::slotOnScenaryClicked(quint32 id) {
    emit signalOpenScenario(id);
    emit signalScenarySelected();
}
