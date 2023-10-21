#include <QApplication>

#include "src/controllers/MainWindowController.h"
#include "src/controllers/user/UserEventsController.h"
#include "src/controllers/user/UserIncidentWidgetController.h"
#include "src/controllers/user/UserScenarioRecommendationWidgetController.h"


#include "src/controllers/admin/AdminEditMenuController.h"
#include "src/controllers/admin/categories/CategoryController.h"
#include "src/controllers/admin/AdminEventsController.h"
#include "src/controllers/admin/incidents/IncidentController.h"
#include "src/controllers/admin/scenaries/ScenariesController.h"
#include "src/controllers/admin/recomms/AdminRecommendationsController.h"

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
    UserIncidentController userIncidentController;
    UserRecommendationController scenarioRecommendationController;

    ///Admin
    AdminEditMenuController editMenuController;
    CategoryController adminCategoryController;
    AdminEventsController adminEventsController;
    IncidentController adminIncidentController;
    ScenariesController adminScenariesController;
    AdminRecommendationsController adminRecommendationsController;





    QObject::connect(&core, &CoreApp::signalDatabaseUpdated, &categoryEventController, &UserEventsController::onDatabaseUpdated);


    //Admin Categories
    QObject::connect(&core, &CoreApp::signalDatabaseUpdated, &adminCategoryController, &CategoryController::onDatabaseUpdated);
    QObject::connect(&adminCategoryController, &CategoryController::signalAdminAddCategory, &core, &CoreApp::addCategory);
    QObject::connect(&adminCategoryController, &CategoryController::signalAdminUpdateCategory, &core, &CoreApp::updateCategory);
    QObject::connect(&adminCategoryController, &CategoryController::signalAdminDeleteCategory, &core, &CoreApp::removeCategory);

    //Admin Events
    QObject::connect(&core, &CoreApp::signalDatabaseUpdated, &adminEventsController, &AdminEventsController::onDatabaseUpdated);
    QObject::connect(&adminEventsController, &AdminEventsController::signalAdminAddEvent, &core, &CoreApp::addEvent);
    QObject::connect(&adminEventsController, &AdminEventsController::signalAdminUpdateEvent, &core, &CoreApp::updateEvent);
    QObject::connect(&adminEventsController, &AdminEventsController::signalAdminDeleteEvent, &core, &CoreApp::removeEvent);

    //Admin Incidents
    QObject::connect(&core, &CoreApp::signalDatabaseUpdated, &adminIncidentController, &IncidentController::onDatabaseUpdated);
    QObject::connect(&adminIncidentController, &IncidentController::signalAdminAddIncident, &core, &CoreApp::addIncident);
    QObject::connect(&adminIncidentController, &IncidentController::signalAdminUpdateIncident, &core, &CoreApp::updateIncident);
    QObject::connect(&adminIncidentController, &IncidentController::signalAdminDeleteIncident, &core, &CoreApp::removeIncident);

    //Admin Scenaries
    QObject::connect(&core, &CoreApp::signalDatabaseUpdated, &adminScenariesController, &ScenariesController::onDatabaseUpdated);
    QObject::connect(&adminScenariesController, &ScenariesController::signalAdminAddScenary, &core, &CoreApp::addScenario);
    QObject::connect(&adminScenariesController, &ScenariesController::signalAdminUpdateScenary, &core, &CoreApp::updateScenario);
    QObject::connect(&adminScenariesController, &ScenariesController::signalAdminDeleteScenary, &core, &CoreApp::removeScenario);

    //Admin Scenaries
    QObject::connect(&core, &CoreApp::signalDatabaseUpdated, &adminRecommendationsController, &AdminRecommendationsController::onDatabaseUpdated);
    QObject::connect(&adminRecommendationsController, &AdminRecommendationsController::signalAdminAddRecommendation, &core, &CoreApp::addRecommendations);
    QObject::connect(&adminRecommendationsController, &AdminRecommendationsController::signalAdminUpdateRecommendation, &core, &CoreApp::updateRecommendations);
    QObject::connect(&adminRecommendationsController, &AdminRecommendationsController::signalAdminDeleteRecommendation, &core, &CoreApp::removeRecommendations);








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

    userIncidentController.init(mainWindow->getIncidentMenuWidget());
    scenarioRecommendationController.init(mainWindow->getScenarioMenuWidget());

    // Инициализация контроллеров административного интерфейса
    editMenuController.init(mainWindow->getEditMenuWidget());
    adminCategoryController.init(mainWindow->getAdminCategoryWidget());
    adminEventsController.init(mainWindow->getAdminEventsWidget());
    adminIncidentController.init(mainWindow->getAdminIncidentWidget());
    adminScenariesController.init(mainWindow->getAdminScenariesWidget());
    adminRecommendationsController.init(mainWindow->getAdminRecommendationsWidget());



    // Инициализация ядря
    core.init();
    core.loadDatabase();
    // Старт интерфейса
    controller.show();

    return a.exec();
}
