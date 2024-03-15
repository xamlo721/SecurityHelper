#include "AdminRecommendationsController.h"

AdminRecommendationsController::AdminRecommendationsController(QObject *parent) : QObject(parent) {

}


void AdminRecommendationsController::init(AdminRecommendationWidget * recommendationWidget) {
    this->ui = recommendationWidget;
    this->editDialog = new AdminRecommendationDialog(recommendationWidget);

    QObject::connect(this->ui, &AdminRecommendationWidget::signalRecomendationClicked, this, &AdminRecommendationsController::onRecommendationSelected);
    QObject::connect(this->ui, &AdminRecommendationWidget::signalAddRecomendationClicked, this, &AdminRecommendationsController::onRecommendationAdded);
    QObject::connect(this->ui, &AdminRecommendationWidget::signalEditRecomendationClicked, this, &AdminRecommendationsController::onRecommendationEditRequest);
    QObject::connect(this->ui, &AdminRecommendationWidget::signalSaveRecomendationClicked, this, &AdminRecommendationsController::onRecommendationUpdated);
    QObject::connect(this->ui, &AdminRecommendationWidget::signalDelRecomendationClicked, this, &AdminRecommendationsController::onRecommendationDeleted);

    QObject::connect(this->ui, &AdminRecommendationWidget::signalSelectedScenaryClicked, this, &AdminRecommendationsController::onScenaryUnselected);
    QObject::connect(this->ui, &AdminRecommendationWidget::signaAvailableScenaryClicked, this, &AdminRecommendationsController::onScenarySelected);

}

void AdminRecommendationsController::onDatabaseUpdated(const Database & db) {
    copyDatabase = db;

    this->ui->clearSelectedScenaries();
    this->ui->clearAvailableScenaries();
    this->ui->clearRecomendations();

    this->availableScenaries.clear();
    this->selectedScenaries.clear();

    this->recommendations = db.recommendations;
    this->allScenaries = db.scenaries;

    //Отобразить все категории в списке
    for (const SecurityRecommendations recommendation : db.recommendations) {
        this->ui->addRecomendation(new SelectedWidget(recommendation.getId(), recommendation.getTextName()));
    }

    //Назодим среди всех событий те, которые никуда не входят
    QMap<quint32, SecurityScenario> freeScenaries = db.scenaries;

    for (const SecurityScenario scenary : db.scenaries) {

        for (const quint32 incidentID : scenary.getIncidents()) {

            if (freeScenaries.contains(incidentID)) {
                freeScenaries.remove(incidentID);
            }

        }

    }

    //Отобразить все события, не входящие в какие либо категории
    for (const SecurityScenario scenary : freeScenaries) {
        this->ui->addAvalilableScenary(new SelectedWidget(scenary.getId(), scenary.getText()));
    }

    availableScenaries = freeScenaries.values();

}


void AdminRecommendationsController::onRecommendationSelected(quint32 recommendationID) {

    //Сбрасывает всё что ты накрутил там
    this->onDatabaseUpdated(this->copyDatabase);

    this->selectedScenaries.clear();
    this->ui->clearSelectedScenaries();
    SecurityRecommendations recommendation = recommendations.value(recommendationID);

    for (quint32 scenaryID : recommendation.getScenaries()) {

        for (SecurityScenario scenary : allScenaries) {
            if (scenary.getId() == scenaryID && !selectedScenaries.contains(scenary)) {
                this->selectedScenaries.append(scenary);
            }
        }
    }

    for (SecurityScenario scenary : selectedScenaries) {
        this->ui->addSelectedScenary(new SelectedWidget(scenary.getId(), scenary.getText()));
    }

    this->ui->setRecommendationText(recommendation.getTextContainment(), recommendation.getTextFixes(), recommendation.getTextRestore());

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
