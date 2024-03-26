#include "AdminEventsController.h"

AdminEventsController::AdminEventsController(QObject *parent) \
    : QObject(parent) {

}
void AdminEventsController::init(AdminEventsWidget *eventsWidget) {
    this->ui = eventsWidget;
    this->editDialog = new AdminEventDialog(eventsWidget);
    this->selectedEventID = -1;

    QObject::connect(this->ui, &AdminEventsWidget::signalAddEventClicked, this, &AdminEventsController::onEventAdded);
    QObject::connect(this->ui, &AdminEventsWidget::signalEditEventClicked, this, &AdminEventsController::onEventEditRequest);
    QObject::connect(this->ui, &AdminEventsWidget::signalSaveEventClicked, this, &AdminEventsController::onEventUpdated);
    QObject::connect(this->ui, &AdminEventsWidget::signalDelEventClicked, this, &AdminEventsController::onEventDeleted);
    QObject::connect(this->ui, &AdminEventsWidget::signalEventSelected, this, &AdminEventsController::slotOnEventSelected);
    QObject::connect(this->ui, &AdminEventsWidget::signalEventUnselected, this, &AdminEventsController::slotOnEventUnselected);

    this->ui->disableEditButton();
    this->ui->disableDeleteButton();
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

/**
 * @brief slotOnEventButtonPressed - слот. активируемый при нажатии
 * на нажатии на кнопку События.
 */
void AdminEventsController::slotOnEventSelected(quint32 eventId) {

    ///Запоминаем ID кого мы там нажали и включаем кнопки редактирования
    this->selectedEventID = eventId;
    this->ui->enableEditButton();
    this->ui->enableDeleteButton();

}

/**
 * @brief slotOnEventButtonPressed - слот. активируемый при нажатии
 * на нажатии на кнопку События.
 */
void AdminEventsController::slotOnEventUnselected(quint32 eventId) {

    ///Если ID совпали, то мы отжали кнопку
    if (this->selectedEventID != eventId) {
        //А как мы сюда попали?
        throw "AdminEventsController()";
        return;
    }

    this->selectedEventID = -1;
    this->ui->disableEditButton();
    this->ui->disableDeleteButton();

}

void AdminEventsController::onEventAdded() {

    //Вызвать создание категории из ядра
    emit signalAdminAddEvent();


}

void AdminEventsController::onEventUpdated(quint32 eventID, QString eventName) {

    SecurityEvent updatedEvent (eventID, eventName);
    emit signalAdminUpdateEvent(eventID, updatedEvent);
}

void AdminEventsController::onEventEditRequest(quint32 eventID) {
    this->editDialog->show();
    this->editDialog->setEditableText(this->allEvents.value(eventID).getText());
}

void AdminEventsController::onEventDeleted(quint32 eventID) {
    emit signalAdminDeleteEvent(eventID);
}
