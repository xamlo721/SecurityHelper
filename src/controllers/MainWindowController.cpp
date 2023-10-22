#include "MainWindowController.h"

MainWindowController::MainWindowController(QObject *parent) : QObject(parent) {

}


void MainWindowController::init(MainWindow *mainWindow) {
    w = mainWindow;
    QObject::connect(this->w, &MainWindow::signalAdminButtonPressed, this, &MainWindowController::onAdminButtonPressed);
    QObject::connect(this->w, &MainWindow::signalResetButtonPressed, this, &MainWindowController::onResetButtonPressed);
    QObject::connect(this->w, &MainWindow::signalIncidentsButtonPressed, this, &MainWindowController::onIncidentsButtonPressed);
    QObject::connect(this->w, &MainWindow::signalSettingsButtonPressed, this, &MainWindowController::onSettingsButtonPressed);
    QObject::connect(this->w, &MainWindow::signalExitButtonPressed, this, &MainWindowController::onExitButtonPressed);

    QObject::connect(this->w, &MainWindow::signalUndoButtonPressed, this, &MainWindowController::onUndoButtonPressed);
    QObject::connect(this->w, &MainWindow::signalRedoButtonPressed, this, &MainWindowController::onRedoButtonPressed);
    QObject::connect(this->w, &MainWindow::signalResetEditButtonPressed, this, &MainWindowController::onResetEditButtonPressed);
    QObject::connect(this->w, &MainWindow::signalEditButtonPressed, this, &MainWindowController::onEditButtonPressed);
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
    w->openAdminToolbar();
}

void MainWindowController::onResetButtonPressed() {
    emit signalResetButtonPressed();
    this->w->openMainMenu();
}

void MainWindowController::onIncidentsButtonPressed() {    
    emit signalCalculateIncidentButtonPressed();
    this->w->openIncidentMenu();
}

void MainWindowController::onSettingsButtonPressed() {

}

void MainWindowController::onExitButtonPressed() {
    this->w->close();
}

void MainWindowController::onUndoButtonPressed() {

}

void MainWindowController::onRedoButtonPressed() {

}

void MainWindowController::onResetEditButtonPressed() {

}

void MainWindowController::onEditButtonPressed() {
    // замена item-ов на редактируемые
}

void MainWindowController::onBackButtonPressed() {
    emit signalResetButtonPressed();
    w->openMainMenu();
    w->openUserToolbar();
}

void MainWindowController::onOpenScenarioMenu() {
    this->w->openScenarioMenu();
}

void MainWindowController::onOpenRecommendationMenu() {
    this->w->openRecommendationMenu();
}

void MainWindowController::setRecommendationWidget(RecommendationsWidget * widget) {
    this->w->setRemmendationWidget(widget);
}

void MainWindowController::onClarifyEvents() {
    this->w->openMainMenu();
}

MainWindowController::~MainWindowController() {
    this->shutdown();
}
