#include "AdminInScenarioIncidentBoxLayout.h"

AdminInScenarioIncidentBoxLayout::AdminInScenarioIncidentBoxLayout(QObject *parent) : QObject{parent} {}

void AdminInScenarioIncidentBoxLayout::init(QVBoxLayout *boxLayout) {
    this->boxLayoutIncidents = boxLayout;
}

void AdminInScenarioIncidentBoxLayout::addIncidentWidget(SelectedWidget *incidentWidget) {
    this->initEventWidget(incidentWidget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(incidentWidget);

    this->boxLayoutIncidents->addLayout(layout);
    this->widgetBoxLayout.append(layout);
}

void AdminInScenarioIncidentBoxLayout::renameIncidentWidget(SelectedWidget *incidentWidget) {
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == incidentWidget) {
            layout->itemAt(0)->widget()->repaint();
        }
    }
}

void AdminInScenarioIncidentBoxLayout::deleteIncidentWidget(SelectedWidget *incidentWidget) {
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

void AdminInScenarioIncidentBoxLayout::unselectIncidentWidget(SelectedWidget *incidentWidget) {
    incidentWidget->unselect();
}

void AdminInScenarioIncidentBoxLayout::enableIncidentWidget(SelectedWidget *incidentWidget) {
    incidentWidget->setEnabled(true);
}
void AdminInScenarioIncidentBoxLayout::disableIncidentWidget(SelectedWidget *incidentWidget) {
    incidentWidget->setEnabled(false);
}

void AdminInScenarioIncidentBoxLayout::initEventWidget(SelectedWidget *incidentWidget) {
    QObject::connect(incidentWidget, &SelectedWidget::signalSelected, this, &AdminInScenarioIncidentBoxLayout::signalIncidentSelected);
    QObject::connect(incidentWidget, &SelectedWidget::signalUnselected, this, &AdminInScenarioIncidentBoxLayout::signalIncidentUnselected);
}
