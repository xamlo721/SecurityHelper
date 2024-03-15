#include "CategoryController.h"

#include "src/ui/SelectedWidget.h"

CategoryController::CategoryController(QObject *parent) : QObject(parent) {

}

void CategoryController::init(AdminCategoriesWidget *categoryWidget) {
    this->ui = categoryWidget;
    this->editDialog = new AdminEditCatorgyDialog(categoryWidget);

    QObject::connect(this->ui, &AdminCategoriesWidget::signalCategoryClicked, this, &CategoryController::onCetegorySelected);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalAddCategoryClicked, this, &CategoryController::onCategoryAdded);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalSaveCategoryClicked, this, &CategoryController::onCategoryUpdated);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalEditCategoryClicked, this, &CategoryController::onCategoryEditRequest);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalDelCategoryClicked, this, &CategoryController::onCategoryDeleted);

    QObject::connect(this->ui, &AdminCategoriesWidget::signalSelectedEventClicked, this, &CategoryController::onEventUnselected);
    QObject::connect(this->ui, &AdminCategoriesWidget::signaAvailableEventClicked, this, &CategoryController::onEventSelected);

}

void CategoryController::resetSelectedEvents(QMap<quint32, SecurityEvent> freeEvents) {
    this->ui->clearSelectedEvents();
    this->selectedEvents.clear();

    //Отобразить все события, не входящие в какие либо категории
    for (const SecurityEvent event : freeEvents) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }

}

void CategoryController::resetAvailableEvents(QMap<quint32, SecurityEvent> freeEvents) {
    this->ui->clearAvailableEvents();
    this->availableEvents.clear();
    this->allEvents = freeEvents;

    //Назодим среди всех событий те, которые никуда не входят

    for (const SecurityEventCategory category : this->copyDatabase.categories) {

        for (const quint32 eventID : category.getEventIds()) {

            if (freeEvents.contains(eventID)) {
                freeEvents.remove(eventID);
            }

        }

    }
    this->availableEvents = freeEvents.values();

}

void CategoryController::onDatabaseUpdated(const Database & db) {

    this->copyDatabase = db;

    this->ui->clearCategories();

    this->categories = db.categories;

    //Отобразить все категории в списке
    for (const SecurityEventCategory category : db.categories) {
        this->ui->addCategory(new SelectedWidget(category.getId(), category.getText()));
    }

    this->resetSelectedEvents(db.events);
    this->resetAvailableEvents(db.events);

}


void CategoryController::onCetegorySelected(quint32 categoryID) {

    //Сбрасывает всё что ты накрутил там

    this->resetSelectedEvents(this->copyDatabase.events);
    this->resetAvailableEvents(this->copyDatabase.events);

    SecurityEventCategory category = categories.value(categoryID);

    for (quint32 eventID : category.getEventIds()) {

        for (SecurityEvent event : allEvents) {
            if (event.getId() == eventID && !selectedEvents.contains(event)) {
                this->selectedEvents.append(event);
            }
        }
    }

    for (SecurityEvent event : selectedEvents) {
        this->ui->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }

}


void CategoryController::onCategoryAdded() {

    //Вызвать создание категории из ядра
    emit signalAdminAddCategory();


}

void CategoryController::onCategoryEditRequest(quint32 categoryID) {
    this->editDialog->show();
}

void CategoryController::onCategoryUpdated(quint32 categoryID, QString categoryName) {

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
    this->ui->clearAvailableEvents();
    this->ui->clearSelectedEvents();

    for (SecurityEvent event : availableEvents) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }

    ///3) обновить выбранные ивенты
    for (SecurityEvent event : selectedEvents) {
        this->ui->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }

}

void CategoryController::onEventUnselected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedEvents.removeOne(allEvents.value(eventID));
    this->availableEvents.append(allEvents.value(eventID));

    ///2) Почистить доступные ивенты от него
    this->ui->clearAvailableEvents();
    this->ui->clearSelectedEvents();

    for (SecurityEvent event : availableEvents) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }

    ///3) обновить выбранные ивенты
    for (SecurityEvent event : selectedEvents) {
        this->ui->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }


}
