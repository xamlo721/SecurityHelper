#include "AdminCategoriesWidget.h"
#include "ui_AdminCategoriesWidget.h"

AdminCategoriesWidget::AdminCategoriesWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AdminCategoriesWidget) {
    ui->setupUi(this);
    QObject::connect(this->ui->pushButton_addCategory, &QPushButton::clicked, this, &AdminCategoriesWidget::onAddCategoryButtonPressed);
    QObject::connect(this->ui->pushButton_editCategory, &QPushButton::clicked, this, &AdminCategoriesWidget::onEditCategoryButtonPressed);
    QObject::connect(this->ui->pushButton_deleteSelectedCategories, &QPushButton::clicked, this, &AdminCategoriesWidget::onDelCategoryButtonPressed);

    QObject::connect(this->ui->pushButton_saveCategory, &QPushButton::clicked, this, &AdminCategoriesWidget::onSaveCategoryButtonPressed);
}


void AdminCategoriesWidget::clearCategories() {
    this->ui->scrollArea_categories->clear();
}

void AdminCategoriesWidget::addCategory(SelectedWidget * category) {
    QObject::connect(category, &SelectedWidget::signalSelected, this, &AdminCategoriesWidget::signalCategoryClicked);
    this->ui->scrollArea_categories->addWidget(category->getId(), category);
}

void AdminCategoriesWidget::clearAvailableEvents() {
    this->ui->scrollArea_categories_freeEvents->clear();
}

void AdminCategoriesWidget::addAvalilableEvent(SelectedWidget * event) {
    QObject::connect(event, &SelectedWidget::signalSelected, this, &AdminCategoriesWidget::signaAvailableEventClicked);
    this->ui->scrollArea_categories_freeEvents->addWidget(event->getId(), event);
}

void AdminCategoriesWidget::clearSelectedEvents() {
    this->ui->scrollArea_categories_includedEvent->clear();

}

void AdminCategoriesWidget::addSelectedEvent(SelectedWidget * event) {
    QObject::connect(event, &SelectedWidget::signalSelected, this, &AdminCategoriesWidget::signalSelectedEventClicked);
    this->ui->scrollArea_categories_includedEvent->addWidget(event->getId(), event);

}

void AdminCategoriesWidget::onAddCategoryButtonPressed() {
    emit signalAddCategoryClicked(this->ui->scrollArea_categories->getSelectedWidgetID());
}

void AdminCategoriesWidget::onEditCategoryButtonPressed() {
    emit signalEditCategoryClicked(this->ui->scrollArea_categories->getSelectedWidgetID());
}

void AdminCategoriesWidget::onDelCategoryButtonPressed() {
    emit signalDelCategoryClicked(this->ui->scrollArea_categories->getSelectedWidgetID());
}

void AdminCategoriesWidget::onSaveCategoryButtonPressed() {
    emit signalSaveCategoryClicked(this->ui->scrollArea_categories->getSelectedWidgetID());
}

AdminCategoriesWidget::~AdminCategoriesWidget() {
    delete ui;
}
