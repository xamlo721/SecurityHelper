#include "MainWindowController.h"

MainWindowController::MainWindowController(QObject *parent) : QObject(parent) {

}


void MainWindowController::init() {
    w = new MainWindow();
}

void MainWindowController::show() {
    w->showMaximized();
}

void MainWindowController::shutdown() {
    delete w;
}

MainWindowController::~MainWindowController() {
    this->shutdown();
}
