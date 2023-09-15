#include "MainWindowController.h"

void MainWindowController::setCategoryList(QList<SecurityEventCategory> categories) {
    this->categories = categories;
    this->w->clearCategoryList();
    for (SecurityEventCategory cat : categories) {
        EventCategoryWidget * categoryWidget = new EventCategoryWidget(cat.getId(), cat.getText());
        QObject::connect(categoryWidget, &EventCategoryWidget::signalOpenIncident, this, &MainWindowController::signalOpenCategory);

        this->w->addCategory(categoryWidget);
    }
}

void MainWindowController::setEventList(QList<SecurityEvent> events) {
    this->availableEvents = events;

    //TODO: Вычесть те, которые уже отображены
    this->w->clearCategoryEventList();

    for (SecurityEvent event : events) {
        EventWidget * eventWidget = new EventWidget(event.getId(), event.getText(), false);
        QObject::connect(eventWidget, &EventWidget::signalEventSelected, this, &MainWindowController::onEventSelected);

        this->w->addCategoryEvent(eventWidget);
    }

}

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


void MainWindowController::onEventSelected(quint32 eventID) {

    ///1) Найти и переложить событие

    //TODO: Проверка, что он его вообще содержит!
    for (quint32 i = 0; i < availableEvents.size(); i++) {
        SecurityEvent event = availableEvents.at(i);
        if (event.getId() == eventID) {
            this->activeEvents.append(availableEvents.takeAt(i));
        }
    }

    ///2) Почистить доступные ивенты от него

    //TODO: Вычесть те, которые уже отображены
    this->w->clearCategoryEventList();
    for (SecurityEvent event : availableEvents) {
        EventWidget * eventWidget = new EventWidget(event.getId(), event.getText(), false);
        QObject::connect(eventWidget, &EventWidget::signalEventSelected, this, &MainWindowController::onEventSelected);
        this->w->addCategoryEvent(eventWidget);
    }

    ///3) обновить выбранные ивенты
    this->w->clearSelectedEventList();
    for (SecurityEvent event : activeEvents) {
        EventWidget * eventWidget = new EventWidget(event.getId(), event.getText(), true);
        QObject::connect(eventWidget, &EventWidget::signalEventSelected, this, &MainWindowController::onEventUnselected);
        this->w->addSelectedEvent(eventWidget);
    }


}

void MainWindowController::onEventUnselected(quint32 eventID) {

    ///1) Найти и переложить событие

    //TODO: Проверка, что он его вообще содержит!
    for (quint32 i = 0; i < activeEvents.size(); i++) {
        SecurityEvent event = activeEvents.at(i);
        if (event.getId() == eventID) {
            this->availableEvents.append(activeEvents.takeAt(i));
        }
    }


    ///2) Почистить доступные ивенты от него

    //TODO: Вычесть те, которые уже отображены
    this->w->clearCategoryEventList();
    for (SecurityEvent event : availableEvents) {
        EventWidget * eventWidget = new EventWidget(event.getId(), event.getText(), false);
        QObject::connect(eventWidget, &EventWidget::signalEventSelected, this, &MainWindowController::onEventSelected);
        this->w->addCategoryEvent(eventWidget);
    }


    ///3) обновить выбранные ивенты
    this->w->clearSelectedEventList();
    for (SecurityEvent event : activeEvents) {
        EventWidget * eventWidget = new EventWidget(event.getId(), event.getText(), true);
        QObject::connect(eventWidget, &EventWidget::signalEventSelected, this, &MainWindowController::onEventUnselected);
        this->w->addSelectedEvent(eventWidget);
    }


}
void MainWindowController::onClarifyEvents() {
    this->w->openMainMenu();
}

void MainWindowController::setAdminCategoryList(QList<SecurityEventCategory> categories) {
    this->categories = categories;
    this->w->clearCategoryList();
    for (SecurityEventCategory cat : categories) {
        EditableEventCategoryWidget *editableCategoryWidget = new EditableEventCategoryWidget(new EventCategoryWidget(cat.getId(), cat.getText()));
        this->w->addEditableCategory(editableCategoryWidget);
    }
}

void MainWindowController::setAdminEventList(QList<SecurityEvent> events) {
    this->availableEvents = events;

    //TODO: Вычесть те, которые уже отображены
    this->w->clearCategoryEventList();

    for (SecurityEvent event : events) {
        EditableEventWidget * editableEventWidget = new EditableEventWidget(new EventWidget(event.getId(), event.getText(), false));
        //EventWidget * eventWidget = new EventWidget(event.getId(), event.getText(), false);
        this->w->addEditableCategoryEvent(editableEventWidget);
    }

}
