#include "CategoryController.h"

#include "src/ui/SelectedWidget.h"

CategoryController::CategoryController(QObject *parent) : QObject(parent) {

}

void CategoryController::init(AdminCategoriesWidget *categoryWidget) {
    this->ui = categoryWidget;
}



void CategoryController::onCetegorySelected(quint32 categoryID) {
    this->availableEvents.clear();
    this->ui->clearAvailableEvents();
    SecurityEventCategory category = categories.value(categoryID);

    QList<SecurityEvent> eventsInCetegory;
    for (quint32 eventID : category.getEventIds()) {

        for (SecurityEvent event : allEvents) {
            if (event.getId() == eventID && !selectedEvents.contains(event)) {
                eventsInCetegory.append(event);
                this->availableEvents.append(event);
            }
        }
    }

    for (SecurityEvent event : eventsInCetegory) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }
}

void CategoryController::onEventSelected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedEvents.append(allEvents.value(eventID));
    this->availableEvents.removeOne(allEvents.value(eventID));

    ///2) Почистить доступные ивенты от него

    //TODO: Вычесть те, которые уже отображены
    this->ui->clearAvailableEvents();
    for (SecurityEvent event : availableEvents) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }

    ///3) обновить выбранные ивенты
    this->ui->clearSelectedEvents();
    for (SecurityEvent event : selectedEvents) {
        this->ui->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }

}

void CategoryController::onEventUnselected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedEvents.removeOne(allEvents.value(eventID));
    this->availableEvents.append(allEvents.value(eventID));

    ///2) Почистить доступные ивенты от него

    //TODO: Вычесть те, которые уже отображены
    this->ui->clearAvailableEvents();
    for (SecurityEvent event : availableEvents) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }


    ///3) обновить выбранные ивенты
    this->ui->clearSelectedEvents();
    for (SecurityEvent event : selectedEvents) {
        this->ui->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }


}
