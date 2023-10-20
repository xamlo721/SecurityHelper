#include <QApplication>

#include "src/controllers/MainWindowController.h"
#include "src/controllers/user/UserEventsController.h"
#include "src/controllers/user/UserIncidentWidgetController.h"
#include "src/controllers/user/UserScenarioRecommendationWidgetController.h"


#include "src/controllers/admin/AdminEditMenuController.h"
#include "src/controllers/admin/categories/CategoryController.h"

#include "src/logic/Database.h"
#include "src/logic/CoreApp.h"

#include "src/ui/MainWindow.h"
#include "ui_MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //Logic
    CoreApp core;

    //Windows
    MainWindow *mainWindow = new MainWindow();

    //Controllers
    MainWindowController controller;

    ///User
    UserEventsController categoryEventController;
    UserIncidentController incidentController;
    UserRecommendationController scenarioRecommendationController;

    ///Admin
    AdminEditMenuController editMenuController;
    CategoryController adminCategoryController;

    QObject::connect(&core, &CoreApp::signalDatabaseUpdated, &categoryEventController, &UserEventsController::onDatabaseUpdated);
    QObject::connect(&core, &CoreApp::signalDatabaseUpdated, &adminCategoryController, &CategoryController::onDatabaseUpdated);


    QObject::connect(&adminCategoryController, &CategoryController::signalAdminAddCategory, &core, &CoreApp::addCategory);
    QObject::connect(&adminCategoryController, &CategoryController::signalAdminUpdateCategory, &core, &CoreApp::updateCategory);
    QObject::connect(&adminCategoryController, &CategoryController::signalAdminDeleteCategory, &core, &CoreApp::removeCategory);











    // Блок инициализации связи сигналов/слотов для пользователя

    //QObject::connect(&controller, &MainWindowController::signalCalculateIncident, &categoryEventController, &UserEventsController::onCalculateIncident);
    QObject::connect(&controller, &MainWindowController::signalResetButtonPressed, &categoryEventController, &UserEventsController::resetWidget);

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

    incidentController.init(mainWindow->getIncidentMenuWidget());
    scenarioRecommendationController.init(mainWindow->getScenarioMenuWidget());

    // Инициализация контроллеров административного интерфейса
    editMenuController.init(mainWindow->getEditMenuWidget());
    adminCategoryController.init(mainWindow->getAdminCategoryWidget());

    // Инициализация ядря
    core.init();
    core.loadDatabase();
    // Старт интерфейса
    controller.show();

    return a.exec();
}
