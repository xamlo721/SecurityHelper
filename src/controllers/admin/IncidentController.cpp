#include "IncidentController.h"

IncidentController::IncidentController(QObject *parent) : QObject(parent) {

}

void IncidentController::init(AdminIncidentsWidget *incidentWidget) {
    this->ui = incidentWidget;
    this->editDialog = new AdminIncidentDialog(incidentWidget);

    QObject::connect(this->ui, &AdminIncidentsWidget::signalIncidentClicked, this, &IncidentController::onIncidentSelected);
    QObject::connect(this->ui, &AdminIncidentsWidget::signalAddIncidentClicked, this, &IncidentController::onIncidentAdded);
    QObject::connect(this->ui, &AdminIncidentsWidget::signaEditIncidentClicked, this, &IncidentController::onIncidentEditRequest);
    QObject::connect(this->ui, &AdminIncidentsWidget::signaSaveIncidentClicked, this, &IncidentController::onIncidentUpdated);
    QObject::connect(this->ui, &AdminIncidentsWidget::signalDelIncidentClicked, this, &IncidentController::onIncidentDeleted);

    QObject::connect(this->ui, &AdminIncidentsWidget::signalSelectedEventClicked, this, &IncidentController::onEventUnselected);
    QObject::connect(this->ui, &AdminIncidentsWidget::signaAvailableEventClicked, this, &IncidentController::onEventSelected);

}

void IncidentController::onDatabaseUpdated(const Database & db) {
    copyDatabase = db;

    this->ui->clearSelectedEvents();
    this->ui->clearAvailableEvents();
    this->ui->clearIncidents();

    this->availableEvents.clear();
    this->selectedEvents.clear();

    this->incidents = db.incidents;
    this->allEvents = db.events;

    //Отобразить все категории в списке
    for (const SecurityIncident incident : db.incidents) {
        this->ui->addIncident(new SelectedWidget(incident.getId(), incident.getText()));
    }

    //Назодим среди всех событий те, которые никуда не входят
    QMap<quint32, SecurityEvent> freeEvents = db.events;

    for (const SecurityIncident incident : db.incidents) {

        for (const quint32 eventID : incident.getEventIds()) {

            if (freeEvents.contains(eventID)) {
                freeEvents.remove(eventID);
            }

        }

    }

    //Отобразить все события, не входящие в какие либо категории
    for (const SecurityEvent event : freeEvents) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }

    availableEvents = freeEvents.values();

}


void IncidentController::onIncidentSelected(quint32 incidentID) {

    //Сбрасывает всё что ты накрутил там
    this->onDatabaseUpdated(this->copyDatabase);

    this->selectedEvents.clear();
    this->ui->clearSelectedEvents();
    SecurityIncident incident = incidents.value(incidentID);

    for (quint32 eventID : incident.getEventIds()) {

        for (SecurityEvent event : allEvents) {
            if (event.getId() == eventID && !selectedEvents.contains(event)) {
                this->selectedEvents.append(event);
            }
        }
    }

    for (SecurityEvent event : selectedEvents) {
        this->ui->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }

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
