#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"

#include "../EnumMenuPages.h"

MainMenuWidget::MainMenuWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainMenuWidget) {
    ui->setupUi(this);
}

void MainMenuWidget::clearCategories() {
    this->ui->scrollArea_categories->clear();
}

void MainMenuWidget::addCategory(SelectedWidget * category) {
    this->ui->scrollArea_categories->addWidget(category->getId(), category);
}

void MainMenuWidget::clearAvailableEvents() {
    this->ui->scrollArea_events->clear();
}

void MainMenuWidget::addEvent(SelectedWidget * event) {
    this->ui->scrollArea_events->addWidget(event->getId(), event);
}

void MainMenuWidget::clearSelectedEvents() {
    this->ui->scrollArea_selectes_eventes->clear();

}

void MainMenuWidget::addSelectedEvent(SelectedWidget * event) {
    QLayout * layout = this->ui->scrollArea_selectes_eventes->layout();
    layout->addWidget(event);
}

void MainMenuWidget::openMainMenu() {
    this->ui->stackedWidget->setCurrentIndex(EnumMenuPages::MainMenu);
}

MainMenuWidget::~MainMenuWidget() {
    delete ui;
}
