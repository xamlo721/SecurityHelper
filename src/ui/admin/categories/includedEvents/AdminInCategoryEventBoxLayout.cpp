#include "AdminInCategoryEventBoxLayout.h"

AdminInCategoryEventBoxLayout::AdminInCategoryEventBoxLayout(QObject *parent) : QObject{parent} {}

void AdminInCategoryEventBoxLayout::init(QVBoxLayout *boxLayout) {
    this->boxLayoutEvents = boxLayout;
}

void AdminInCategoryEventBoxLayout::addEventWidget(InCategoryEventWidget *eventWidget) {
    this->initEventWidget(eventWidget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(eventWidget);

    this->boxLayoutEvents->addLayout(layout);
    this->widgetBoxLayout.append(layout);
}

void AdminInCategoryEventBoxLayout::renameEventWidget(InCategoryEventWidget *eventWidget) {
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == eventWidget) {
            layout->itemAt(0)->widget()->repaint();
        }
    }
}

void AdminInCategoryEventBoxLayout::deleteEventWidget(InCategoryEventWidget *eventWidget) {
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

void AdminInCategoryEventBoxLayout::clearEvents() {
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

void AdminInCategoryEventBoxLayout::unselectEventWidget(InCategoryEventWidget *eventWidget) {
    eventWidget->setUnselected();
}

void AdminInCategoryEventBoxLayout::enableEventWidget(InCategoryEventWidget *eventWidget) {
    eventWidget->setEnabled(true);
}
void AdminInCategoryEventBoxLayout::disableEventWidget(InCategoryEventWidget *eventWidget) {
    eventWidget->setEnabled(false);
}

void AdminInCategoryEventBoxLayout::initEventWidget(InCategoryEventWidget *eventWidget) {
    QObject::connect(eventWidget, &InCategoryEventWidget::signalEventSelected, this, &AdminInCategoryEventBoxLayout::signalEventSelected);
    QObject::connect(eventWidget, &InCategoryEventWidget::signalEventUnselected, this, &AdminInCategoryEventBoxLayout::signalEventUnselected);
}
