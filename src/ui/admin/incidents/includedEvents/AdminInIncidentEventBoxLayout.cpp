#include "AdminInIncidentEventBoxLayout.h"

AdminInIncidentEventBoxLayout::AdminInIncidentEventBoxLayout(QObject *parent) : QObject{parent} {}

void AdminInIncidentEventBoxLayout::init(QVBoxLayout *boxLayout) {
    this->boxLayoutEvents = boxLayout;
}

void AdminInIncidentEventBoxLayout::addEventWidget(InIncidentEventWidget *eventWidget) {
    this->initEventWidget(eventWidget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(eventWidget);

    this->boxLayoutEvents->addLayout(layout);
    this->widgetBoxLayout.append(layout);
}

void AdminInIncidentEventBoxLayout::renameEventWidget(InIncidentEventWidget *eventWidget) {
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == eventWidget) {
            layout->itemAt(0)->widget()->repaint();
        }
    }
}

void AdminInIncidentEventBoxLayout::deleteEventWidget(InIncidentEventWidget *eventWidget) {
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == eventWidget) {
            QLayoutItem* item;
                while ( ( item = layout->takeAt( 0 ) ) != NULL ) {
                    delete item->widget();
                    delete item;
                }
            this->widgetBoxLayout.removeOne(layout);
            this->boxLayoutEvents->removeItem(layout);
            layout->deleteLater();
        }
    }
}

void AdminInIncidentEventBoxLayout::clearEvents() {
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout != NULL) {
            QLayoutItem* item;
                while ( ( item = layout->takeAt( 0 ) ) != NULL ) {
                    delete item->widget();
                    delete item;
                }
            this->widgetBoxLayout.removeOne(layout);
            this->boxLayoutEvents->removeItem(layout);
            layout->deleteLater();
        }
    }
}

void AdminInIncidentEventBoxLayout::unselectEventWidget(InIncidentEventWidget *eventWidget) {
    eventWidget->setUnselected();
}

void AdminInIncidentEventBoxLayout::enableEventWidget(InIncidentEventWidget *eventWidget) {
    eventWidget->setEnabled(true);
}
void AdminInIncidentEventBoxLayout::disableEventWidget(InIncidentEventWidget *eventWidget) {
    eventWidget->setEnabled(false);
}

void AdminInIncidentEventBoxLayout::initEventWidget(InIncidentEventWidget *eventWidget) {
    QObject::connect(eventWidget, &InIncidentEventWidget::signalEventSelected, this, &AdminInIncidentEventBoxLayout::signalEventSelected);
    QObject::connect(eventWidget, &InIncidentEventWidget::signalEventUnselected, this, &AdminInIncidentEventBoxLayout::signalEventUnselected);
}
