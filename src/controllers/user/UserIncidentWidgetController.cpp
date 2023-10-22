#include "UserIncidentWidgetController.h"

UserIncidentController::UserIncidentController(QObject *parent) : QObject{parent} {

}

void UserIncidentController::init(IncidentMenuWidget *incidentWidget) {
    incidentMenuWidget = incidentWidget;
}

void UserIncidentController::setIncidentList(QList<SecurityIncident> incidents) {
    this->incidentMenuWidget->clear();

    for (SecurityIncident inc : incidents) {
        IncidentWidget * widget = new IncidentWidget(inc.getId(), inc.getText(), inc.getName());
        QObject::connect(widget, &IncidentWidget::signalIncidentOpen, this, &UserIncidentController::slotOnIncidentSelected);
        this->incidentMenuWidget->addIncidentWidget(widget);
    }

}

void UserIncidentController::slotOnIncidentSelected(quint32 id) {
    emit signalOpenIncident(id);
    emit signalIncidentSelected();
}
