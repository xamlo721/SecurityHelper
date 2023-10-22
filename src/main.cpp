#include <QApplication>

#include "src/controllers/MainWindowController.h"
#include "src/controllers/user/UserEventsController.h"
#include "src/controllers/user/UserIncidentWidgetController.h"
#include "src/controllers/user/UserScenarioController.h"
#include "src/controllers/user/UserRecommendationController.h"


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
    UserEventsController userEventController;
    UserIncidentController userIncidentController;
    UserScenaryController userScenaryController;
    UserRecommendationController userRecommendationController;

    ///Admin
    AdminEditMenuController editMenuController;
    CategoryController adminCategoryController;
    AdminEventsController adminEventsController;
    IncidentController adminIncidentController;
    ScenariesController adminScenariesController;
    AdminRecommendationsController adminRecommendationsController;





    QObject::connect(&core, &CoreApp::signalDatabaseUpdated, &userEventController, &UserEventsController::onDatabaseUpdated);


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

    //Admin Categories
    QObject::connect(&core, &CoreApp::signalDatabaseUpdated, &adminRecommendationsController, &AdminRecommendationsController::onDatabaseUpdated);
    QObject::connect(&adminRecommendationsController, &AdminRecommendationsController::signalAdminAddRecommendation, &core, &CoreApp::addRecommendations);
    QObject::connect(&adminRecommendationsController, &AdminRecommendationsController::signalAdminUpdateRecommendation, &core, &CoreApp::updateRecommendations);
    QObject::connect(&adminRecommendationsController, &AdminRecommendationsController::signalAdminDeleteRecommendation, &core, &CoreApp::removeRecommendations);


    // Блок инициализации связи сигналов/слотов для пользователя

    //##############    USER ACTION    ################//

    //Select Events
    QObject::connect(&controller, &MainWindowController::signalResetButtonPressed, &userEventController, &UserEventsController::resetWidget);

    QObject::connect(&controller, &MainWindowController::signalCalculateIncidentButtonPressed, &userEventController, &UserEventsController::onCalculateIncident);
    QObject::connect(&userEventController, &UserEventsController::signalEventsForIncidentSelected, &core, &CoreApp::onEventsSelected);
    QObject::connect(&core, &CoreApp::signalIncidentCalculated, &userIncidentController, &UserIncidentController::setIncidentList);

    //Incident Selected
    QObject::connect(&userIncidentController, &UserIncidentController::signalOpenIncident, &core, &CoreApp::onIncidentSelected);
    QObject::connect(&userIncidentController, &UserIncidentController::signalIncidentSelected, &controller, &MainWindowController::onOpenScenarioMenu);
    QObject::connect(&core, &CoreApp::signalScenarioCalculated, &userScenaryController, &UserScenaryController::setScenariesList);

    //Scenario Selected
    QObject::connect(&userScenaryController, &UserScenaryController::signalOnClarifyEvents, &controller, &MainWindowController::onClarifyEvents);
    QObject::connect(&userScenaryController, &UserScenaryController::signalOpenScenario, &core, &CoreApp::onScenarySelected);
    QObject::connect(&userScenaryController, &UserScenaryController::signalScenarySelected, &controller, &MainWindowController::onOpenRecommendationMenu);
    QObject::connect( &core, &CoreApp::signalRecommendationCalculated, &userRecommendationController, &UserRecommendationController::setRecommendation);





    // Инициализация контроллеров пользовательского интерфейса
    controller.init(mainWindow);

    userEventController.init(mainWindow->getMainMenuWidget());
    userIncidentController.init(mainWindow->getIncidentMenuWidget());
    userScenaryController.init(mainWindow->getScenarioMenuWidget());
    userRecommendationController.init(mainWindow->getRecommendationMenuWidget());

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
