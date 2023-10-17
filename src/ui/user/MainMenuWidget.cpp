#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"

#include "../EnumMenuPages.h"

MainMenuWidget::MainMenuWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainMenuWidget) {
    ui->setupUi(this);
    QObject::connect(this->ui->scrollArea_categories, &MenuSelectedWidget::signalOnWidgetSelected, this, &MainMenuWidget::signalCategoryClicked);
}

void MainMenuWidget::clearCategories() {
    this->ui->scrollArea_categories->clear();
}

void MainMenuWidget::addCategory(SelectedWidget * category) {
    QObject::connect(category, &SelectedWidget::signalSelected, this, &MainMenuWidget::signalCategoryClicked);
    this->ui->scrollArea_categories->addWidget(category->getId(), category);
}

void MainMenuWidget::clearAvailableEvents() {
    this->ui->scrollArea_events->clear();
}

void MainMenuWidget::addAvalilableEvent(SelectedWidget * event) {
    QObject::connect(event, &SelectedWidget::signalSelected, this, &MainMenuWidget::signaAvailableEventClicked);
    this->ui->scrollArea_events->addWidget(event->getId(), event);
}

void MainMenuWidget::clearSelectedEvents() {
    this->ui->scrollArea_selectes_eventes->clear();

}

void MainMenuWidget::addSelectedEvent(SelectedWidget * event) {
    QObject::connect(event, &SelectedWidget::signalSelected, this, &MainMenuWidget::signalSelectedEventClicked);
    this->ui->scrollArea_selectes_eventes->addWidget(event->getId(), event);

}

MainMenuWidget::~MainMenuWidget() {
    delete ui;
}
