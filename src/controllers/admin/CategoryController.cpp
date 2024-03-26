#include "CategoryController.h"

#include "src/ui/SelectedWidget.h"

CategoryController::CategoryController(QObject *parent) : QObject(parent) {

}

void CategoryController::init(AdminCategoriesWidget *categoryWidget) {
    this->ui = categoryWidget;
    this->editDialog = new AdminEditCatorgyDialog(categoryWidget);
    this->categoryEventID = -1;

    QObject::connect(this->ui, &AdminCategoriesWidget::signalCategorySelected, this, &CategoryController::onCetegorySelected);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalCategoryUnselected, this, &CategoryController::onCetegoryUnselected);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalAddCategoryClicked, this, &CategoryController::onCategoryAdded);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalSaveCategoryClicked, this, &CategoryController::onCategoryUpdated);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalEditCategoryClicked, this, &CategoryController::onCategoryEditRequest);
    QObject::connect(this->ui, &AdminCategoriesWidget::signalDelCategoryClicked, this, &CategoryController::onCategoryDeleted);

    QObject::connect(this->ui, &AdminCategoriesWidget::signalSelectedEventClicked, this, &CategoryController::onEventUnselected);
    QObject::connect(this->ui, &AdminCategoriesWidget::signaAvailableEventClicked, this, &CategoryController::onEventSelected);


    this->ui->disableEditButton();
    this->ui->disableSaveButton();
    this->ui->disableDeleteButton();
}

void CategoryController::resetSelectedEvents(QList<SecurityEvent> selectedEvents) {
    this->ui->clearSelectedEvents();
    this->selectedEvents = selectedEvents;

    //Отобразить все события, не входящие в какие либо категории
    for (const SecurityEvent event : selectedEvents) {
        this->ui->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }


}

void CategoryController::resetAvailableEvents(QList<SecurityEvent> freeEvents) {
    this->ui->clearAvailableEvents();
    this->availableEvents = freeEvents;

    //Назодим среди всех событий те, которые никуда не входят

    for (const SecurityEvent event : availableEvents) {
        this->ui->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }


}

void CategoryController::onDatabaseUpdated(const Database & db) {

    this->allEvents = db.events;

    this->copyDatabase = db;

    this->ui->clearCategories();

    this->categories = db.categories;

    //Отобразить все категории в списке
    for (const SecurityEventCategory category : db.categories) {
        this->ui->addCategory(new SelectedWidget(category.getId(), category.getText()));
    }

    this->ui->clearSelectedEvents();
    this->selectedEvents.clear();

    this->ui->clearAvailableEvents();
    this->availableEvents.clear();

}

//Сбрасывает всё что ты накрутил там
void CategoryController::onCetegorySelected(quint32 categoryID) {

    ///Для поиска доступных ивентов, сначала скопируем все ивенты, затем удалим
    QMap<quint32, SecurityEvent> copyAllEvents = this->copyDatabase.events;

    ///Поиск среди всех доступных категорий
    for (SecurityEventCategory category : this->copyDatabase.categories) {
        ///Среди всех событий категории
        for (quint32 eventID : category.getEventIds()) {
            ///Если категория содержит такой ID, значит не доступен он!
            if (copyAllEvents.contains(eventID)) {
                copyAllEvents.remove(eventID);
            }

        }
    }

    QList<SecurityEvent> categorySelectedEvents;

    SecurityEventCategory category = categories.value(categoryID);

    for (quint32 eventID : category.getEventIds()) {
        categorySelectedEvents.append(this->allEvents.value(eventID));
    }

    this->resetAvailableEvents(copyAllEvents.values());
    this->resetSelectedEvents(categorySelectedEvents);


    ///Запоминаем ID кого мы там нажали и включаем кнопки редактирования
    this->categoryEventID = categoryID;
    this->ui->enableEditButton();
    this->ui->enableSaveButton();
    this->ui->enableDeleteButton();

}
void CategoryController::onCetegoryUnselected(quint32 categoryID) {
    ///Если ID совпали, то мы отжали кнопку
    if (this->categoryEventID != categoryID) {
        //А как мы сюда попали?
        throw "onCetegoryUnselected()";
        return;
    }

    this->categoryEventID = -1;
    this->ui->disableEditButton();
    this->ui->disableSaveButton();
    this->ui->disableDeleteButton();


    this->selectedEvents.clear();
    this->availableEvents.clear();

    this->resetAvailableEvents(this->availableEvents);
    this->resetSelectedEvents(this->selectedEvents);
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
    this->onCetegoryUnselected(categoryID);
}

void CategoryController::onCategoryDeleted(quint32 categoryID) {
    emit signalAdminDeleteCategory(categoryID);
}

void CategoryController::onEventSelected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->availableEvents.removeOne(allEvents.value(eventID));
    this->selectedEvents.append(allEvents.value(eventID));

    ///2) Почистить доступные ивенты от него


    ///3) обновить выбранные ивенты

    this->resetAvailableEvents(this->availableEvents);
    this->resetSelectedEvents(this->selectedEvents);

}

void CategoryController::onEventUnselected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedEvents.removeOne(allEvents.value(eventID));
    this->availableEvents.append(allEvents.value(eventID));

    ///2) Почистить доступные ивенты от него


    ///3) обновить выбранные ивенты

    this->resetAvailableEvents(this->availableEvents);
    this->resetSelectedEvents(this->selectedEvents);


}
