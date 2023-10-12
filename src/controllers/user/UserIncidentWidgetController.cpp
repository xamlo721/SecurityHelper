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
        QObject::connect(widget, &IncidentWidget::signalIncidentOpen, this, &UserIncidentController::signalOpenIncident);
        this->incidentMenuWidget->addIncidentWidget(widget);
    }

}
