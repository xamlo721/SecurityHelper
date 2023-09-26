#include <QApplication>

#include "src/controllers/MainWindowController.h"
#include "src/controllers/user/UserCategoryEventWidgetController.h"
#include "src/controllers/user/UserIncidentWidgetController.h"
#include "src/controllers/user/UserScenarioRecommendationWidgetController.h"

#include "src/controllers/admin/AdminEditMenuController.h"
#include "src/controllers/admin/AdminEventCategoryBoxLayoutController.h"

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
    UserIncidentWidgetController incidentController;
    UserScenarioRecommendationWidgetController scenarioRecommendationController;

    AdminEditMenuController editMenuController;

    AdminEventCategoryBoxLayoutController eventCategoryBoxContoller;

    /// Блок инициализации связи сигналов/слотов для пользователя
    QObject::connect(&core, &CoreApp::signalOpenCategories, &categoryEventController, &UserCategoryEventWidgetController::setCategoryList);
    QObject::connect(&core, &CoreApp::signalOpenCategory, &categoryEventController, &UserCategoryEventWidgetController::setEventList);
    QObject::connect(&core, &CoreApp::signalOpenIncidents, &incidentController, &UserIncidentWidgetController::setIncidentList);
    QObject::connect(&core, &CoreApp::signalOpenScenaries, &scenarioRecommendationController, &UserScenarioRecommendationWidgetController::setScenariesList);
    QObject::connect(&core, &CoreApp::signalOpenRecommandations, &scenarioRecommendationController, &UserScenarioRecommendationWidgetController::setRecommendationsList);

    QObject::connect(&controller, &MainWindowController::signalCalculateIncident, &categoryEventController, &UserCategoryEventWidgetController::onCalculateIncident);
    QObject::connect(&controller, &MainWindowController::signalResetButtonPressed, &categoryEventController, &UserCategoryEventWidgetController::clearWidget);

    QObject::connect(&categoryEventController, &UserCategoryEventWidgetController::signalOpenCategory, &core, &CoreApp::onOpenCategory);
    QObject::connect(&categoryEventController, &UserCategoryEventWidgetController::signalCalculateIncident, &core, &CoreApp::onCalculateIncident);

    QObject::connect(&incidentController, &UserIncidentWidgetController::signalOpenIncident, &core, &CoreApp::onOpenIncident);

    QObject::connect(&scenarioRecommendationController, &UserScenarioRecommendationWidgetController::signalOpenScenarioMenu, &controller, &MainWindowController::onOpenScenarioMenu);
    QObject::connect(&scenarioRecommendationController, &UserScenarioRecommendationWidgetController::signalOpenScenario, &core, &CoreApp::onOpenScenario);
    QObject::connect(&scenarioRecommendationController, &UserScenarioRecommendationWidgetController::signalOnClarifyEvents, &controller, &MainWindowController::onClarifyEvents);
    QObject::connect(&scenarioRecommendationController, &UserScenarioRecommendationWidgetController::signalOpenRecommendationMenu, &controller, &MainWindowController::onOpenRecommendationMenu);
    QObject::connect(&scenarioRecommendationController, &UserScenarioRecommendationWidgetController::signalSetRecommentationWidget, &controller, &MainWindowController::setRecommendationWidget);


    /// Блок инициализации связи сигналов/слотов для администратора
    QObject::connect(&core, &CoreApp::signalAdminOpenCategories, &eventCategoryBoxContoller, &AdminEventCategoryBoxLayoutController::setCategoryList);


    /// Инициализация контроллеров пользовательского интерфейса
    controller.init(mainWindow);

    categoryEventController.init(mainWindow->getMainMenuWidget());

    incidentController.init(mainWindow->getIncidentMenuWidget());

    scenarioRecommendationController.init(mainWindow->getScenarioMenuWidget());

    /// Инициализация контроллеров административного интерфейса
    editMenuController.init(mainWindow->getEditMenuWidget());

    eventCategoryBoxContoller.init(mainWindow->getEditMenuWidget()->getBoxLayoutCategories());

    /// Инициализация ядря
    core.init();

    /// Старт пользовательского интерфейса
    controller.show();

    return a.exec();
}
