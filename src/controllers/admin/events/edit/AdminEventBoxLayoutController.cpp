#include "AdminEventBoxLayoutController.h"

#include "src/ui/admin/ItemDeletionMessageBox.h"
#include "src/ui/admin/EnumMessageBoxVariants.h"
#include "src/ui/admin/EnumMessageBoxItemVariants.h"

AdminEventBoxLayoutController::AdminEventBoxLayoutController(QObject *parent) : QObject{parent} {}

void AdminEventBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutEvents) {

    this->boxLayoutEvents = new AdminEventBoxLayout();

    this->boxLayoutEvents->init(editMenuBoxLayoutEvents);


    QObject::connect(this->boxLayoutEvents, &AdminEventBoxLayout::signalEditEvent, this, &AdminEventBoxLayoutController::slotShowEditableWidget);
    QObject::connect(this->boxLayoutEvents, &AdminEventBoxLayout::signalDeleteEvent, this, &AdminEventBoxLayoutController::slotDeleteEvent);

    QObject::connect(this->boxLayoutEvents, &AdminEventBoxLayout::signalEventSelected, this, &AdminEventBoxLayoutController::onEventSelected);
    QObject::connect(this->boxLayoutEvents, &AdminEventBoxLayout::signalEventUnselected, this, &AdminEventBoxLayoutController::onEventUnselected);


    QObject::connect(this->boxLayoutEvents, &AdminEventBoxLayout::editingFinished, this, &AdminEventBoxLayoutController::slotShowUneditableWidget);
}

void AdminEventBoxLayoutController::setEventList(const QList<SecurityEvent> events) {

    this->events = events;

    this->boxLayoutEvents->clearEvents();

    for (SecurityEvent event : events) {

        this->addEventWidget(event);
    }

    emit eventListSet();
}

void AdminEventBoxLayoutController::slotShowEditableWidget(UneditableEventWidget *uneditableWidget) {

    EditableEventWidget *editableWidget = this->widgetStorage.getEditableWidget(uneditableWidget->getID());

    this->boxLayoutEvents->showEditableWidget(uneditableWidget, editableWidget);


    this->unselectAllEvents();

    this->disableAllEvents();


    emit eventIsActive();
}

void AdminEventBoxLayoutController::slotShowUneditableWidget(EditableEventWidget *editableWidget) {

    UneditableEventWidget *uneditableWidget = this->widgetStorage.getUneditableWidget(editableWidget->getID());


    this->renameEvent(editableWidget->getID(), editableWidget->getTitle());


    uneditableWidget->setTitle(editableWidget->getTitle());

    emit eventsMustBeSaved(this->events);


    this->boxLayoutEvents->showUneditableWidget(editableWidget, uneditableWidget);


    this->enableAllEvents();

    emit eventIsNotActive();
}

SecurityEvent AdminEventBoxLayoutController::addEvent() {
    quint32 newEventId = 0;
    for(SecurityEvent event : events) {
        if(newEventId < event.getId())
            newEventId = event.getId();
    }
    newEventId += 1;


    SecurityEvent newEvent(newEventId, "Новое событие");

    events.append(newEvent);


    emit eventAdded(newEvent);

    return newEvent;
}

void AdminEventBoxLayoutController::addEventWidget(const SecurityEvent event) {

    UneditableEventWidget *uneditableWidget = new UneditableEventWidget(event.getId(), event.getText());
    EditableEventWidget *editableWidget = new EditableEventWidget(event.getId(), event.getText());

    this->widgetStorage.appendWidget(uneditableWidget, editableWidget);
    this->boxLayoutEvents->addEventWidget(uneditableWidget, editableWidget);
}

void AdminEventBoxLayoutController::deleteEvent(const quint32 eventID) {

    for(SecurityEvent &event : events) {
        if(event.getId() == eventID) {

            if(this->selectedEvents.contains(event))
                this->onEventUnselected(event.getId());

            events.removeOne(event);
        }
    }    

    emit eventDeleted(eventID);
}

void AdminEventBoxLayoutController::deleteEventWidget(const quint32 eventID) {
    UneditableEventWidget *tempWidget = this->widgetStorage.getUneditableWidget(eventID);
    this->widgetStorage.removeWidget(eventID);
    this->boxLayoutEvents->deleteEventWidget(tempWidget);
}

void AdminEventBoxLayoutController::renameEvent(const quint32 widgetID, const QString widgetText) {

    quint32 eventID;
    QString newEventTitle;
    for(SecurityEvent &event : events) {
        if(event.getId() == widgetID) {

            event.setText(widgetText);

            eventID = event.getId();
            newEventTitle = widgetText;
        }
    }

    emit eventRenamed(eventID, newEventTitle);
}

void AdminEventBoxLayoutController::unselectAllEvents() {
    for(SecurityEvent event : selectedEvents) {

        this->boxLayoutEvents->unselectUneditableWidget(this->widgetStorage.getUneditableWidget(event.getId()));
    }
}

void AdminEventBoxLayoutController::enableAllEvents() {
    for(SecurityEvent event : events) {

        this->boxLayoutEvents->enableUneditableWidget(this->widgetStorage.getUneditableWidget(event.getId()));
    }
}

void AdminEventBoxLayoutController::disableAllEvents() {
    for(SecurityEvent event : events) {

        this->boxLayoutEvents->disableUneditableWidget(this->widgetStorage.getUneditableWidget(event.getId()));
    }
}

void AdminEventBoxLayoutController::slotDeleteEvent(UneditableEventWidget * uneditableWidget) {

    ItemDeletionMessageBox messageBox;

    if(messageBox.openWarning(EnumMessageBoxVariants::DeletionOneItem, EnumMessageBoxItemVariants::Event) == ItemDeletionMessageBox::Yes) {

        this->deleteEventWidget(uneditableWidget->getID());
        this->deleteEvent(uneditableWidget->getID());

        /// Производим разблокировку интерфейса
        this->enableAllEvents();
        emit eventIsNotActive();
    }
}

void AdminEventBoxLayoutController::slotAddEventButtonPressed() {
    this->addEventWidget(this->addEvent());
}

void AdminEventBoxLayoutController::slotDeleteSelectedEventsButtonPressed() {

    ItemDeletionMessageBox messageBox;

    if(messageBox.openWarning(EnumMessageBoxVariants::DeletionSeveralItems, EnumMessageBoxItemVariants::Event) == ItemDeletionMessageBox::Yes) {


        for(SecurityEvent &event : selectedEvents) {

            this->deleteEventWidget(event.getId());
            this->deleteEvent(event.getId());

            /// Производим разблокировку интерфейса
            this->enableAllEvents();
            emit eventIsNotActive();
        }
    }
}

void AdminEventBoxLayoutController::onEventSelected(const quint32 eventID) {

    quint32 eventsChecked = 0;
    for(SecurityEvent event : events) {
        if(event.getId() != eventID)
            eventsChecked++;
    }

    /*if(eventsChecked == events.size()) {
        throw
    }*/


    eventsChecked = 0;
    for(SecurityEvent selectedEvent : selectedEvents) {
        if(selectedEvent.getId() == eventID)
            eventsChecked++;
    }

    if(eventsChecked != 1) {

        for(quint32 i = 0; i < events.size(); i++) {
            SecurityEvent event = this->events.at(i);

            if(event.getId() == eventID)
                this->selectedEvents.append(event);
        }
    }

    // else throw

    if(!selectedEvents.isEmpty())
        emit signalSelectedEventsNotEmpty();
}

void AdminEventBoxLayoutController::onEventUnselected(const quint32 eventID) {

    quint32 eventsChecked = 0;
    for(SecurityEvent event : events) {
        if(event.getId() != eventID)
            eventsChecked++;
    }

    //if(eventsChecked == events.size())
        //throw


    eventsChecked = 0;
    for(SecurityEvent selectedEvent : selectedEvents) {
        if(selectedEvent.getId() == eventID)
            eventsChecked++;
    }

    if(eventsChecked != 1) {
        //throw
    }

    else {

        for(quint32 i = 0; i < selectedEvents.size(); i++) {
            SecurityEvent selectedEvent = this->selectedEvents.at(i);

            if(selectedEvent.getId() == eventID)
                this->selectedEvents.removeOne(selectedEvent);
        }
    }

    if(selectedEvents.isEmpty())
        emit signalSelectedEventsEmpty();
}
