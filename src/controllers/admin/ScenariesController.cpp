#include "ScenariesController.h"

ScenariesController::ScenariesController(QObject *parent) : QObject(parent) {

}

void ScenariesController::init(AdminScenariesWidget *incidentWidget) {
    this->ui = incidentWidget;
    this->editDialog = new AdminScenariesDialog(incidentWidget);

    QObject::connect(this->ui, &AdminScenariesWidget::signalScenaryClicked, this, &ScenariesController::onScenarySelected);
    QObject::connect(this->ui, &AdminScenariesWidget::signalAddScenaryClicked, this, &ScenariesController::onScenaryAdded);
    QObject::connect(this->ui, &AdminScenariesWidget::signaEditScenaryClicked, this, &ScenariesController::onScenaryEditRequest);
    QObject::connect(this->ui, &AdminScenariesWidget::signaSaveScenaryClicked, this, &ScenariesController::onScenaryUpdated);
    QObject::connect(this->ui, &AdminScenariesWidget::signalDelScenaryClicked, this, &ScenariesController::onScenaryDeleted);

    QObject::connect(this->ui, &AdminScenariesWidget::signalSelectedIncidentClicked, this, &ScenariesController::onIncidentUnselected);
    QObject::connect(this->ui, &AdminScenariesWidget::signaAvailableIncidentClicked, this, &ScenariesController::onIncidentSelected);

}

void ScenariesController::onDatabaseUpdated(const Database & db) {
    copyDatabase = db;

    this->ui->clearSelectedIncidents();
    this->ui->clearAvailableIncidents();
    this->ui->clearScenaries();

    this->availableIncidents.clear();
    this->selectedIncidents.clear();

    this->scenaries = db.scenaries;
    this->allIncidents = db.incidents;

    //Отобразить все категории в списке
    for (const SecurityScenario scenary : db.scenaries) {
        this->ui->addScenary(new SelectedWidget(scenary.getId(), scenary.getText()));
    }

    //Назодим среди всех событий те, которые никуда не входят
    QMap<quint32, SecurityIncident> freeIncidents = db.incidents;

    for (const SecurityScenario scenary : db.scenaries) {

        for (const quint32 incidentID : scenary.getIncidents()) {

            if (freeIncidents.contains(incidentID)) {
                freeIncidents.remove(incidentID);
            }

        }

    }

    //Отобразить все инциденты, не входящие в какие либо категории
    for (const SecurityIncident incident : freeIncidents) {
        this->ui->addAvalilableIncident(new SelectedWidget(incident.getId(), incident.getText()));
    }

    availableIncidents = freeIncidents.values();

}


void ScenariesController::onScenarySelected(quint32 scenaryID) {

    //Сбрасывает всё что ты накрутил там
    this->onDatabaseUpdated(this->copyDatabase);

    this->selectedIncidents.clear();
    this->ui->clearSelectedIncidents();
    SecurityScenario scenary = scenaries.value(scenaryID);

    for (quint32 incidentID : scenary.getIncidents()) {

        for (SecurityIncident incident : allIncidents) {
            if (incident.getId() == incidentID && !selectedIncidents.contains(incident)) {
                this->selectedIncidents.append(incident);
            }
        }
    }

    for (SecurityIncident incident : selectedIncidents) {
        this->ui->addSelectedIncident(new SelectedWidget(incident.getId(), incident.getText()));
    }

}


void ScenariesController::onScenaryAdded() {

    //Вызвать создание категории из ядра
    emit signalAdminAddScenary();


}

void ScenariesController::onScenaryUpdated(quint32 scenaryID, QString scenaryName) {

    QList<quint32> selectedIncidentIDs;
    for (SecurityIncident incident : this->selectedIncidents) {
        selectedIncidentIDs.append(incident.getId());
    }
    SecurityScenario updatedIncident (scenaryID, scenaryName, "", selectedIncidentIDs); //FIXME: Добавить параметр
    emit signalAdminUpdateScenary(scenaryID, updatedIncident);
}

void ScenariesController::onScenaryEditRequest(quint32 scenaryID) {
    this->editDialog->show();
}

void ScenariesController::onScenaryDeleted(quint32 scenaryID) {
    emit signalAdminDeleteScenary(scenaryID);
}

void ScenariesController::onIncidentSelected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedIncidents.append(allIncidents.value(eventID));
    this->availableIncidents.removeOne(allIncidents.value(eventID));

    ///2) Почистить доступные ивенты от него
    this->ui->clearAvailableIncidents();
    this->ui->clearSelectedIncidents();

    for (SecurityIncident incident : availableIncidents) {
        this->ui->addAvalilableIncident(new SelectedWidget(incident.getId(), incident.getText()));
    }

    ///3) обновить выбранные ивенты
    for (SecurityIncident incident : selectedIncidents) {
        this->ui->addSelectedIncident(new SelectedWidget(incident.getId(), incident.getText()));
    }

}

void ScenariesController::onIncidentUnselected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedIncidents.removeOne(allIncidents.value(eventID));
    this->availableIncidents.append(allIncidents.value(eventID));

    ///2) Почистить доступные ивенты от него
    this->ui->clearAvailableIncidents();
    this->ui->clearSelectedIncidents();

    for (SecurityIncident incident : availableIncidents) {
        this->ui->addAvalilableIncident(new SelectedWidget(incident.getId(), incident.getText()));
    }

    ///3) обновить выбранные ивенты
    for (SecurityIncident incident : selectedIncidents) {
        this->ui->addSelectedIncident(new SelectedWidget(incident.getId(), incident.getText()));
    }


}
