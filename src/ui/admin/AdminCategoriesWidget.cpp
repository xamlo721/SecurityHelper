#include "AdminCategoriesWidget.h"
#include "ui_AdminCategoriesWidget.h"

AdminCategoriesWidget::AdminCategoriesWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AdminCategoriesWidget) {
    ui->setupUi(this);
    QObject::connect(this->ui->pushButton_addCategory, &QPushButton::clicked, this, &AdminCategoriesWidget::onAddCategoryButtonPressed);
    QObject::connect(this->ui->pushButton_editCategory, &QPushButton::clicked, this, &AdminCategoriesWidget::onEditCategoryButtonPressed);
    QObject::connect(this->ui->pushButton_deleteSelectedCategories, &QPushButton::clicked, this, &AdminCategoriesWidget::onDelCategoryButtonPressed);

    QObject::connect(this->ui->pushButton_saveCategory, &QPushButton::clicked, this, &AdminCategoriesWidget::onSaveCategoryButtonPressed);
}


/**
 * @brief clearCategories - очищает визуальный список категорий событий
 */
void AdminCategoriesWidget::clearCategories() {
    this->ui->scrollArea_categories->clear();
}

/**
 * @brief addCategory - добавляет в отображаемый
 * список категорий новый виджет категории
 * @param category - заранее сделанный виджет
 */
void AdminCategoriesWidget::addCategory(SelectedWidget * category) {
    QObject::connect(category, &SelectedWidget::signalSelected, this, &AdminCategoriesWidget::signalCategorySelected);
    QObject::connect(category, &SelectedWidget::signalUnselected, this, &AdminCategoriesWidget::signalCategoryUnselected);
    this->ui->scrollArea_categories->addWidget(category->getId(), category);
}

/**
 * @brief clearAvailableEvents - очищает визуальный список доступных событий
 */
void AdminCategoriesWidget::clearAvailableEvents() {
    this->ui->scrollArea_categories_freeEvents->clear();
}

/**
 * @brief addEvent - добавляет в отображаемый
 * список доступных для выделения событий
 * новый виджет
 * @param event - заранее сделанный виджет
 */
void AdminCategoriesWidget::addAvalilableEvent(SelectedWidget * event) {
    QObject::connect(event, &SelectedWidget::signalSelected, this, &AdminCategoriesWidget::signaAvailableEventClicked);
    this->ui->scrollArea_categories_freeEvents->addWidget(event->getId(), event);
}

/**
 * @brief clearSelectedEvents - очищает визуальный список выбранных событий
 */
void AdminCategoriesWidget::clearSelectedEvents() {
    this->ui->scrollArea_categories_includedEvent->clear();

}

/**
 * @brief addSelectedEvent - добавляет в отображаемый
 * список выбранных событий новый виджет
 * @param event - заранее сделанный виджет
 */
void AdminCategoriesWidget::addSelectedEvent(SelectedWidget * event) {
    QObject::connect(event, &SelectedWidget::signalSelected, this, &AdminCategoriesWidget::signalSelectedEventClicked);
    this->ui->scrollArea_categories_includedEvent->addWidget(event->getId(), event);

}

void AdminCategoriesWidget::onAddCategoryButtonPressed() {
    this->ui->scrollArea_categories->unselect();
    emit signalAddCategoryClicked();
}

void AdminCategoriesWidget::onEditCategoryButtonPressed() {
    //TODO: Оставить возможность редактировать только если выбрана категория
    emit signalEditCategoryClicked(this->ui->scrollArea_categories->getSelectedWidgetID());
}

void AdminCategoriesWidget::onDelCategoryButtonPressed() {
    emit signalDelCategoryClicked(this->ui->scrollArea_categories->getSelectedWidgetID());
}

void AdminCategoriesWidget::onSaveCategoryButtonPressed() {
    SelectedWidget * selected =  this->ui->scrollArea_categories->getSelectedWidget();
    emit signalSaveCategoryClicked(selected->getId(), selected->getText());
}


/**
 * @brief enableEditButton - включить доступность кнопки
 * "Редактировать" на пакели событий
 */
void AdminCategoriesWidget::enableEditButton() {
    this->ui->pushButton_editCategory->setEnabled(true);
}

/**
 * @brief disableEditButton - выключить доступность кнопки
 * "Редактировать" на пакели событий
 */
void AdminCategoriesWidget::disableEditButton() {
    this->ui->pushButton_editCategory->setEnabled(false);
}

/**
 * @brief enableDeleteButton - включить доступность кнопки
 * "Удалить" на пакели событий
 */
void AdminCategoriesWidget::enableDeleteButton() {
    this->ui->pushButton_deleteSelectedCategories->setEnabled(true);
}

/**
 * @brief disableDeleteButton - выключить доступность кнопки
 * "Удалить" на пакели событий
 */
void AdminCategoriesWidget::disableDeleteButton() {
    this->ui->pushButton_deleteSelectedCategories->setEnabled(false);
}


AdminCategoriesWidget::~AdminCategoriesWidget() {
    delete ui;
}
