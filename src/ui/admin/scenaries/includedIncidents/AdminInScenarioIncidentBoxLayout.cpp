#include "AdminInScenarioIncidentBoxLayout.h"

AdminInScenarioIncidentBoxLayout::AdminInScenarioIncidentBoxLayout(QObject *parent) : QObject{parent} {}

void AdminInScenarioIncidentBoxLayout::init(QVBoxLayout *boxLayout) {
    this->boxLayoutIncidents = boxLayout;
}

void AdminInScenarioIncidentBoxLayout::addIncidentWidget(InScenarioIncidentWidget *incidentWidget) {
    this->initEventWidget(incidentWidget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(incidentWidget);

    this->boxLayoutIncidents->addLayout(layout);
    this->widgetBoxLayout.append(layout);
}

void AdminInScenarioIncidentBoxLayout::renameIncidentWidget(InScenarioIncidentWidget *incidentWidget) {
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == incidentWidget) {
            layout->itemAt(0)->widget()->repaint();
        }
    }
}

void AdminInScenarioIncidentBoxLayout::deleteIncidentWidget(InScenarioIncidentWidget *incidentWidget) {
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == incidentWidget) {
            QLayoutItem* item;
                while ( ( item = layout->takeAt( 0 ) ) != NULL ) {
                    delete item->widget();
                    delete item;
                }
            this->widgetBoxLayout.removeOne(layout);
            this->boxLayoutIncidents->removeItem(layout);
            layout->deleteLater();
        }
    }
}

void AdminInScenarioIncidentBoxLayout::clearIncidents() {
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout != NULL) {
            QLayoutItem* item;
                while ( ( item = layout->takeAt( 0 ) ) != NULL ) {
                    delete item->widget();
                    delete item;
                }
            this->widgetBoxLayout.removeOne(layout);
            this->boxLayoutIncidents->removeItem(layout);
            layout->deleteLater();
        }
    }
}

void AdminInScenarioIncidentBoxLayout::unselectIncidentWidget(InScenarioIncidentWidget *incidentWidget) {
    incidentWidget->setUnselected();
}

void AdminInScenarioIncidentBoxLayout::enableIncidentWidget(InScenarioIncidentWidget *incidentWidget) {
    incidentWidget->setEnabled(true);
}
void AdminInScenarioIncidentBoxLayout::disableIncidentWidget(InScenarioIncidentWidget *incidentWidget) {
    incidentWidget->setEnabled(false);
}

void AdminInScenarioIncidentBoxLayout::initEventWidget(InScenarioIncidentWidget *incidentWidget) {
    QObject::connect(incidentWidget, &InScenarioIncidentWidget::signalIncidentSelected, this, &AdminInScenarioIncidentBoxLayout::signalIncidentSelected);
    QObject::connect(incidentWidget, &InScenarioIncidentWidget::signalIncidentUnselected, this, &AdminInScenarioIncidentBoxLayout::signalIncidentUnselected);
}
