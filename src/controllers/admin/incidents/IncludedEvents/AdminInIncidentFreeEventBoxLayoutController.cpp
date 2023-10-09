#include "AdminInIncidentFreeEventBoxLayoutController.h"

AdminInIncidentFreeEventBoxLayoutController::AdminInIncidentFreeEventBoxLayoutController(QObject *parent) : QObject{parent} {}

AdminInIncidentFreeEventBoxLayoutController::~AdminInIncidentFreeEventBoxLayoutController() {
    delete this->boxLayoutEvents;
}

SecurityEvent AdminInIncidentFreeEventBoxLayoutController::addFreeEvent(SecurityEvent event) {
    freeEvents.append(event);

    return event;
}

void AdminInIncidentFreeEventBoxLayoutController::addFreeEventWidget(SecurityEvent event) {
    InIncidentEventWidget *eventWidget = new InIncidentEventWidget(event.getId(), event.getText());

    this->widgetStorage.appendWidget(eventWidget);
    this->boxLayoutEvents->addEventWidget(eventWidget);
}

void AdminInIncidentFreeEventBoxLayoutController::addDisabledFreeEvent(SecurityEvent event) {
    freeEvents.append(event);

    InIncidentEventWidget *eventWidget = new InIncidentEventWidget(event.getId(), event.getText());

    this->widgetStorage.appendWidget(eventWidget);
    this->boxLayoutEvents->addEventWidget(eventWidget);

    eventWidget->setEnabled(false);
}

void AdminInIncidentFreeEventBoxLayoutController::deleteFreeEvent(quint32 eventID) {
    for(SecurityEvent &event : freeEvents) {
        if(event.getId() == eventID) {
            freeEvents.removeOne(event);
        }
    }

    this->onFreeEventUnselected(eventID);
}

void AdminInIncidentFreeEventBoxLayoutController::deleteFreeEventWidget(quint32 eventID) {
    InIncidentEventWidget *tempWidget = this->widgetStorage.getEventWidget(eventID);

    this->widgetStorage.removeWidget(eventID);
    this->boxLayoutEvents->deleteEventWidget(tempWidget);
}

void AdminInIncidentFreeEventBoxLayoutController::renameFreeEvent(const quint32 eventID, QString newEventTitle) {
    for(SecurityEvent &event : freeEvents) {
        if(event.getId() == eventID) {


            event.setText(newEventTitle);

            this->widgetStorage.getEventWidget(eventID)->setTitle(newEventTitle);
        }
    }
}

void AdminInIncidentFreeEventBoxLayoutController::unselectAllFreeEvents() {
    for(SecurityEvent event : selectedFreeEvents) {

        this->boxLayoutEvents->unselectEventWidget(this->widgetStorage.getEventWidget(event.getId()));
    }
}

void AdminInIncidentFreeEventBoxLayoutController::enableAllFreeEvents() {
    for(SecurityEvent event : freeEvents) {

        this->boxLayoutEvents->enableEventWidget(this->widgetStorage.getEventWidget(event.getId()));
    }
}

void AdminInIncidentFreeEventBoxLayoutController::disableAllFreeEvents() {
    for(SecurityEvent event : freeEvents) {

        this->boxLayoutEvents->disableEventWidget(this->widgetStorage.getEventWidget(event.getId()));
    }
}

void AdminInIncidentFreeEventBoxLayoutController::onFreeEventSelected(const quint32 eventID) {

    quint32 eventsChecked = 0;
    for(SecurityEvent event : freeEvents) {
        if(event.getId() != eventID)
            eventsChecked++;
    }

    /*if(eventsChecked == events.size()) {
        throw
    }*/


    eventsChecked = 0;
    for(SecurityEvent selectedFreeEvent : selectedFreeEvents) {
        if(selectedFreeEvent.getId() == eventID)
            eventsChecked++;
    }

    if(eventsChecked != 1) {

        for(quint32 i = 0; i < freeEvents.size(); i++) {
            SecurityEvent event = this->freeEvents.at(i);
            if(event.getId() == eventID) {
                this->selectedFreeEvents.append(event);

            }
        }
    }

    //else throw

    if(!selectedFreeEvents.isEmpty())
        emit signalSelectedFreeEventsNotEmpty();
}

void AdminInIncidentFreeEventBoxLayoutController::onFreeEventUnselected(const quint32 eventID) {

    quint32 eventsChecked = 0;
    for(SecurityEvent event : freeEvents) {
        if(event.getId() != eventID)
            eventsChecked++;
    }

    //if(eventsChecked == events.size())
        //throw

    eventsChecked = 0;
    for(SecurityEvent selectedFreeEvent : selectedFreeEvents) {
        if(selectedFreeEvent.getId() == eventID)
            eventsChecked++;
    }

    if(eventsChecked != 1) {
        //throw
    }

    else {

        for(quint32 i = 0; i < selectedFreeEvents.size(); i++) {
            SecurityEvent selectedEvent = this->selectedFreeEvents.at(i);
            if(selectedEvent.getId() == eventID)
                this->selectedFreeEvents.removeOne(selectedEvent);
        }
    }

    if(selectedFreeEvents.isEmpty())
        emit signalSelectedFreeEventsEmpty();
}


void AdminInIncidentFreeEventBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutInCategoryEvents) {
    this->boxLayoutEvents = new AdminInIncidentEventBoxLayout();
    this->boxLayoutEvents->init(editMenuBoxLayoutInCategoryEvents);

    QObject::connect(this->boxLayoutEvents, &AdminInIncidentEventBoxLayout::signalEventSelected, this, &AdminInIncidentFreeEventBoxLayoutController::onFreeEventSelected);
    QObject::connect(this->boxLayoutEvents, &AdminInIncidentEventBoxLayout::signalEventUnselected, this, &AdminInIncidentFreeEventBoxLayoutController::onFreeEventUnselected);

}

void AdminInIncidentFreeEventBoxLayoutController::setFreeEventList(const QList<SecurityEvent> events) {
    this->freeEvents = events;
    this->boxLayoutEvents->clearEvents();

    for (SecurityEvent event : events) {

        this->addFreeEventWidget(event);
    }
}

void AdminInIncidentFreeEventBoxLayoutController::slotUnincludeEventsFromIncident(QList<SecurityEvent> includedEvents) {
    for(SecurityEvent includedEvent : includedEvents) {

        //if(this->freeEvents.contains(includedEvent) || this->selectedFreeEvents.contains(includedEvent))
            // throw

        this->slotAddFreeEvent(includedEvent.getId(), includedEvent.getText());
    }
}

void AdminInIncidentFreeEventBoxLayoutController::slotAddFreeEvent(quint32 eventID, QString eventTitle) {
    SecurityEvent newEvent(eventID, eventTitle);

    this->addFreeEvent(newEvent);
    this->addFreeEventWidget(newEvent);
}

void AdminInIncidentFreeEventBoxLayoutController::slotDeleteFreeEvent(quint32 eventID) {
    this->deleteFreeEventWidget(eventID);
    this->deleteFreeEvent(eventID);
}

void AdminInIncidentFreeEventBoxLayoutController::slotAddSelectedEventsToIncidentButtonPressed() {
    emit freeEventsIncludedInIncident(selectedFreeEvents);

    for(SecurityEvent selectedFreeEvent : selectedFreeEvents) {

        this->slotDeleteFreeEvent(selectedFreeEvent.getId());
    }
}

void AdminInIncidentFreeEventBoxLayoutController::clearFreeEventList(const quint32 eventID) {
    this->freeEvents.clear();

    this->unselectAllFreeEvents();
    this->selectedFreeEvents.clear();

    this->boxLayoutEvents->clearEvents();
    this->widgetStorage.clear();
}
