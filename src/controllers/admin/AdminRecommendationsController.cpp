#include "AdminRecommendationsController.h"

AdminRecommendationsController::AdminRecommendationsController(QObject *parent) : QObject(parent) {

}

void AdminRecommendationsController::resetSelectedRecommendations(QList<SecurityScenario> selectedScenaries) {
    this->ui->clearSelectedScenaries();
    this->selectedScenaries = selectedScenaries;

    //Отобразить все события, не входящие в какие либо категории
    for (const SecurityScenario incident : selectedScenaries) {
        this->ui->addSelectedScenary(new SelectedWidget(incident.getId(), incident.getText()));
    }


}

void AdminRecommendationsController::resetAvailableRecommendations(QList<SecurityScenario> freeScenaries) {
    this->ui->clearAvailableScenaries();
    this->availableScenaries = freeScenaries;

    //Назодим среди всех событий те, которые никуда не входят

    for (const SecurityScenario incident : freeScenaries) {
        this->ui->addAvalilableScenary(new SelectedWidget(incident.getId(), incident.getText()));
    }


}


void AdminRecommendationsController::init(AdminRecommendationWidget * recommendationWidget) {
    this->ui = recommendationWidget;
    this->editDialog = new AdminRecommendationDialog(recommendationWidget);

    QObject::connect(this->ui, &AdminRecommendationWidget::signalRecomendationSelected, this, &AdminRecommendationsController::onRecommendationSelected);
    QObject::connect(this->ui, &AdminRecommendationWidget::signalRecomendationUnselected, this, &AdminRecommendationsController::onRecommendationUnselected);
    QObject::connect(this->ui, &AdminRecommendationWidget::signalAddRecomendationClicked, this, &AdminRecommendationsController::onRecommendationAdded);
    QObject::connect(this->ui, &AdminRecommendationWidget::signalEditRecomendationClicked, this, &AdminRecommendationsController::onRecommendationEditRequest);
    QObject::connect(this->ui, &AdminRecommendationWidget::signalSaveRecomendationClicked, this, &AdminRecommendationsController::onRecommendationUpdated);
    QObject::connect(this->ui, &AdminRecommendationWidget::signalDelRecomendationClicked, this, &AdminRecommendationsController::onRecommendationDeleted);

    QObject::connect(this->ui, &AdminRecommendationWidget::signalSelectedScenaryClicked, this, &AdminRecommendationsController::onScenaryUnselected);
    QObject::connect(this->ui, &AdminRecommendationWidget::signaAvailableScenaryClicked, this, &AdminRecommendationsController::onScenarySelected);

    this->ui->disableEditButton();
    this->ui->disableDeleteButton();
}

void AdminRecommendationsController::onDatabaseUpdated(const Database & db) {


    this->allScenaries = db.scenaries;

    this->copyDatabase = db;

    this->ui->clearRecomendations();

    this->recommendations = db.recommendations;

    //Отобразить все категории в списке
    for (const SecurityScenario scenario : db.scenaries) {
        this->ui->addRecomendation(new SelectedWidget(scenario.getId(), scenario.getText()));
    }

    this->ui->clearSelectedScenaries();
    this->selectedScenaries.clear();

    this->ui->clearAvailableScenaries();
    this->availableScenaries.clear();


}


void AdminRecommendationsController::onRecommendationSelected(quint32 recommendationID) {

    ///Для поиска доступных ивентов, сначала скопируем все ивенты, затем удалим
    QMap<quint32, SecurityScenario> copyAllScenaries = this->copyDatabase.scenaries;

    ///Поиск среди всех доступных категорий
    for (SecurityRecommendations rec : this->copyDatabase.recommendations) {
        ///Среди всех событий категории
        for (quint32 scenaryID : rec.getScenaries()) {
            ///Если категория содержит такой ID, значит не доступен он!
            if (copyAllScenaries.contains(scenaryID)) {
                copyAllScenaries.remove(scenaryID);
            }

        }
    }

    QList<SecurityScenario> recSelectedScenaries;

    SecurityRecommendations selectedRecommendation = recommendations.value(recommendationID);

    for (quint32 scenaryID : selectedRecommendation.getScenaries()) {
        recSelectedScenaries.append(this->allScenaries.value(scenaryID));
    }

    this->resetAvailableRecommendations(copyAllScenaries.values());
    this->resetSelectedRecommendations(recSelectedScenaries);

    ///Запоминаем ID кого мы там нажали и включаем кнопки редактирования
    this->selectedRecommendationID = recommendationID;
    this->ui->enableEditButton();
    this->ui->enableDeleteButton();

}


void AdminRecommendationsController::onRecommendationUnselected(quint32 recommendationID) {
    ///Если ID совпали, то мы отжали кнопку
    if (this->selectedRecommendationID!= recommendationID) {
        //А как мы сюда попали?
        throw "onRecommendationUnselected()";
        return;
    }

    this->selectedRecommendationID = -1;
    this->ui->disableEditButton();
    this->ui->disableDeleteButton();


    this->selectedScenaries.clear();
    this->availableScenaries.clear();

    this->resetAvailableRecommendations(this->availableScenaries);
    this->resetSelectedRecommendations(this->selectedScenaries);
}

void AdminRecommendationsController::onRecommendationAdded() {

    //Вызвать создание категории из ядра
    emit signalAdminAddRecommendation();


}

void AdminRecommendationsController::onRecommendationUpdated(quint32 incidentID, QString recomendationName, QString TextContainment, QString TextFixes, QString TextRestore) {

    QList<quint32> selectedScenaryIDs;
    for (SecurityScenario scenary : this->selectedScenaries) {
        selectedScenaryIDs.append(scenary.getId());
    }
    SecurityRecommendations updatedRecommendation (incidentID, recomendationName, TextContainment, TextFixes, TextRestore, selectedScenaryIDs); //FIXME: Добавить параметр
    emit signalAdminUpdateRecommendation(incidentID, updatedRecommendation);
    this->onScenaryUnselected(incidentID);
}

void AdminRecommendationsController::onRecommendationEditRequest(quint32 recommendationID) {
    this->editDialog->show();
}

void AdminRecommendationsController::onRecommendationDeleted(quint32 incidentID) {
    emit signalAdminDeleteRecommendation(incidentID);
}

void AdminRecommendationsController::onScenarySelected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedScenaries.append(allScenaries.value(eventID));
    this->availableScenaries.removeOne(allScenaries.value(eventID));

    ///2) Почистить доступные ивенты от него
    this->ui->clearAvailableScenaries();
    this->ui->clearSelectedScenaries();

    for (SecurityScenario scenary : availableScenaries) {
        this->ui->addAvalilableScenary(new SelectedWidget(scenary.getId(), scenary.getText()));
    }

    ///3) обновить выбранные ивенты
    for (SecurityScenario event : selectedScenaries) {
        this->ui->addSelectedScenary(new SelectedWidget(event.getId(), event.getText()));
    }

}

void AdminRecommendationsController::onScenaryUnselected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedScenaries.removeOne(allScenaries.value(eventID));
    this->availableScenaries.append(allScenaries.value(eventID));

    ///2) Почистить доступные ивенты от него
    this->ui->clearAvailableScenaries();
    this->ui->clearSelectedScenaries();

    for (SecurityScenario scenary : availableScenaries) {
        this->ui->addAvalilableScenary(new SelectedWidget(scenary.getId(), scenary.getText()));
    }

    ///3) обновить выбранные ивенты
    for (SecurityScenario scenary : selectedScenaries) {
        this->ui->addSelectedScenary(new SelectedWidget(scenary.getId(), scenary.getText()));
    }


}
