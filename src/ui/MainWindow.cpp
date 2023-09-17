#include "MainWindow.h"
#include "src/ui/EditableEventCategoryWidget.h"
#include "ui_MainWindow.h"
#include <QStackedWidget>

#include "EnumMenuPages.h"
#include "EnumToolbarPages.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

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

    QObject::connect(this->ui->widget_main_menu, &MainMenuWidget::signalAddCategoryButtonPressed, this, &MainWindow::signalAddCategoryButtonPressed);
    QObject::connect(this->ui->widget_main_menu, &MainMenuWidget::signalDeleteCategoriesButtonPressed, this, &MainWindow::signalDeleteCategoriesButtonPressed);

    QObject::connect(this->ui->widget_main_menu, &MainMenuWidget::signalAddEventButtonPressed, this, &MainWindow::signalAddEventButtonPressed);
    QObject::connect(this->ui->widget_main_menu, &MainMenuWidget::signalDeleteEventButtonPressed, this, &MainWindow::signalDeleteEventButtonPressed);
}

void MainWindow::openUserMainMenu() {
    this->ui->stackedWidget->setCurrentIndex(EnumMenuPages::MainMenu);
    this->ui->widget_main_menu->openUserMainMenu();
}

void MainWindow::openAdminMainMenu() {
    this->ui->stackedWidget->setCurrentIndex(EnumMenuPages::MainMenu);
    this->ui->widget_main_menu->openAdminMainMenu();
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

void MainWindow::openUserToolbar() {
    this->ui->stackedWidget_toolbar->setCurrentIndex(EnumToolbarPages::UserToolbar);
}

void MainWindow::openAdminToolbar() {
    this->ui->stackedWidget_toolbar->setCurrentIndex(EnumToolbarPages::AdminToolbar);
}

void MainWindow::clearCategoryList() {
    this->ui->widget_main_menu->clearCategories();
}

void MainWindow::addCategory(EventCategoryWidget * category) {
    this->ui->widget_main_menu->addCategory(category);
}

void MainWindow::addCategoryToAdmin(EventCategoryWidget * category) {
    this->ui->widget_main_menu->addCategoryToAdmin(category);
}

void MainWindow::clearCategoryEventList() {
    this->ui->widget_main_menu->clearAvailableEvents();
}

void MainWindow::addCategoryEvent(EventWidget * event) {
    this->ui->widget_main_menu->addEvent(event);
}

void MainWindow::addCategoryEventToAdmin(EventWidget * event) {
    this->ui->widget_main_menu->addEventToAdmin(event);
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

void MainWindow::clearScenarioList() {
    this->ui->widget_scenario_menu->clear();
}

void MainWindow::addScenarioWidget(ScenarioWidget * widget) {
    this->ui->widget_scenario_menu->addScenarioWidget(widget);

}

void MainWindow::addEditableCategory(EditableEventCategoryWidget * editableCategory) {
    this->ui->widget_main_menu->addEditableCategory(editableCategory);
}

void MainWindow::addEditableCategoryEvent(EditableEventWidget * editableEvent) {
    this->ui->widget_main_menu->addEditableEvent(editableEvent);
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
