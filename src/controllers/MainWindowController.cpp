#include "MainWindowController.h"

MainWindowController::MainWindowController(QObject *parent) : QObject(parent) {

}


void MainWindowController::init(MainWindow *mainWindow) {
    w = mainWindow;
    QObject::connect(this->w, &MainWindow::signalAdminButtonPressed, this, &MainWindowController::onAdminButtonPressed);
    QObject::connect(this->w, &MainWindow::signalResetButtonPressed, this, &MainWindowController::onResetButtonPressed);
    QObject::connect(this->w, &MainWindow::signalIncidentsButtonPressed, this, &MainWindowController::onIncidentsButtonPressed);
    QObject::connect(this->w, &MainWindow::signalExitButtonPressed, this, &MainWindowController::onExitButtonPressed);
    QObject::connect(this->w, &MainWindow::signalBackButtonPressed, this, &MainWindowController::onBackButtonPressed);

    w->openMainMenu();

}

void MainWindowController::show() {
    w->showMaximized();
}

void MainWindowController::shutdown() {
    delete w;
}

void MainWindowController::onAdminButtonPressed() {
    emit signalResetButtonPressed();
    w->openAdminEditMenu();
}

void MainWindowController::onResetButtonPressed() {
    emit signalResetButtonPressed();
    this->w->openMainMenu();
}

void MainWindowController::onIncidentsButtonPressed() {    
    emit signalCalculateIncidentButtonPressed();
    this->w->openIncidentMenu();
}

void MainWindowController::onExitButtonPressed() {
    this->w->close();
}

void MainWindowController::onBackButtonPressed() {
    emit signalResetButtonPressed();
    w->openMainMenu();
}

void MainWindowController::onOpenScenarioMenu() {
    this->w->openScenarioMenu();
}

void MainWindowController::onOpenRecommendationMenu() {
    this->w->openRecommendationMenu();
}

void MainWindowController::onClarifyEvents() {
    this->w->openMainMenu();
}

MainWindowController::~MainWindowController() {
    this->shutdown();
}
