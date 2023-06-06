#include <QApplication>

#include "src/controllers/MainWindowController.h"
#include "src/logic/Database.h"
#include "src/logic/CoreApp.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    CoreApp core;

    MainWindowController controller;


    QObject::connect(&core, &CoreApp::signalOpenCategories, &controller, &MainWindowController::setCategoryList);
    QObject::connect(&core, &CoreApp::signalOpenCategory, &controller, &MainWindowController::setEventList);
    QObject::connect(&core, &CoreApp::signalOpenIncidents, &controller, &MainWindowController::setIncidentList);

    QObject::connect(&controller, &MainWindowController::signalOpenCategory, &core, &CoreApp::onOpenCategory);
    QObject::connect(&controller, &MainWindowController::signalOpenIncident, &core, &CoreApp::onCalculateIncident);

    controller.init();

    core.init();

    controller.show();

    return a.exec();
}
