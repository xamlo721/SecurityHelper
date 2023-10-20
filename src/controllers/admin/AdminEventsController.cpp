#include "AdminEventsController.h"

AdminEventsController::AdminEventsController(QObject *parent) : QObject(parent)
{

}
void AdminEventsController::init(AdminEventsWidget *eventsWidget) {
    this->ui = eventsWidget;
    //QObject::connect(this->ui, &AdminEventsWidget::signalEventClicked, this, &AdminEventsController::onCetegorySelected);
    QObject::connect(this->ui, &AdminEventsWidget::signalAddEventClicked, this, &AdminEventsController::onEventAdded);
    QObject::connect(this->ui, &AdminEventsWidget::signalEditEventClicked, this, &AdminEventsController::onEventEdited);
    QObject::connect(this->ui, &AdminEventsWidget::signalDelEventClicked, this, &AdminEventsController::onEventDeleted);

}


void AdminEventsController::onDatabaseUpdated(const Database & db) {
    copyDatabase = db;

    this->ui->clearEvents();
    this->allEvents = db.events;

    //Отобразить все категории в списке
    for (const SecurityEvent event : db.events) {
        this->ui->addEvent(new SelectedWidget(event.getId(), event.getText()));
    }

}


void AdminEventsController::onEventAdded() {

    //Вызвать создание категории из ядра
    emit signalAdminAddEvent();


}

void AdminEventsController::onEventEdited(quint32 eventID, QString eventName) {

    SecurityEvent updatedEvent (eventID, eventName);
    emit signalAdminUpdateEvent(eventID, updatedEvent);
}

void AdminEventsController::onEventDeleted(quint32 eventID) {
    emit signalAdminDeleteEvent(eventID);
}
