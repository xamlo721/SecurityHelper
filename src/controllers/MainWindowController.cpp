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


    w->openMainMenu();

}

void MainWindowController::show() {
    w->showMaximized();
}



void MainWindowController::shutdown() {
    delete w;
}


void MainWindowController::onAdminButtonPressed() {

}

void MainWindowController::onResetButtonPressed() {

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


MainWindowController::~MainWindowController() {
    this->shutdown();
}
