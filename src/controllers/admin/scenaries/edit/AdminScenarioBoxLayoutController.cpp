#include "AdminScenarioBoxLayoutController.h"

#include "src/ui/admin/ItemDeletionMessageBox.h"
#include "src/ui/admin/EnumMessageBoxVariants.h"
#include "src/ui/admin/EnumMessageBoxItemVariants.h"

AdminScenarioBoxLayoutController::AdminScenarioBoxLayoutController(QObject *parent) : QObject{parent} {}

void AdminScenarioBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutScenaries) {

    this->boxLayoutScenaries = new AdminScenarioBoxLayout();

    this->boxLayoutScenaries->init(editMenuBoxLayoutScenaries);


    QObject::connect(this->boxLayoutScenaries, &AdminScenarioBoxLayout::signalEditScenario, this, &AdminScenarioBoxLayoutController::slotShowEditableWidget);
    QObject::connect(this->boxLayoutScenaries, &AdminScenarioBoxLayout::signalDeleteScenario, this, &AdminScenarioBoxLayoutController::slotDeleteScenario);

    QObject::connect(this->boxLayoutScenaries, &AdminScenarioBoxLayout::signalScenarioSelected, this, &AdminScenarioBoxLayoutController::onScenarioSelected);
    QObject::connect(this->boxLayoutScenaries, &AdminScenarioBoxLayout::signalScenarioUnselected, this, &AdminScenarioBoxLayoutController::onScenarioUnselected);


    QObject::connect(this->boxLayoutScenaries, &AdminScenarioBoxLayout::editingFinished, this, &AdminScenarioBoxLayoutController::slotShowUneditableWidget);
}

void AdminScenarioBoxLayoutController::setScenarioList(const QList<SecurityScenario> scenaries) {

    this->scenaries = scenaries;

    this->boxLayoutScenaries->clearScenaries();

    for (SecurityScenario scenario : scenaries) {

        this->addScenarioWidget(scenario);
    }
}

void AdminScenarioBoxLayoutController::slotShowEditableWidget(UneditableScenarioWidget *uneditableWidget) {

    EditableScenarioWidget *editableWidget = this->widgetStorage.getEditableWidget(uneditableWidget->getID());

    this->boxLayoutScenaries->showEditableWidget(uneditableWidget, editableWidget);


    this->unselectAllScenaries();

    this->disableAllScenaries();


    emit scenarioIsActive();
    emit scenarioIsOpened(editableWidget->getID());
}

void AdminScenarioBoxLayoutController::slotShowUneditableWidget(EditableScenarioWidget *editableWidget) {

    UneditableScenarioWidget *uneditableWidget = this->widgetStorage.getUneditableWidget(editableWidget->getID());


    this->renameScenario(editableWidget->getID(), editableWidget->getTitle(), editableWidget->getText());


    uneditableWidget->setTitle(editableWidget->getTitle());

    emit scenariesMustBeSaved(this->scenaries);

    this->boxLayoutScenaries->showUneditableWidget(editableWidget, uneditableWidget);


    this->enableAllScenaries();

    emit scenarioIsNotActive();
    emit scenarioIsClosed(editableWidget->getID());
}

SecurityScenario AdminScenarioBoxLayoutController::addScenario() {
    quint32 newScenarioId = 0;
    for(SecurityScenario scenario : scenaries) {
        if(newScenarioId < scenario.getId())
            newScenarioId = scenario.getId();
    }
    newScenarioId += 1;

    SecurityScenario newScenario(newScenarioId, "Здесь должно быть описание сценария", "Новый сценарий", QList<quint32>());
    scenaries.append(newScenario);


    emit scenarioAdded(newScenario);
    return newScenario;
}

void AdminScenarioBoxLayoutController::addScenarioWidget(SecurityScenario scenario) {

    UneditableScenarioWidget *uneditableWidget = new UneditableScenarioWidget(scenario.getId(), scenario.getName());
    EditableScenarioWidget *editableWidget = new EditableScenarioWidget(scenario.getId(), scenario.getName(), scenario.getText());

    this->widgetStorage.appendWidget(uneditableWidget, editableWidget);
    this->boxLayoutScenaries->addScenarioWidget(uneditableWidget, editableWidget);
}

void AdminScenarioBoxLayoutController::deleteScenario(const quint32 scenarioID) {


    for(SecurityScenario &incident : scenaries) {
        if(incident.getId() == scenarioID) {

            if(this->selectedScenaries.contains(incident))
                this->onScenarioUnselected(incident.getId());


            scenaries.removeOne(incident);
        }
    }    
}

void AdminScenarioBoxLayoutController::deleteScenarioWidget(const quint32 scenarioID) {
    UneditableScenarioWidget *tempWidget = this->widgetStorage.getUneditableWidget(scenarioID);
    this->widgetStorage.removeWidget(scenarioID);
    this->boxLayoutScenaries->deleteScenarioWidget(tempWidget);
}

void AdminScenarioBoxLayoutController::renameScenario(const quint32 widgetID, const QString widgetTitle, const QString widgetText) {

    quint32 scenarioID;
    QString newScenarioTitle;
    QString newScenarioText;
    for(SecurityScenario &scenario : scenaries) {
        if(scenario.getId() == widgetID) {

            scenario.setName(widgetTitle);
            scenario.setText(widgetText);

            scenarioID = scenario.getId();
            newScenarioTitle = widgetTitle;
            newScenarioText = widgetText;
        }
    }

    emit scenarioRenamed(scenarioID, newScenarioTitle, newScenarioText);
}

void AdminScenarioBoxLayoutController::unselectAllScenaries() {
    for(SecurityScenario scenario : selectedScenaries) {

        this->boxLayoutScenaries->unselectUneditableWidget(this->widgetStorage.getUneditableWidget(scenario.getId()));
    }
}

void AdminScenarioBoxLayoutController::enableAllScenaries() {
    for(SecurityScenario scenario : scenaries) {

        this->boxLayoutScenaries->enableUneditableWidget(this->widgetStorage.getUneditableWidget(scenario.getId()));
    }
}

void AdminScenarioBoxLayoutController::disableAllScenaries() {
    for(SecurityScenario scenario : scenaries) {

        this->boxLayoutScenaries->disableUneditableWidget(this->widgetStorage.getUneditableWidget(scenario.getId()));
    }
}

void AdminScenarioBoxLayoutController::slotDeleteScenario(UneditableScenarioWidget * uneditableWidget) {

    ItemDeletionMessageBox messageBox;

    if(messageBox.openWarning(EnumMessageBoxVariants::DeletionOneItem, EnumMessageBoxItemVariants::Scenario) == ItemDeletionMessageBox::Yes) {

        this->deleteScenarioWidget(uneditableWidget->getID());
        this->deleteScenario(uneditableWidget->getID());

        this->enableAllScenaries();
        emit scenarioIsNotActive();
    }
}

void AdminScenarioBoxLayoutController::slotAddScenarioButtonPressed() {
    this->addScenarioWidget(this->addScenario());
}

void AdminScenarioBoxLayoutController::slotDeleteSelectedScenariesButtonPressed() {

    ItemDeletionMessageBox messageBox;

    if(messageBox.openWarning(EnumMessageBoxVariants::DeletionSeveralItems, EnumMessageBoxItemVariants::Scenario) == ItemDeletionMessageBox::Yes) {


        for(SecurityScenario &scenario : selectedScenaries) {

            this->deleteScenarioWidget(scenario.getId());
            this->deleteScenario(scenario.getId());

            /// Производим разблокировку интерфейса
            this->enableAllScenaries();
            emit scenarioIsNotActive();
        }
    }
}

void AdminScenarioBoxLayoutController::onScenarioSelected(const quint32 scenarioID) {

    quint32 scenarioChecked = 0;
    for(SecurityScenario scenario : scenaries) {
        if(scenario.getId() != scenarioID)
            scenarioChecked++;
    }

    /*if(eventsChecked == events.size()) {
        throw
    }*/


    scenarioChecked = 0;
    for(SecurityScenario selectedScenario : selectedScenaries) {
        if(selectedScenario.getId() == scenarioID)
            scenarioChecked++;
    }

    if(scenarioChecked != 1) {

        for(quint32 i = 0; i < scenaries.size(); i++) {
            SecurityScenario scenario = this->scenaries.at(i);

            if(scenario.getId() == scenarioID)
                this->selectedScenaries.append(scenario);
        }
    }

    // else throw

    if(!selectedScenaries.isEmpty())
        emit signalSelectedScenariesNotEmpty();
}

void AdminScenarioBoxLayoutController::onScenarioUnselected(const quint32 scenarioID) {

    quint32 scenariesChecked = 0;
    for(SecurityScenario scenario : scenaries) {
        if(scenario.getId() != scenarioID)
            scenariesChecked++;
    }

    //if(eventsChecked == events.size())
        //throw


    scenariesChecked = 0;
    for(SecurityScenario selectedScenario : selectedScenaries) {
        if(selectedScenario.getId() == scenarioID)
            scenariesChecked++;
    }

    if(scenariesChecked != 1) {
        //throw
    }

    else {

        for(quint32 i = 0; i < selectedScenaries.size(); i++) {
            SecurityScenario selectedScenario = this->selectedScenaries.at(i);

            if(selectedScenario.getId() == scenarioID)
                this->selectedScenaries.removeOne(selectedScenario);
        }
    }

    if(selectedScenaries.isEmpty())
        emit signalSelectedScenariesEmpty();
}
