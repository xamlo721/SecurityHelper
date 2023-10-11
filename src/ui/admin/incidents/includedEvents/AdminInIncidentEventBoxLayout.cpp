#include "AdminInIncidentEventBoxLayout.h"

AdminInIncidentEventBoxLayout::AdminInIncidentEventBoxLayout(QObject *parent) : QObject{parent} {}

void AdminInIncidentEventBoxLayout::init(QVBoxLayout *boxLayout) {
    this->boxLayoutEvents = boxLayout;
}

void AdminInIncidentEventBoxLayout::addEventWidget(SelectedWidget *eventWidget) {
    this->initEventWidget(eventWidget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(eventWidget);

    this->boxLayoutEvents->addLayout(layout);
    this->widgetBoxLayout.append(layout);
}

void AdminInIncidentEventBoxLayout::renameEventWidget(SelectedWidget *eventWidget) {
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == eventWidget) {
            layout->itemAt(0)->widget()->repaint();
        }
    }
}

void AdminInIncidentEventBoxLayout::deleteEventWidget(SelectedWidget *eventWidget) {
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

void AdminInIncidentEventBoxLayout::unselectEventWidget(SelectedWidget *eventWidget) {
    eventWidget->unselect();
}

void AdminInIncidentEventBoxLayout::enableEventWidget(SelectedWidget *eventWidget) {
    eventWidget->setEnabled(true);
}
void AdminInIncidentEventBoxLayout::disableEventWidget(SelectedWidget *eventWidget) {
    eventWidget->setEnabled(false);
}

void AdminInIncidentEventBoxLayout::initEventWidget(SelectedWidget *eventWidget) {
    QObject::connect(eventWidget, &SelectedWidget::signalSelected, this, &AdminInIncidentEventBoxLayout::signalEventSelected);
    QObject::connect(eventWidget, &SelectedWidget::signalUnselected, this, &AdminInIncidentEventBoxLayout::signalEventUnselected);
}
