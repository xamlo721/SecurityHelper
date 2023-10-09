#include "AdminScenarioBoxLayout.h"

AdminScenarioBoxLayout::AdminScenarioBoxLayout(QObject *parent) : QObject{parent} {}

void AdminScenarioBoxLayout::init(QVBoxLayout *boxLayout) {

    this->boxLayoutScenaries = boxLayout;
}

void AdminScenarioBoxLayout::initUneditableWidget(UneditableScenarioWidget *uneditableWidget) {
    QObject::connect(uneditableWidget, &UneditableScenarioWidget::signalEditScenario, this, &AdminScenarioBoxLayout::signalEditScenario);
    QObject::connect(uneditableWidget, &UneditableScenarioWidget::signalDeleteScenario, this, &AdminScenarioBoxLayout::signalDeleteScenario);

    QObject::connect(uneditableWidget, &UneditableScenarioWidget::signalScenarioSelected, this, &AdminScenarioBoxLayout::signalScenarioSelected);
    QObject::connect(uneditableWidget, &UneditableScenarioWidget::signalScenarioUnselected, this, &AdminScenarioBoxLayout::signalScenarioUnselected);
}

void AdminScenarioBoxLayout::initEditableWidget(EditableScenarioWidget *editableWidget) {
    QObject::connect(editableWidget, &EditableScenarioWidget::editingFinished, this, &AdminScenarioBoxLayout::editingFinished);
}

void AdminScenarioBoxLayout::addScenarioWidget(UneditableScenarioWidget *uneditableWidget, EditableScenarioWidget *editableWidget) {

    uneditableWidget->initMenu();

    this->initUneditableWidget(uneditableWidget);
    this->initEditableWidget(editableWidget);


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(uneditableWidget);
    layout->addWidget(editableWidget);


    editableWidget->hide();

    this->boxLayoutScenaries->addLayout(layout);

    this->widgetBoxLayout.append(layout);
}

void AdminScenarioBoxLayout::deleteScenarioWidget(UneditableScenarioWidget *uneditableWidget) {

    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == uneditableWidget) {
            QLayoutItem* item;
                while ( ( item = layout->takeAt( 0 ) ) != NULL ) {
                    delete item->widget();
                    delete item;
                }
            this->widgetBoxLayout.removeOne(layout);
            this->boxLayoutScenaries->removeItem(layout);
            layout->deleteLater();
        }
    }
}

void AdminScenarioBoxLayout::clearScenaries() {

    if(this->boxLayoutScenaries->layout() != NULL) {
        QLayoutItem* item;
        while ( ( item = this->boxLayoutScenaries->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
    }

}

void AdminScenarioBoxLayout::showEditableWidget(UneditableScenarioWidget *uneditableWidget, EditableScenarioWidget *editableWidget) {

    uneditableWidget->hide();

    editableWidget->show();

    editableWidget->setFocus();
}

void AdminScenarioBoxLayout::showUneditableWidget(EditableScenarioWidget *editableWidget, UneditableScenarioWidget *uneditableWidget) {

    editableWidget->hide();

    uneditableWidget->show();
}

void AdminScenarioBoxLayout::unselectUneditableWidget(UneditableScenarioWidget *uneditableWidget) {
    uneditableWidget->setUnselected();
}

void AdminScenarioBoxLayout::enableUneditableWidget(UneditableScenarioWidget *uneditableWidget) {
    uneditableWidget->setEnabled(true);
}

void AdminScenarioBoxLayout::disableUneditableWidget(UneditableScenarioWidget *uneditableWidget) {
    uneditableWidget->setEnabled(false);
}
