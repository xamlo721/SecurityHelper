#include "ScenariesController.h"

ScenariesController::ScenariesController(QObject *parent)
    : QObject(parent) {

}


void ScenariesController::resetSelectedIncidents(QList<SecurityIncident> selectedIncidents) {
    this->ui->clearSelectedIncidents();
    this->selectedIncidents = selectedIncidents;

    //Отобразить все события, не входящие в какие либо категории
    for (const SecurityIncident incident : selectedIncidents) {
        this->ui->addSelectedIncident(new SelectedWidget(incident.getId(), incident.getText()));
    }


}

void ScenariesController::resetAvailableIncidents(QList<SecurityIncident> freeIncidents) {
    this->ui->clearAvailableIncidents();
    this->availableIncidents = freeIncidents;

    //Назодим среди всех событий те, которые никуда не входят

    for (const SecurityIncident incident : availableIncidents) {
        this->ui->addAvalilableIncident(new SelectedWidget(incident.getId(), incident.getText()));
    }


}


void ScenariesController::init(AdminScenariesWidget *incidentWidget) {
    this->ui = incidentWidget;
    this->editDialog = new AdminScenariesDialog(incidentWidget);

    QObject::connect(this->ui, &AdminScenariesWidget::signalScenarySelected, this, &ScenariesController::onScenarySelected);
    QObject::connect(this->ui, &AdminScenariesWidget::signalScenaryUnselected, this, &ScenariesController::onScenaryUnselected);
    QObject::connect(this->ui, &AdminScenariesWidget::signalAddScenaryClicked, this, &ScenariesController::onScenaryAdded);
    QObject::connect(this->ui, &AdminScenariesWidget::signaEditScenaryClicked, this, &ScenariesController::onScenaryEditRequest);
    QObject::connect(this->ui, &AdminScenariesWidget::signaSaveScenaryClicked, this, &ScenariesController::onScenaryUpdated);
    QObject::connect(this->ui, &AdminScenariesWidget::signalDelScenaryClicked, this, &ScenariesController::onScenaryDeleted);

    QObject::connect(this->ui, &AdminScenariesWidget::signalSelectedIncidentClicked, this, &ScenariesController::onIncidentUnselected);
    QObject::connect(this->ui, &AdminScenariesWidget::signaAvailableIncidentClicked, this, &ScenariesController::onIncidentSelected);

    this->ui->disableEditButton();
    this->ui->disableSaveButton();
    this->ui->disableDeleteButton();
}

void ScenariesController::onDatabaseUpdated(const Database & db) {


    this->allIncidents = db.incidents;

    this->copyDatabase = db;

    this->ui->clearScenaries();

    this->scenaries = db.scenaries;

    //Отобразить все категории в списке
    for (const SecurityScenario scenario : db.scenaries) {
        this->ui->addScenary(new SelectedWidget(scenario.getId(), scenario.getText()));
    }

    this->ui->clearSelectedIncidents();
    this->selectedIncidents.clear();

    this->ui->clearAvailableIncidents();
    this->availableIncidents.clear();

}


void ScenariesController::onScenarySelected(quint32 scenaryID) {

    ///Для поиска доступных ивентов, сначала скопируем все ивенты, затем удалим
    QMap<quint32, SecurityIncident> copyAllIncindets = this->copyDatabase.incidents;

    ///Поиск среди всех доступных категорий
    for (SecurityScenario scenary : this->copyDatabase.scenaries) {
        ///Среди всех событий категории
        for (quint32 incidentID : scenary.getIncidents()) {
            ///Если категория содержит такой ID, значит не доступен он!
            if (copyAllIncindets.contains(incidentID)) {
                copyAllIncindets.remove(incidentID);
            }

        }
    }

    QList<SecurityIncident> scenarioSelectedIncidents;

    SecurityScenario selectedScenario = scenaries.value(scenaryID);

    for (quint32 scenaryID : selectedScenario.getIncidents()) {
        scenarioSelectedIncidents.append(this->allIncidents.value(scenaryID));
    }

    this->resetAvailableIncidents(copyAllIncindets.values());
    this->resetSelectedIncidents(scenarioSelectedIncidents);

    ///Запоминаем ID кого мы там нажали и включаем кнопки редактирования
    this->selectedScenarioID = scenaryID;
    this->ui->enableEditButton();
    this->ui->enableSaveButton();
    this->ui->enableDeleteButton();

}

void ScenariesController::onScenaryUnselected(quint32 scenaryID) {
    ///Если ID совпали, то мы отжали кнопку
    if (this->selectedScenarioID != scenaryID) {
        //А как мы сюда попали?
        throw "onScenaryUnselected()";
        return;
    }

    this->selectedScenarioID = -1;
    this->ui->disableEditButton();
    this->ui->disableSaveButton();
    this->ui->disableDeleteButton();


    this->selectedIncidents.clear();
    this->availableIncidents.clear();

    this->resetAvailableIncidents(this->availableIncidents);
    this->resetSelectedIncidents(this->selectedIncidents);
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
    this->onScenaryUnselected(scenaryID);
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
