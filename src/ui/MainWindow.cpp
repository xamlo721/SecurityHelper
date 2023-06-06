#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QStackedWidget>

#include "EnumMenuPages.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QObject::connect(this->ui->pushButton_admin, &QPushButton::clicked, this, &MainWindow::signalAdminButtonPressed);
    QObject::connect(this->ui->pushButton_reset, &QPushButton::clicked, this, &MainWindow::signalResetButtonPressed);
    QObject::connect(this->ui->pushButton_incidents, &QPushButton::clicked, this, &MainWindow::signalIncidentsButtonPressed);
    QObject::connect(this->ui->pushButton_settigns, &QPushButton::clicked, this, &MainWindow::signalSettingsButtonPressed);
    QObject::connect(this->ui->pushButton_exit, &QPushButton::clicked, this, &MainWindow::signalExitButtonPressed);

}

void MainWindow::openMainMenu() {
    this->ui->stackedWidget->setCurrentIndex(EnumMenuPages::MainMenu);
}

void MainWindow::openIncidentMenu() {
    this->ui->stackedWidget->setCurrentIndex(EnumMenuPages::IncidentMenu);
}

void MainWindow::openScenarioMenu() {
    this->ui->stackedWidget->setCurrentIndex(EnumMenuPages::ScenarioMenu);
}

void MainWindow::openRecommendationMenu() {
    this->ui->stackedWidget->setCurrentIndex(EnumMenuPages::RecommendationMenu);
}

void MainWindow::clearCategoryList() {
    this->ui->widget_main_menu->clearCategories();
}

void MainWindow::addCategory(EventCategoryWidget * category) {
    this->ui->widget_main_menu->addCategory(category);
}

void MainWindow::clearCategoryEventList() {
    this->ui->widget_main_menu->clearAvailableEvents();
}

void MainWindow::addCategoryEvent(EventWidget * event) {
    this->ui->widget_main_menu->addEvent(event);
}

void MainWindow::clearSelectedEventList() {
    this->ui->widget_main_menu->clearSelectedEvents();
}

void MainWindow::addSelectedEvent(EventWidget * event) {
    this->ui->widget_main_menu->addSelectedEvent(event);
}

void MainWindow::clearIncidentList() {
    this->ui->widget_incident_menu->clear();
}

void MainWindow::addIncidentWidget(IncidentWidget * widget) {
    this->ui->widget_incident_menu->addcIncidentWidget(widget);
}

MainWindow::~MainWindow() {
    delete ui;
}
