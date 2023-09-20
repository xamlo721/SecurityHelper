#include <QApplication>

#include "src/controllers/MainWindowController.h"
#include "src/controllers/user/UserCategoryEventWidgetController.h"
#include "src/logic/Database.h"
#include "src/logic/CoreApp.h"
#include "src/ui/MainWindow.h"
#include "ui_MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    CoreApp core;

    MainWindow *mainWindow = new MainWindow();

    MainWindowController controller;

    UserCategoryEventWidgetController categoryEventController;


    QObject::connect(&core, &CoreApp::signalOpenCategories, &categoryEventController, &UserCategoryEventWidgetController::setCategoryList);
    QObject::connect(&core, &CoreApp::signalOpenCategory, &categoryEventController, &UserCategoryEventWidgetController::setEventList);
    QObject::connect(&core, &CoreApp::signalOpenIncidents, &controller, &MainWindowController::setIncidentList); // сигнал в новый контроллер инцидентов
    QObject::connect(&core, &CoreApp::signalOpenScenaries, &controller, &MainWindowController::setScenariesList);
    QObject::connect(&core, &CoreApp::signalOpenRecommandations, &controller, &MainWindowController::setRecommendationsList);

    QObject::connect(&controller, &MainWindowController::signalCalculateIncident, &categoryEventController, &UserCategoryEventWidgetController::onCalculateIncident);

    QObject::connect(&controller, &MainWindowController::signalResetButtonPressed, &categoryEventController, &UserCategoryEventWidgetController::clearWidget);

    QObject::connect(&categoryEventController, &UserCategoryEventWidgetController::signalOpenCategory, &core, &CoreApp::onOpenCategory);
    QObject::connect(&categoryEventController, &UserCategoryEventWidgetController::signalCalculateIncident, &core, &CoreApp::onCalculateIncident);
    //QObject::connect(&controller, &MainWindowController::signalOpenIncident, &core, &CoreApp::onOpenIncident);
    //QObject::connect(&controller, &MainWindowController::signalOpenScenario, &core, &CoreApp::onOpenScenario);


    controller.init(mainWindow);

    categoryEventController.init(mainWindow->getMainMenuWidget());

    core.init();

    controller.show();

    return a.exec();
}
