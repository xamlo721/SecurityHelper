#include "AdminInCategoryEventBoxLayout.h"

AdminInCategoryEventBoxLayout::AdminInCategoryEventBoxLayout(QObject *parent) : QObject{parent} {}

void AdminInCategoryEventBoxLayout::init(QVBoxLayout *boxLayout) {
    this->boxLayoutEvents = boxLayout;
}

void AdminInCategoryEventBoxLayout::addEventWidget(SelectedWidget *eventWidget) {
    this->initEventWidget(eventWidget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(eventWidget);

    this->boxLayoutEvents->addLayout(layout);
    this->widgetBoxLayout.append(layout);
}

void AdminInCategoryEventBoxLayout::renameEventWidget(SelectedWidget *eventWidget) {
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == eventWidget) {
            layout->itemAt(0)->widget()->repaint();
        }
    }
}

void AdminInCategoryEventBoxLayout::deleteEventWidget(SelectedWidget *eventWidget) {
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

void AdminInCategoryEventBoxLayout::unselectEventWidget(SelectedWidget *eventWidget) {
    eventWidget->unselect();
}

void AdminInCategoryEventBoxLayout::enableEventWidget(SelectedWidget *eventWidget) {
    eventWidget->setEnabled(true);
}
void AdminInCategoryEventBoxLayout::disableEventWidget(SelectedWidget *eventWidget) {
    eventWidget->setEnabled(false);
}

void AdminInCategoryEventBoxLayout::initEventWidget(SelectedWidget *eventWidget) {
    QObject::connect(eventWidget, &SelectedWidget::signalSelected, this, &AdminInCategoryEventBoxLayout::signalEventSelected);
    QObject::connect(eventWidget, &SelectedWidget::signalUnselected, this, &AdminInCategoryEventBoxLayout::signalEventUnselected);
}
