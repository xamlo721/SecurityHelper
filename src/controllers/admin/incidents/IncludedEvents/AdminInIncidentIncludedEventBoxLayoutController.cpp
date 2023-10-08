#include "AdminInIncidentIncludedEventBoxLayoutController.h"

AdminInIncidentIncludedEventBoxLayoutController::AdminInIncidentIncludedEventBoxLayoutController(QObject *parent) : QObject{parent} {}

AdminInIncidentIncludedEventBoxLayoutController::~AdminInIncidentIncludedEventBoxLayoutController() {
    delete this->boxLayoutEvents;
}

SecurityEvent AdminInIncidentIncludedEventBoxLayoutController::addIncludedEvent(SecurityEvent event) {
    includedEvents.append(event);

    return event;
}

void AdminInIncidentIncludedEventBoxLayoutController::addIncludedEventWidget(SecurityEvent event) {
    InIncidentEventWidget *eventWidget = new InIncidentEventWidget(event.getId(), event.getText());

    this->widgetStorage.appendWidget(eventWidget);
    this->boxLayoutEvents->addEventWidget(eventWidget);
}

void AdminInIncidentIncludedEventBoxLayoutController::deleteIncludedEvent(quint32 eventID) {

    for(SecurityEvent &event : includedEvents) {
        if(event.getId() == eventID) {
            includedEvents.removeOne(event);
        }
    }

    this->onIncludedEventUnselected(eventID);
}

void AdminInIncidentIncludedEventBoxLayoutController::deleteIncludedEventWidget(quint32 eventID) {
    InIncidentEventWidget *tempWidget = this->widgetStorage.getEventWidget(eventID);

    this->widgetStorage.removeWidget(eventID);
    this->boxLayoutEvents->deleteEventWidget(tempWidget);
}

void AdminInIncidentIncludedEventBoxLayoutController::renameIncludedEvent(const quint32 eventID, QString newEventTitle) {
    for(SecurityEvent &event : includedEvents) {
        if(event.getId() == eventID) {

            /// Изменяем имя события
            event.setText(newEventTitle);
            /// Изменяем имя виджета этого события
            this->widgetStorage.getEventWidget(eventID)->setTitle(newEventTitle);
        }
    }
}

void AdminInIncidentIncludedEventBoxLayoutController::unselectAllIncludedEvents() {
    for(SecurityEvent event : selectedIncludedEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его не выбранным
        this->boxLayoutEvents->unselectEventWidget(this->widgetStorage.getEventWidget(event.getId()));
    }
}

void AdminInIncidentIncludedEventBoxLayoutController::enableAllIncludedEvents() {
    for(SecurityEvent event : includedEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его доступным
        this->boxLayoutEvents->enableEventWidget(this->widgetStorage.getEventWidget(event.getId()));
    }
}

void AdminInIncidentIncludedEventBoxLayoutController::disableAllIncludedEvents() {
    for(SecurityEvent event : includedEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его не доступным
        this->boxLayoutEvents->disableEventWidget(this->widgetStorage.getEventWidget(event.getId()));
    }
}

void AdminInIncidentIncludedEventBoxLayoutController::onIncludedEventSelected(const quint32 eventID) {
    // Проверка, есть ли в списке событий такое событие
    quint32 eventsChecked = 0;
    for(SecurityEvent event : includedEvents) {
        if(event.getId() != eventID)
            eventsChecked++;
    }

    /*if(eventsChecked == events.size()) {
        throw
    }*/


    eventsChecked = 0;
    for(SecurityEvent selectedIncludedEvent : selectedIncludedEvents) {
        if(selectedIncludedEvent.getId() == eventID)
            eventsChecked++;
    }

    if(eventsChecked != 1) {

        /// Находим и забрасываем событие в список выбранных
        for(quint32 i = 0; i < includedEvents.size(); i++) {
            SecurityEvent event = this->includedEvents.at(i);
            if(event.getId() == eventID) {
                this->selectedIncludedEvents.append(event);

            }
        }
    }

    if(!selectedIncludedEvents.isEmpty())
        emit signalSelectedIncludedEventsNotEmpty();
}

void AdminInIncidentIncludedEventBoxLayoutController::onIncludedEventUnselected(const quint32 eventID) {
    // Проверка, есть ли в списке событий такое событие
    quint32 eventsChecked = 0;
    for(SecurityEvent event : includedEvents) {
        if(event.getId() != eventID)
            eventsChecked++;
    }

    /*if(eventsChecked == events.size()) {
        throw
    }*/


    eventsChecked = 0;
    for(SecurityEvent selectedIncludedEvent : selectedIncludedEvents) {
        if(selectedIncludedEvent.getId() == eventID)
            eventsChecked++;
    }

    if(eventsChecked != 1) {
        //throw
    }

    else {

        /// Находим и удаляем событие из списка выбранных событий
        for(quint32 i = 0; i < selectedIncludedEvents.size(); i++) {
            SecurityEvent selectedEvent = this->selectedIncludedEvents.at(i);
            if(selectedEvent.getId() == eventID)
                this->selectedIncludedEvents.removeOne(selectedEvent);
        }
    }

    if(selectedIncludedEvents.isEmpty())
        emit signalSelectedIncludedEventsEmpty();
}


void AdminInIncidentIncludedEventBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutInCategoryEvents) {
    this->boxLayoutEvents = new AdminInIncidentEventBoxLayout();
    this->boxLayoutEvents->init(editMenuBoxLayoutInCategoryEvents);

    QObject::connect(this->boxLayoutEvents, &AdminInIncidentEventBoxLayout::signalEventSelected, this, &AdminInIncidentIncludedEventBoxLayoutController::onIncludedEventSelected);
    QObject::connect(this->boxLayoutEvents, &AdminInIncidentEventBoxLayout::signalEventUnselected, this, &AdminInIncidentIncludedEventBoxLayoutController::onIncludedEventUnselected);

}

void AdminInIncidentIncludedEventBoxLayoutController::setIncludedEventList(const QList<SecurityEvent> events) {
    this->includedEvents = events;
    this->boxLayoutEvents->clearEvents();

    for (SecurityEvent event : events) {

        this->addIncludedEventWidget(event);
    }
}

void AdminInIncidentIncludedEventBoxLayoutController::clearIncludedEventList(const quint32 categoryID) {
    /// Отправляем сигнал о принудительном сохранении в базу данных событий в категорию
    emit incidentEventsMustBeSaved(categoryID, this->includedEvents);

    this->includedEvents.clear();

    this->unselectAllIncludedEvents();
    this->selectedIncludedEvents.clear();

    this->boxLayoutEvents->clearEvents();
    this->widgetStorage.clear();
}

void AdminInIncidentIncludedEventBoxLayoutController::slotIncludeFreeEventsToIncident(QList<SecurityEvent> freeEvents) {
    for(SecurityEvent freeEvent : freeEvents) {

        //if(this->includedEvents.contains(freeEvent) || this->selectedIncludedEvents.contains(freeEvent))
            // throw

        this->slotAddIncludedEvent(freeEvent.getId(), freeEvent.getText());
    }
}

void AdminInIncidentIncludedEventBoxLayoutController::slotDeleteIncludedEvent(quint32 eventID) {
    this->deleteIncludedEventWidget(eventID);
    this->deleteIncludedEvent(eventID);
}

void AdminInIncidentIncludedEventBoxLayoutController::slotAddIncludedEvent(quint32 eventID, QString eventTitle) {
    SecurityEvent newEvent(eventID, eventTitle);

    this->addIncludedEvent(newEvent);
    this->addIncludedEventWidget(newEvent);
}

void AdminInIncidentIncludedEventBoxLayoutController::slotRemoveSelectedEventsFromIncidentButtonPressed() {
    emit eventsRemovedFromIncident(selectedIncludedEvents);

    for(SecurityEvent selectedIncludedEvent : selectedIncludedEvents) {

        this->slotDeleteIncludedEvent(selectedIncludedEvent.getId());
    }
}
