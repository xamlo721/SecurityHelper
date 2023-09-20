#include "MainWindowController.h"

MainWindowController::MainWindowController(QObject *parent) : QObject(parent) {

}


void MainWindowController::init() {
    w = new MainWindow();
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
    /*
        TODO №1: создать класс Interface для управления контроллерами и разбить MainWindowController на несколько контроллеров.

        TODO №2.5: добавить на тулбар админа кнопки:
    д) сохранить ( сохранить изменения );

        TODO №4: добавить отслеживание активного меню.

    */
    w->openAdminToolbar();
}

void MainWindowController::onResetButtonPressed() {
    this->availableEvents.clear();
    this->activeEvents.clear();
    this->w->clearCategoryEventList();
    this->w->clearSelectedEventList();
    this->w->openMainMenu();

}

void MainWindowController::onIncidentsButtonPressed() {
    emit signalCalculateIncident(this->activeEvents);
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
    this->setCategoryList(this->categories);
    this->setEventList(this->availableEvents);

    w->openMainMenu();
    w->openUserToolbar();
}

MainWindowController::~MainWindowController() {
    this->shutdown();
}
