#include "AdminIncidentBoxLayoutController.h"

#include "src/ui/admin/ItemDeletionMessageBox.h"
#include "src/ui/admin/EnumMessageBoxVariants.h"
#include "src/ui/admin/EnumMessageBoxItemVariants.h"

AdminIncidentBoxLayoutController::AdminIncidentBoxLayoutController(QObject *parent) : QObject{parent} {}

void AdminIncidentBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutEvents) {

    this->boxLayoutIncidents = new AdminIncidentBoxLayout();

    this->boxLayoutIncidents->init(editMenuBoxLayoutEvents);


    QObject::connect(this->boxLayoutIncidents, &AdminIncidentBoxLayout::signalEditIncident, this, &AdminIncidentBoxLayoutController::slotShowEditableWidget);
    QObject::connect(this->boxLayoutIncidents, &AdminIncidentBoxLayout::signalDeleteIncident, this, &AdminIncidentBoxLayoutController::slotDeleteIncident);

    QObject::connect(this->boxLayoutIncidents, &AdminIncidentBoxLayout::signalIncidentSelected, this, &AdminIncidentBoxLayoutController::onIncidentSelected);
    QObject::connect(this->boxLayoutIncidents, &AdminIncidentBoxLayout::signalIncidentUnselected, this, &AdminIncidentBoxLayoutController::onIncidentUnselected);


    QObject::connect(this->boxLayoutIncidents, &AdminIncidentBoxLayout::editingFinished, this, &AdminIncidentBoxLayoutController::slotShowUneditableWidget);
}

void AdminIncidentBoxLayoutController::setIncidentList(const QList<SecurityIncident> incidents) {

    this->incidents = incidents;

    this->boxLayoutIncidents->clearIncidents();

    for (SecurityIncident incident : incidents) {

        this->addIncidentWidget(incident);
    }
}

void AdminIncidentBoxLayoutController::slotShowEditableWidget(UneditableIncidentWidget *uneditableWidget) {

    EditableIncidentWidget *editableWidget = this->widgetStorage.getEditableWidget(uneditableWidget->getID());

    this->boxLayoutIncidents->showEditableWidget(uneditableWidget, editableWidget);


    this->unselectAllIncidents();

    this->disableAllIncidents();


    emit incidentIsActive();
    emit incidentIsOpened(editableWidget->getID());
}

void AdminIncidentBoxLayoutController::slotShowUneditableWidget(EditableIncidentWidget *editableWidget) {

    UneditableIncidentWidget *uneditableWidget = this->widgetStorage.getUneditableWidget(editableWidget->getID());


    this->renameIncident(editableWidget->getID(), editableWidget->getTitle(), editableWidget->getText());


    uneditableWidget->setTitle(editableWidget->getTitle());

    emit incidentsMustBeSaved(this->incidents);

    this->boxLayoutIncidents->showUneditableWidget(editableWidget, uneditableWidget);


    this->enableAllIncidents();

    emit incidentIsNotActive();
    emit incidentIsClosed(editableWidget->getID());
}

SecurityIncident AdminIncidentBoxLayoutController::addIncident() {
    quint32 newIncidentId = 0;
    for(SecurityIncident incident : incidents) {
        if(newIncidentId < incident.getId())
            newIncidentId = incident.getId();
    }
    newIncidentId += 1;

    SecurityIncident newIncident(newIncidentId, "Пустое описание", "Новое событие", QList<quint32>());
    incidents.append(newIncident);


    emit incidentAdded(newIncident);
    return newIncident;
}

void AdminIncidentBoxLayoutController::addIncidentWidget(SecurityIncident incident) {

    UneditableIncidentWidget *uneditableWidget = new UneditableIncidentWidget(incident.getId(), incident.getName());
    EditableIncidentWidget *editableWidget = new EditableIncidentWidget(incident.getId(), incident.getName(), incident.getText());

    this->widgetStorage.appendWidget(uneditableWidget, editableWidget);
    this->boxLayoutIncidents->addIncidentWidget(uneditableWidget, editableWidget);
}

void AdminIncidentBoxLayoutController::deleteIncident(const quint32 incidentID) {


    for(SecurityIncident &incident : incidents) {
        if(incident.getId() == incidentID) {

            if(this->selectedIncidents.contains(incident))
                this->onIncidentUnselected(incident.getId());


            incidents.removeOne(incident);
        }
    }    
}

void AdminIncidentBoxLayoutController::deleteIncidentWidget(const quint32 incidentID) {
    UneditableIncidentWidget *tempWidget = this->widgetStorage.getUneditableWidget(incidentID);
    this->widgetStorage.removeWidget(incidentID);
    this->boxLayoutIncidents->deleteIncidentWidget(tempWidget);
}

void AdminIncidentBoxLayoutController::renameIncident(const quint32 widgetID, const QString widgetTitle, const QString widgetText) {

    quint32 incidentID;
    QString newIncidentTitle;
    QString newIncidentText;
    for(SecurityIncident &incident : incidents) {
        if(incident.getId() == widgetID) {

            incident.setName(widgetTitle);
            incident.setText(widgetText);

            incidentID = incident.getId();
            newIncidentTitle = widgetTitle;
            newIncidentText = widgetText;
        }
    }

    emit incidentRenamed(incidentID, newIncidentTitle, newIncidentText);
}

void AdminIncidentBoxLayoutController::unselectAllIncidents() {
    for(SecurityIncident incident : selectedIncidents) {

        this->boxLayoutIncidents->unselectUneditableWidget(this->widgetStorage.getUneditableWidget(incident.getId()));
    }
}

void AdminIncidentBoxLayoutController::enableAllIncidents() {
    for(SecurityIncident incident : incidents) {

        this->boxLayoutIncidents->enableUneditableWidget(this->widgetStorage.getUneditableWidget(incident.getId()));
    }
}

void AdminIncidentBoxLayoutController::disableAllIncidents() {
    for(SecurityIncident incident : incidents) {

        this->boxLayoutIncidents->disableUneditableWidget(this->widgetStorage.getUneditableWidget(incident.getId()));
    }
}

void AdminIncidentBoxLayoutController::slotDeleteIncident(UneditableIncidentWidget * uneditableWidget) {

    ItemDeletionMessageBox messageBox;

    if(messageBox.openWarning(EnumMessageBoxVariants::DeletionOneItem, EnumMessageBoxItemVariants::Event) == ItemDeletionMessageBox::Yes) {

        this->deleteIncidentWidget(uneditableWidget->getID());
        this->deleteIncident(uneditableWidget->getID());

        this->enableAllIncidents();
        emit incidentIsNotActive();
    }
}

void AdminIncidentBoxLayoutController::slotAddIncidentButtonPressed() {
    this->addIncidentWidget(this->addIncident());
}

void AdminIncidentBoxLayoutController::slotDeleteSelectedIncidentsButtonPressed() {

    ItemDeletionMessageBox messageBox;

    if(messageBox.openWarning(EnumMessageBoxVariants::DeletionSeveralItems, EnumMessageBoxItemVariants::Event) == ItemDeletionMessageBox::Yes) {


        for(SecurityIncident &incident : selectedIncidents) {

            this->deleteIncidentWidget(incident.getId());
            this->deleteIncident(incident.getId());

            /// Производим разблокировку интерфейса
            this->enableAllIncidents();
            emit incidentIsNotActive();
        }
    }
}

void AdminIncidentBoxLayoutController::onIncidentSelected(const quint32 incidentID) {

    quint32 incidentChecked = 0;
    for(SecurityIncident incident : incidents) {
        if(incident.getId() != incidentID)
            incidentChecked++;
    }

    /*if(eventsChecked == events.size()) {
        throw
    }*/


    incidentChecked = 0;
    for(SecurityIncident selectedIncident : selectedIncidents) {
        if(selectedIncident.getId() == incidentID)
            incidentChecked++;
    }

    if(incidentChecked != 1) {

        for(quint32 i = 0; i < incidents.size(); i++) {
            SecurityIncident incident = this->incidents.at(i);

            if(incident.getId() == incidentID)
                this->selectedIncidents.append(incident);
        }
    }

    // else throw

    if(!selectedIncidents.isEmpty())
        emit signalSelectedIncidentsNotEmpty();
}

void AdminIncidentBoxLayoutController::onIncidentUnselected(const quint32 incidentID) {

    quint32 incidentsChecked = 0;
    for(SecurityIncident incident : incidents) {
        if(incident.getId() != incidentID)
            incidentsChecked++;
    }

    //if(eventsChecked == events.size())
        //throw


    incidentsChecked = 0;
    for(SecurityIncident selectedIncident : selectedIncidents) {
        if(selectedIncident.getId() == incidentID)
            incidentsChecked++;
    }

    if(incidentsChecked != 1) {
        //throw
    }

    else {

        for(quint32 i = 0; i < selectedIncidents.size(); i++) {
            SecurityIncident selectedIncident = this->selectedIncidents.at(i);

            if(selectedIncident.getId() == incidentID)
                this->selectedIncidents.removeOne(selectedIncident);
        }
    }

    if(selectedIncidents.isEmpty())
        emit signalSelectedIncidentsEmpty();
}
