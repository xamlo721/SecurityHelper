#include <QApplication>

#include "src/controllers/MainWindowController.h"
#include "src/controllers/user/UserEventsController.h"
#include "src/controllers/user/UserIncidentWidgetController.h"
#include "src/controllers/user/UserScenarioRecommendationWidgetController.h"


#include "src/controllers/admin/AdminEditMenuController.h"

#include "src/logic/Database.h"
#include "src/logic/CoreApp.h"

#include "src/ui/MainWindow.h"
#include "ui_MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    CoreApp core;

    MainWindow *mainWindow = new MainWindow();
    MainWindowController controller;

    UserEventsController categoryEventController;

    UserIncidentController incidentController;
    UserRecommendationController scenarioRecommendationController;

    AdminEditMenuController editMenuController;

    // Блок инициализации связи сигналов/слотов для пользователя

    QObject::connect(&controller, &MainWindowController::signalCalculateIncident, &categoryEventController, &UserEventsController::onCalculateIncident);
    QObject::connect(&controller, &MainWindowController::signalResetButtonPressed, &categoryEventController, &UserEventsController::clearWidget);

    //QObject::connect(&categoryEventController, &UserEventsController::signalOpenCategory, &core, &CoreApp::onOpenCategory);
    //QObject::connect(&categoryEventController, &UserEventsController::signalCalculateIncident, &core, &CoreApp::onCalculateIncident);

    //QObject::connect(&incidentController, &UserIncidentController::signalOpenIncident, &core, &CoreApp::onOpenIncident);

    QObject::connect(&scenarioRecommendationController, &UserRecommendationController::signalOpenScenarioMenu, &controller, &MainWindowController::onOpenScenarioMenu);
    //QObject::connect(&scenarioRecommendationController, &UserRecommendationController::signalOpenScenario, &core, &CoreApp::onOpenScenario);
    QObject::connect(&scenarioRecommendationController, &UserRecommendationController::signalOnClarifyEvents, &controller, &MainWindowController::onClarifyEvents);
    QObject::connect(&scenarioRecommendationController, &UserRecommendationController::signalOpenRecommendationMenu, &controller, &MainWindowController::onOpenRecommendationMenu);
    QObject::connect(&scenarioRecommendationController, &UserRecommendationController::signalSetRecommentationWidget, &controller, &MainWindowController::setRecommendationWidget);




    // Инициализация контроллеров пользовательского интерфейса
    controller.init(mainWindow);

    categoryEventController.init(mainWindow->getMainMenuWidget());
    categoryEventController.setCategoryList(core.categoriesSaved);
    categoryEventController.setEventList(core.eventsSaved);

    incidentController.init(mainWindow->getIncidentMenuWidget());
    scenarioRecommendationController.init(mainWindow->getScenarioMenuWidget());

    // Инициализация контроллеров административного интерфейса
    editMenuController.init(mainWindow->getEditMenuWidget());

    // Инициализация ядря
    core.init();

    // Старт интерфейса
    controller.show();

    return a.exec();
}
