#include "UserIncidentWidgetController.h"

UserIncidentWidgetController::UserIncidentWidgetController(QObject *parent) : QObject{parent} {

}

void UserIncidentWidgetController::init(IncidentMenuWidget *incidentWidget) {
    incidentMenuWidget = incidentWidget;
}

void UserIncidentWidgetController::setIncidentList(QList<SecurityIncident> incidents) {
    this->incidentMenuWidget->clear();

    for (SecurityIncident inc : incidents) {
        IncidentWidget * widget = new IncidentWidget(inc.getId(), inc.getText());
        QObject::connect(widget, &IncidentWidget::signalIncidentOpen, this, &UserIncidentWidgetController::signalOpenIncident);
        this->incidentMenuWidget->addIncidentWidget(widget);
    }

}
