#include "CategoryController.h"

#include "src/ui/SelectedWidget.h"

CategoryController::CategoryController(QObject *parent) : QObject(parent) {

}

void CategoryController::init(AdminCategoriesWidget *categoryWidget) {
    this->ui = categoryWidget;
    QObject::connect(this->ui, &AdminCategoriesWidget::signalCategoryClicked, this, &CategoryController::onCetegorySelected);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalAddCategoryClicked, this, &CategoryController::onCategoryAdded);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalEditCategoryClicked, this, &CategoryController::onCategoryEdited);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalDelCategoryClicked, this, &CategoryController::onCategoryDeleted);

    QObject::connect(this->ui, &AdminCategoriesWidget::signalSelectedEventClicked, this, &CategoryController::onEventUnselected);
    QObject::connect(this->ui, &AdminCategoriesWidget::signaAvailableEventClicked, this, &CategoryController::onEventSelected);

}

void CategoryController::onDatabaseUpdated(const Database & db) {
    this->ui->clearSelectedEvents();
    this->ui->clearAvailableEvents();
    this->ui->clearCategories();

    this->availableEvents.clear();
    this->selectedEvents.clear();

    this->categories = db.categories;
    this->allEvents = db.events;

    //Отобразить все категории в списке
    for (const SecurityEventCategory category : db.categories) {
        this->ui->addCategory(new SelectedWidget(category.getId(), category.getText()));
    }

    //Назодим среди всех событий те, которые никуда не входят
    QList<SecurityEvent> freeEvents;
    for (const SecurityEvent event : db.events) {

        for (const SecurityEventCategory category : db.categories) {
            if (!category.getEventIds().contains(event.getId())) {
                freeEvents.append(event);
            }
        }

    }

    //Отобразить все события, не входящие в какие либо категории
    for (const SecurityEvent event : freeEvents) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }


}


void CategoryController::onCetegorySelected(quint32 categoryID) {
    this->selectedEvents.clear();
    this->ui->clearSelectedEvents();
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


void CategoryController::onCategoryAdded() {

    //Вызвать создание категории из ядра
    emit signalAdminAddCategory();

    //Очистить отображаемый список событий, принадлежащих категории
    this->ui->clearSelectedEvents();
    this->ui->clearAvailableEvents();

}

void CategoryController::onCategoryEdited(quint32 categoryID, QString categoryName) {

    QList<quint32> selectedEventIDs;
    for (SecurityEvent event : this->selectedEvents) {
        selectedEventIDs.append(event.getId());
    }
    SecurityEventCategory updatedCategory (categoryID, categoryName, selectedEventIDs);
    emit signalAdminUpdateCategory(categoryID, updatedCategory);
}

void CategoryController::onCategoryDeleted(quint32 categoryID) {
    emit signalAdminDeleteCategory(categoryID);
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
