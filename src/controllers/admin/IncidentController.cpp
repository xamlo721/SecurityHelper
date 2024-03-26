#include "IncidentController.h"

IncidentController::IncidentController(QObject *parent) : QObject(parent) {

}

void IncidentController::init(AdminIncidentsWidget *incidentWidget) {
    this->ui = incidentWidget;
    this->editDialog = new AdminIncidentDialog(incidentWidget);
    this->selectedIncidentID = -1;

    QObject::connect(this->ui, &AdminIncidentsWidget::signalIncidentSelected, this, &IncidentController::onIncidentSelected);
    QObject::connect(this->ui, &AdminIncidentsWidget::signalIncidentUnselected, this, &IncidentController::onIncidentUnselected);
    QObject::connect(this->ui, &AdminIncidentsWidget::signalAddIncidentClicked, this, &IncidentController::onIncidentAdded);
    QObject::connect(this->ui, &AdminIncidentsWidget::signaEditIncidentClicked, this, &IncidentController::onIncidentEditRequest);
    QObject::connect(this->ui, &AdminIncidentsWidget::signaSaveIncidentClicked, this, &IncidentController::onIncidentUpdated);
    QObject::connect(this->ui, &AdminIncidentsWidget::signalDelIncidentClicked, this, &IncidentController::onIncidentDeleted);

    QObject::connect(this->ui, &AdminIncidentsWidget::signalSelectedEventClicked, this, &IncidentController::onEventUnselected);
    QObject::connect(this->ui, &AdminIncidentsWidget::signaAvailableEventClicked, this, &IncidentController::onEventSelected);

    this->ui->disableEditButton();
    this->ui->disableSaveButton();
    this->ui->disableDeleteButton();

}


void IncidentController::resetSelectedEvents(QList<SecurityEvent> selectedEvents) {
    this->ui->clearSelectedEvents();
    this->selectedEvents = selectedEvents;

    //Отобразить все события, не входящие в какие либо категории
    for (const SecurityEvent event : selectedEvents) {
        this->ui->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }


}

void IncidentController::resetAvailableEvents(QList<SecurityEvent> freeEvents) {
    this->ui->clearAvailableEvents();
    this->availableEvents = freeEvents;

    //Назодим среди всех событий те, которые никуда не входят

    for (const SecurityEvent event : availableEvents) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }


}


void IncidentController::onDatabaseUpdated(const Database & db) {

    this->allEvents = db.events;

    this->copyDatabase = db;

    this->ui->clearIncidents();

    this->incidents = db.incidents;

    //Отобразить все категории в списке
    for (const SecurityIncident incident : db.incidents) {
        this->ui->addIncident(new SelectedWidget(incident.getId(), incident.getText()));
    }

    this->ui->clearSelectedEvents();
    this->selectedEvents.clear();

    this->ui->clearAvailableEvents();
    this->availableEvents.clear();


}


void IncidentController::onIncidentSelected(quint32 incidentID) {

    ///Для поиска доступных ивентов, сначала скопируем все ивенты, затем удалим
    QMap<quint32, SecurityEvent> copyAllEvents = this->copyDatabase.events;

    ///Поиск среди всех доступных категорий
    for (SecurityIncident incident : this->copyDatabase.incidents) {
        ///Среди всех событий категории
        for (quint32 eventID : incident.getEventIds()) {
            ///Если категория содержит такой ID, значит не доступен он!
            if (copyAllEvents.contains(eventID)) {
                copyAllEvents.remove(eventID);
            }

        }
    }

    QList<SecurityEvent> incidentSelectedEvents;

    SecurityIncident selectedIncident = incidents.value(incidentID);

    for (quint32 eventID : selectedIncident.getEventIds()) {
        incidentSelectedEvents.append(this->allEvents.value(eventID));
    }

    this->resetAvailableEvents(copyAllEvents.values());
    this->resetSelectedEvents(incidentSelectedEvents);

    ///Запоминаем ID кого мы там нажали и включаем кнопки редактирования
    this->selectedIncidentID = incidentID;
    this->ui->enableEditButton();
    this->ui->enableSaveButton();
    this->ui->enableDeleteButton();

}

void IncidentController::onIncidentUnselected(quint32 incidentID) {
    ///Если ID совпали, то мы отжали кнопку
    if (this->selectedIncidentID != incidentID) {
        //А как мы сюда попали?
        throw "onCetegoryUnselected()";
        return;
    }

    this->selectedIncidentID = -1;
    this->ui->disableEditButton();
    this->ui->disableSaveButton();
    this->ui->disableDeleteButton();


    this->selectedEvents.clear();
    this->availableEvents.clear();

    this->resetAvailableEvents(this->availableEvents);
    this->resetSelectedEvents(this->selectedEvents);

}


void IncidentController::onIncidentEditRequest(quint32 incidentID) {
    this->editDialog->show();
}


void IncidentController::onIncidentAdded() {

    //Вызвать создание категории из ядра
    emit signalAdminAddIncident();


}

void IncidentController::onIncidentUpdated(quint32 incidentID, QString incidentName) {

    QList<quint32> selectedEventIDs;
    for (SecurityEvent event : this->selectedEvents) {
        selectedEventIDs.append(event.getId());
    }
    SecurityIncident updatedIncident (incidentID, incidentName, "", selectedEventIDs); //FIXME: Добавить параметр
    emit signalAdminUpdateIncident(incidentID, updatedIncident);
    this->onIncidentUnselected(incidentID);
}

void IncidentController::onIncidentDeleted(quint32 incidentID) {
    emit signalAdminDeleteIncident(incidentID);
}

void IncidentController::onEventSelected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedEvents.append(allEvents.value(eventID));
    this->availableEvents.removeOne(allEvents.value(eventID));

    ///2) Почистить доступные ивенты от него
    this->ui->clearAvailableEvents();
    this->ui->clearSelectedEvents();

    for (SecurityEvent event : availableEvents) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }

    ///3) обновить выбранные ивенты
    for (SecurityEvent event : selectedEvents) {
        this->ui->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }

}

void IncidentController::onEventUnselected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedEvents.removeOne(allEvents.value(eventID));
    this->availableEvents.append(allEvents.value(eventID));

    ///2) Почистить доступные ивенты от него
    this->ui->clearAvailableEvents();
    this->ui->clearSelectedEvents();

    for (SecurityEvent event : availableEvents) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }

    ///3) обновить выбранные ивенты
    for (SecurityEvent event : selectedEvents) {
        this->ui->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }


}
