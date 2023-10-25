#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QStackedWidget>

#include "EnumMenuPages.h"
#include "EnumToolbarPages.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QPixmap bkgnd(":/../images/bg-firewall.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);

    this->setPalette(p);
    QObject::connect(this->ui->pushButton_admin, &QPushButton::clicked, this, &MainWindow::signalAdminButtonPressed);
    QObject::connect(this->ui->pushButton_reset, &QPushButton::clicked, this, &MainWindow::signalResetButtonPressed);
    QObject::connect(this->ui->pushButton_incidents, &QPushButton::clicked, this, &MainWindow::signalIncidentsButtonPressed);
    QObject::connect(this->ui->pushButton_exit, &QPushButton::clicked, this, &MainWindow::signalExitButtonPressed);
    QObject::connect(this->ui->pushButton_back, &QPushButton::clicked, this, &MainWindow::signalBackButtonPressed);
}

void MainWindow::resizeEvent(QResizeEvent *evt) {
    //QPixmap bkgnd(":/../images/bg.jpg");
    QPixmap bkgnd(":/../images/bg-firewall.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);
    this->setPalette(p);

    QMainWindow::resizeEvent(evt); //call base implementation
}

MainMenuWidget *MainWindow::getMainMenuWidget() {
    return this->ui->widget_main_menu;
}

IncidentMenuWidget *MainWindow::getIncidentMenuWidget() {
    return this->ui->widget_incident_menu;
}

ScenarioMenuWidget *MainWindow::getScenarioMenuWidget() {
    return this->ui->widget_scenario_menu;
}

RecommendationsWidget *MainWindow::getRecommendationMenuWidget() {
    return this->ui->widget_recomendations_menu;
}


AdminEditMenuWidget *MainWindow::getEditMenuWidget() {
    return this->ui->widget_edit_menu;
}

AdminCategoriesWidget *MainWindow::getAdminCategoryWidget() {
    return this->ui->widget_edit_menu->ui->categories;
}

AdminEventsWidget *MainWindow::getAdminEventsWidget() {
    return this->ui->widget_edit_menu->ui->events;
}

AdminIncidentsWidget *MainWindow::getAdminIncidentWidget() {
    return this->ui->widget_edit_menu->ui->incidents;
}
AdminScenariesWidget *MainWindow::getAdminScenariesWidget() {
    return this->ui->widget_edit_menu->ui->scenaries;
}
AdminRecommendationWidget *MainWindow::getAdminRecommendationsWidget() {
    return this->ui->widget_edit_menu->ui->recommendations;
}



void MainWindow::openMainMenu() {
    this->ui->stackedWidget->setCurrentIndex(EnumMenuPages::MainMenu);
    this->ui->pushButton_back->setDisabled(true);
    this->ui->pushButton_admin->setDisabled(false);
    this->ui->pushButton_reset->setDisabled(false);
    this->ui->pushButton_incidents->setDisabled(false);
    this->ui->pushButton_admin->setDisabled(false);

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

void MainWindow::openAdminEditMenu() {
    this->ui->stackedWidget->setCurrentIndex(EnumMenuPages::AdminEditMenu);
    this->ui->pushButton_back->setDisabled(false);
    this->ui->pushButton_admin->setDisabled(true);
    this->ui->pushButton_reset->setDisabled(true);
    this->ui->pushButton_incidents->setDisabled(true);
    this->ui->pushButton_admin->setDisabled(true);

}

MainWindow::~MainWindow() {
    delete ui;
}
