#include "AdminEventBoxLayout.h"

AdminEventBoxLayout::AdminEventBoxLayout(QObject *parent) : QObject{parent} {}

void AdminEventBoxLayout::init(QVBoxLayout *boxLayout) {

    this->boxLayoutEvents = boxLayout;
}

void AdminEventBoxLayout::initUneditableWidget(UneditableEventWidget *uneditableWidget) {
    QObject::connect(uneditableWidget, &UneditableEventWidget::signalEditEvent, this, &AdminEventBoxLayout::signalEditEvent);
    QObject::connect(uneditableWidget, &UneditableEventWidget::signalDeleteEvent, this, &AdminEventBoxLayout::signalDeleteEvent);

    QObject::connect(uneditableWidget, &UneditableEventWidget::signalEventSelected, this, &AdminEventBoxLayout::signalEventSelected);
    QObject::connect(uneditableWidget, &UneditableEventWidget::signalEventUnselected, this, &AdminEventBoxLayout::signalEventUnselected);
}

void AdminEventBoxLayout::initEditableWidget(EditableEventWidget *editableWidget) {
    QObject::connect(editableWidget, &EditableEventWidget::editingFinished, this, &AdminEventBoxLayout::editingFinished);
}

void AdminEventBoxLayout::addEventWidget(UneditableEventWidget *uneditableWidget, EditableEventWidget *editableWidget) {

    uneditableWidget->initMenu();

    this->initUneditableWidget(uneditableWidget);
    this->initEditableWidget(editableWidget);


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(uneditableWidget);
    layout->addWidget(editableWidget);


    editableWidget->hide();

    this->boxLayoutEvents->addLayout(layout);

    this->widgetBoxLayout.append(layout);
}

void AdminEventBoxLayout::deleteEventWidget(UneditableEventWidget *uneditableWidget) {

    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == uneditableWidget) {
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

void AdminEventBoxLayout::clearEvents() {

    if(this->boxLayoutEvents->layout() != NULL) {
        QLayoutItem* item;
        while ( ( item = this->boxLayoutEvents->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
    }

}

void AdminEventBoxLayout::showEditableWidget(UneditableEventWidget *uneditableWidget, EditableEventWidget *editableWidget) {

    uneditableWidget->hide();

    editableWidget->show();

    editableWidget->setFocus();
}

void AdminEventBoxLayout::showUneditableWidget(EditableEventWidget *editableWidget, UneditableEventWidget *uneditableWidget) {

    editableWidget->hide();

    uneditableWidget->show();
}

void AdminEventBoxLayout::unselectUneditableWidget(UneditableEventWidget *uneditableWidget) {
    uneditableWidget->setUnselected();
}

void AdminEventBoxLayout::enableUneditableWidget(UneditableEventWidget *uneditableWidget) {
    uneditableWidget->setEnabled(true);
}

void AdminEventBoxLayout::disableUneditableWidget(UneditableEventWidget *uneditableWidget) {
    uneditableWidget->setEnabled(false);
}
