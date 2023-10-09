#include "AdminIncidentBoxLayout.h"

AdminIncidentBoxLayout::AdminIncidentBoxLayout(QObject *parent) : QObject{parent} {}

void AdminIncidentBoxLayout::init(QVBoxLayout *boxLayout) {

    this->boxLayoutIncidents = boxLayout;
}

void AdminIncidentBoxLayout::initUneditableWidget(UneditableIncidentWidget *uneditableWidget) {
    QObject::connect(uneditableWidget, &UneditableIncidentWidget::signalEditIncident, this, &AdminIncidentBoxLayout::signalEditIncident);
    QObject::connect(uneditableWidget, &UneditableIncidentWidget::signalDeleteIncident, this, &AdminIncidentBoxLayout::signalDeleteIncident);

    QObject::connect(uneditableWidget, &UneditableIncidentWidget::signalIncidentSelected, this, &AdminIncidentBoxLayout::signalIncidentSelected);
    QObject::connect(uneditableWidget, &UneditableIncidentWidget::signalIncidentUnselected, this, &AdminIncidentBoxLayout::signalIncidentUnselected);
}

void AdminIncidentBoxLayout::initEditableWidget(EditableIncidentWidget *editableWidget) {
    QObject::connect(editableWidget, &EditableIncidentWidget::editingFinished, this, &AdminIncidentBoxLayout::editingFinished);
}

void AdminIncidentBoxLayout::addIncidentWidget(UneditableIncidentWidget *uneditableWidget, EditableIncidentWidget *editableWidget) {

    uneditableWidget->initMenu();

    this->initUneditableWidget(uneditableWidget);
    this->initEditableWidget(editableWidget);


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(uneditableWidget);
    layout->addWidget(editableWidget);


    editableWidget->hide();

    this->boxLayoutIncidents->addLayout(layout);

    this->widgetBoxLayout.append(layout);
}

void AdminIncidentBoxLayout::deleteIncidentWidget(UneditableIncidentWidget *uneditableWidget) {

    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == uneditableWidget) {
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

void AdminIncidentBoxLayout::clearIncidents() {

    if(this->boxLayoutIncidents->layout() != NULL) {
        QLayoutItem* item;
        while ( ( item = this->boxLayoutIncidents->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
    }

}

void AdminIncidentBoxLayout::showEditableWidget(UneditableIncidentWidget *uneditableWidget, EditableIncidentWidget *editableWidget) {

    uneditableWidget->hide();

    editableWidget->show();

    editableWidget->setFocus();
}

void AdminIncidentBoxLayout::showUneditableWidget(EditableIncidentWidget *editableWidget, UneditableIncidentWidget *uneditableWidget) {

    editableWidget->hide();

    uneditableWidget->show();
}

void AdminIncidentBoxLayout::unselectUneditableWidget(UneditableIncidentWidget *uneditableWidget) {
    uneditableWidget->setUnselected();
}

void AdminIncidentBoxLayout::enableUneditableWidget(UneditableIncidentWidget *uneditableWidget) {
    uneditableWidget->setEnabled(true);
}

void AdminIncidentBoxLayout::disableUneditableWidget(UneditableIncidentWidget *uneditableWidget) {
    uneditableWidget->setEnabled(false);
}
