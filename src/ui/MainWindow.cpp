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
    QObject::connect(this->ui->pushButton_settigns, &QPushButton::clicked, this, &MainWindow::signalSettingsButtonPressed);
    QObject::connect(this->ui->pushButton_exit, &QPushButton::clicked, this, &MainWindow::signalExitButtonPressed);

    QObject::connect(this->ui->pushButton_undo, &QPushButton::clicked, this, &MainWindow::signalUndoButtonPressed);
    QObject::connect(this->ui->pushButton_redo, &QPushButton::clicked, this, &MainWindow::signalRedoButtonPressed);
    QObject::connect(this->ui->pushButton_reset_edit, &QPushButton::clicked, this, &MainWindow::signalResetEditButtonPressed);
    QObject::connect(this->ui->pushButton_edit, &QPushButton::clicked, this, &MainWindow::signalEditButtonPressed);
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

AdminEditMenuWidget *MainWindow::getEditMenuWidget() {
    return this->ui->widget_edit_menu;
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

void MainWindow::openAdminEditMenu() {
    this->ui->stackedWidget->setCurrentIndex(EnumMenuPages::AdminEditMenu);
}

void MainWindow::openUserToolbar() {
    this->ui->stackedWidgetStatusbar->setCurrentIndex(EnumToolbarPages::UserToolbar);
}

void MainWindow::openAdminToolbar() {
    this->ui->stackedWidgetStatusbar->setCurrentIndex(EnumToolbarPages::AdminToolbar);
}

void MainWindow::setRemmendationWidget(RecommendationsWidget * widget) {
    //FIXME: Уродская система, переписать!
    delete this->ui->widget_recomendations_menu;
    this->ui->widget_recomendations_menu = widget;
    this->ui->stackedWidget->repaint();
    this->ui->verticalLayout_3->addWidget(widget);
}

MainWindow::~MainWindow() {
    delete ui;
}
