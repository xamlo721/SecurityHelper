#include "AdminEditMenuController.h"

AdminEditMenuController::AdminEditMenuController(QObject *parent) : QObject{parent} {

}

void AdminEditMenuController::init(AdminEditMenuWidget *editMenu) {
    editMenuWidget = editMenu;

    /// Блок связи сигналов, поступающих в меню редактирования из не редактируемого виджета
    QObject::connect(editMenuWidget, &AdminEditMenuWidget::signalEditCategory, this, &AdminEditMenuController::makeCategoryEditable);

    /// Блок связи сигналов, поступающих в меню редактирования из редактируемого виджета
    QObject::connect(editMenuWidget, &AdminEditMenuWidget::editingFinished, this, &AdminEditMenuController::makeCategoryUneditable);
}

void AdminEditMenuController::setCategoryList(QList<SecurityEventCategory> categories) {
    this->categories = categories;
    this->editMenuWidget->clearCategories();
    for (SecurityEventCategory cat : categories) {
        UneditableEventCategoryWidget *categoryWidget = new UneditableEventCategoryWidget(cat.getId(), cat.getText());
        categories_number++;
        active_categories.insert(categories_number, cat);

        //QObject::connect(categoryWidget, &UneditableEventCategoryWidget::signalOpenIncident, this, &AdminEditMenuController::signalOpenCategory);

        this->editMenuWidget->addCategory(categoryWidget);
    }
}

void AdminEditMenuController::makeCategoryEditable(UneditableEventCategoryWidget *uneditableCategory) {
    this->editMenuWidget->makeCategoryEditable(uneditableCategory);
}

void AdminEditMenuController::makeCategoryUneditable(EditableEventCategoryWidget *editableCategory) {
    this->editMenuWidget->makeCategoryUneditable(editableCategory);
}
