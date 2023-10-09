#include <QApplication>

#include "src/controllers/MainWindowController.h"
#include "src/controllers/user/UserCategoryEventWidgetController.h"
#include "src/controllers/user/UserIncidentWidgetController.h"
#include "src/controllers/user/UserScenarioRecommendationWidgetController.h"


#include "src/controllers/admin/AdminEditMenuController.h"

#include "src/controllers/admin/categories/edit/AdminEventCategoryBoxLayoutController.h"
#include "src/controllers/admin/categories/includedEvents/AdminInCategoryFreeEventBoxLayoutController.h"
#include "src/controllers/admin/categories/includedEvents/AdminInCategoryIncludedEventBoxLayoutController.h"

#include "src/controllers/admin/events/edit/AdminEventBoxLayoutController.h"

#include "src/controllers/admin/incidents/edit/AdminIncidentBoxLayoutController.h"
#include "src/controllers/admin/incidents/IncludedEvents/AdminInIncidentFreeEventBoxLayoutController.h"
#include "src/controllers/admin/incidents/IncludedEvents/AdminInIncidentIncludedEventBoxLayoutController.h"

#include "src/controllers/admin/scenaries/edit/AdminScenarioBoxLayoutController.h"
#include "src/controllers/admin/scenaries/IncludedIncidents/AdminInScenarioFreeIncidentBoxLayoutController.h"
#include "src/controllers/admin/scenaries/IncludedIncidents/AdminInScenarioIncludedIncidentBoxLayoutController.h"

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

    AdminEventCategoryBoxLayoutController adminEventCategoryController;
    AdminInCategoryFreeEventBoxLayoutController inCategoryFreeEventController;
    AdminInCategoryIncludedEventBoxLayoutController inCategoryIncludedEventController;

    AdminEventBoxLayoutController adminEventContoller;

    AdminIncidentBoxLayoutController adminIncidentController;
    AdminInIncidentFreeEventBoxLayoutController inIncidentFreeEventController;
    AdminInIncidentIncludedEventBoxLayoutController inIncidentIncludedEventController;

    AdminScenarioBoxLayoutController adminScenarioController;
    AdminInScenarioFreeIncidentBoxLayoutController inScenarioFreeIncidentController;
    AdminInScenarioIncludedIncidentBoxLayoutController inScenarioIncludedIncidentController;

    // Блок инициализации связи сигналов/слотов для пользователя


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




    // Блок инициализации связи сигналов/слотов для администратора

    /// Блок связи сигналов для создания списков в администрировании
    QObject::connect(&core, &CoreApp::signalAdminOpenCategories, &adminEventCategoryController, &AdminEventCategoryBoxLayoutController::setCategoryList);
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryListSet, &core, &CoreApp::formEvents);

    QObject::connect(&core, &CoreApp::eventsFormed, &adminEventContoller, &AdminEventBoxLayoutController::setEventList);
    QObject::connect(&core, &CoreApp::freeEventsFormed, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::setFreeEventList);

    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::eventListSet, &core, &CoreApp::formIncidents);
    QObject::connect(&core, &CoreApp::incidentsFormed, &adminIncidentController, &AdminIncidentBoxLayoutController::setIncidentList);

    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentListSet, &core, &CoreApp::formScenaries);
    QObject::connect(&core, &CoreApp::scenariesFormed, &adminScenarioController, &AdminScenarioBoxLayoutController::setScenarioList);

    // Блок связи сигналов для вкладки Категории событий

    /// Блок связи сигналов о присутствии/отсутствии активной категории
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsActive, &editMenuController, &AdminEditMenuController::slotSetCategoriesActive);
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsActive, &editMenuController, &AdminEditMenuController::slotSetAddCategoryButtonDisabled);

    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAllTabsEnable);
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAddCategoryButtonEnabled);


    /// Блок связи сохранения категории в бд
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoriesMustBeSaved, &core, &CoreApp::acceptCategoriesForSaving);

    /// Блок связи сигналов об установке/очистке списка открытой категории
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsOpened, &core, &CoreApp::onOpenCategory);
    QObject::connect(&core, &CoreApp::signalOpenAdminCategory, &inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::setIncludedEventList);
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsActive, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::enableAllFreeEvents);

    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsClosed, &inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::clearIncludedEventList);

    /// Блок связи записи событий в категорию и сохранение в базу данных
    QObject::connect(&inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::categoryEventsMustBeSaved, &core, &CoreApp::acceptEventCategoryForSaving);


    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsNotActive, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::unselectAllFreeEvents);
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsNotActive, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::disableAllFreeEvents);


    /// Блок связи сигналов о появлении свободных событий при удалении категории
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsDeleted, &core, &CoreApp::onOpenDeletedCategory);
    QObject::connect(&core, &CoreApp::signalOpenAdminDeletedCategory, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::addFreeEventsFromDeletedCategory);


    /// Блок связи сигналов о:  добавлении в категорию событий/удалении событий из категории
    QObject::connect(&inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::freeEventsIncludedInCategory, &inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::slotIncludeFreeEventsToCategory);
    QObject::connect(&inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::eventsRemovedFromCategory, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::slotUnincludeEventsFromCategory);


    /// Блок связи сигналов о нажатии кнопок Добавить/Удалить выбранное в категориях
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddCategoryButtonPressed, &adminEventCategoryController, &AdminEventCategoryBoxLayoutController::slotAddCategoryButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalDeleteSelectedCategoriesButtonPressed, &adminEventCategoryController, &AdminEventCategoryBoxLayoutController::slotDeleteSelectedCategoriesButtonPressed);


    /// Блок связи сигналов о нажатии кнопок Добавить выбранное в категорию/Удалить выбранное из категории
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddToCategoryButtonPressed, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::slotAddSelectedEventsToCategoryButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalRemoveFromCategoryButtonPressed, &inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::slotRemoveSelectedEventsFromCategoryButtonPressed);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранные категории
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::signalSelectedCategoriesNotEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedCategoriesButtonEnabled);
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::signalSelectedCategoriesEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedCategoriesButtonDisabled);


    /// Блок связи сигналов о добавлении/переименовании/удалении события для вкладки Категории событий
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::eventAdded, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::addDisabledFreeEvent);
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::eventRenamed, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::renameFreeEvent);
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::eventDeleted, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::slotDeleteFreeEvent);


    /// Блок связи сигналов о доступности/недоступности кнопки Добавить выбранное в категорию
    QObject::connect(&inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::signalSelectedFreeEventsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetAddToCategoryButtonEnabled);
    QObject::connect(&inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::signalSelectedFreeEventsEmpty, &editMenuController, &AdminEditMenuController::slotSetAddToCategoryButtonDisabled);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранное из категории
    QObject::connect(&inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::signalSelectedIncludedEventsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetRemoveFromCategoryButtonEnabled);
    QObject::connect(&inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::signalSelectedIncludedEventsEmpty, &editMenuController, &AdminEditMenuController::slotSetRemoveFromCategoryButtonDisabled);



    // Блок связи сигналов для вкладки События

    /// Блок связи сигналов о присутствии/отсутствии активного события
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::eventIsActive, &editMenuController, &AdminEditMenuController::slotSetEventsActive);
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::eventIsActive, &editMenuController, &AdminEditMenuController::slotSetAddEventButtonDisabled);


    /// Блок связи сохранения категории в бд
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::eventsMustBeSaved, &core, &CoreApp::acceptEventForSaving);


    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::eventIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAllTabsEnable);
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::eventIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAddEventButtonEnabled);


    /// Блок связи сигналов о нажатии кнопок Добавить/Удалить выбранное в событиях
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddEventButtonPressed, &adminEventContoller, &AdminEventBoxLayoutController::slotAddEventButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalDeleteSelectedEventsButtonPressed, &adminEventContoller, &AdminEventBoxLayoutController::slotDeleteSelectedEventsButtonPressed);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранные события
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::signalSelectedEventsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedEventsButtonEnabled);
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::signalSelectedEventsEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedEventsButtonDisabled);



    // Блок связи сигналов для вкладки Инциденты

    /// Блок связи сигналов о присутствии/отсутствии активного инцидента
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsActive, &editMenuController, &AdminEditMenuController::slotSetIncidentsActive);
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsActive, &editMenuController, &AdminEditMenuController::slotSetAddIncidentButtonDisabled);

    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAllTabsEnable);
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAddIncidentButtonEnabled);


    /// Блок связи сохранения категории в бд
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentsMustBeSaved, &core, &CoreApp::acceptIncidentsForSaving);


    /// Блок связи сигналов об установке/очистке списка открытого инцидента
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsOpened, &core, &CoreApp::onOpenAdminIncident);
    QObject::connect(&core, &CoreApp::signalOpenAdminIncident, &inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::setIncludedEventList);
    QObject::connect(&core, &CoreApp::freeEventsForIncidentFormed, &inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::setFreeEventList);

    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsClosed, &inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::clearIncludedEventList);
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsClosed, &inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::clearFreeEventList);

    /// Блок связи записи событий в инцидент и сохранение в базу данных
    QObject::connect(&inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::incidentEventsMustBeSaved, &core, &CoreApp::acceptEventIncidentsForSaving);/////


    /// Блок связи сигналов о добавлении в инцидент событий/удалении событий из инцидента
    QObject::connect(&inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::freeEventsIncludedInIncident, &inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::slotIncludeFreeEventsToIncident);
    QObject::connect(&inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::eventsRemovedFromIncident, &inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::slotUnincludeEventsFromIncident);


    /// Блок связи сигналов о нажатии кнопок Добавить/Удалить выбранное в инцидентах
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddIncidentButtonPressed, &adminIncidentController, &AdminIncidentBoxLayoutController::slotAddIncidentButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalDeleteSelectedIncidentsButtonPressed, &adminIncidentController, &AdminIncidentBoxLayoutController::slotDeleteSelectedIncidentsButtonPressed);


    /// Блок связи сигналов о нажатии кнопок Добавить выбранное в инцидент/Удалить выбранное из инцидента
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddToIncidentButtonPressed, &inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::slotAddSelectedEventsToIncidentButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalRemoveFromIncidentButtonPressed, &inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::slotRemoveSelectedEventsFromIncidentButtonPressed);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранные инциденты
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::signalSelectedIncidentsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedIncidentsButtonEnabled);
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::signalSelectedIncidentsEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedIncidentsButtonDisabled);


    /// Блок связи сигналов о доступности/недоступности кнопки Добавить выбранное в инцидент
    QObject::connect(&inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::signalSelectedFreeEventsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetAddToIncidentButtonEnabled);
    QObject::connect(&inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::signalSelectedFreeEventsEmpty, &editMenuController, &AdminEditMenuController::slotSetAddToIncidentButtonDisabled);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранное из инцидента
    QObject::connect(&inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::signalSelectedIncludedEventsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetRemoveFromIncidentButtonEnabled);
    QObject::connect(&inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::signalSelectedIncludedEventsEmpty, &editMenuController, &AdminEditMenuController::slotSetRemoveFromIncidentButtonDisabled);



    // Блок связи сигналов для вкладки Сценарии

    /// Блок связи сигналов о присутствии/отсутствии активного сценария
    QObject::connect(&adminScenarioController, &AdminScenarioBoxLayoutController::scenarioIsActive, &editMenuController, &AdminEditMenuController::slotSetScenariesActive);
    QObject::connect(&adminScenarioController, &AdminScenarioBoxLayoutController::scenarioIsActive, &editMenuController, &AdminEditMenuController::slotSetAddScenarioButtonDisabled);

    QObject::connect(&adminScenarioController, &AdminScenarioBoxLayoutController::scenarioIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAllTabsEnable);
    QObject::connect(&adminScenarioController, &AdminScenarioBoxLayoutController::scenarioIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAddScenarioButtonEnabled);


    /// Блок связи сохранения категории в бд
    //QObject::connect(&adminScenarioController, &AdminScenarioBoxLayoutController::scenariesMustBeSaved, ...);


    /// Блок связи сигналов об установке/очистке списка открытого сценария
    QObject::connect(&adminScenarioController, &AdminScenarioBoxLayoutController::scenarioIsOpened, &core, &CoreApp::onOpenAdminScenario);
    QObject::connect(&core, &CoreApp::signalOpenAdminScenario, &inScenarioIncludedIncidentController, &AdminInScenarioIncludedIncidentBoxLayoutController::setIncludedIncidentList);
    QObject::connect(&core, &CoreApp::freeIncidentsForScenarioFormed, &inScenarioFreeIncidentController, &AdminInScenarioFreeIncidentBoxLayoutController::setFreeIncidentList);

    QObject::connect(&adminScenarioController, &AdminScenarioBoxLayoutController::scenarioIsClosed, &inScenarioIncludedIncidentController, &AdminInScenarioIncludedIncidentBoxLayoutController::clearIncludedIncidentList);
    QObject::connect(&adminScenarioController, &AdminScenarioBoxLayoutController::scenarioIsClosed, &inScenarioFreeIncidentController, &AdminInScenarioFreeIncidentBoxLayoutController::clearFreeIncidentList);

    /// Блок связи записи событий в инцидент и сохранение в базу данных
    //QObject::connect(&inScenarioIncludedIncidentController, &AdminInScenarioIncludedIncidentBoxLayoutController::scenarioIncidentMustBeSaved, идет в бд или в ядро, где данные events сохраняются в категорию по incidentID);


    /// Блок связи сигналов о добавлении в сценарий инцидентов/удалении инцидентов из сценария
    QObject::connect(&inScenarioFreeIncidentController, &AdminInScenarioFreeIncidentBoxLayoutController::freeIncidentsIncludedInScenario, &inScenarioIncludedIncidentController, &AdminInScenarioIncludedIncidentBoxLayoutController::slotIncludeFreeIncidentsToScenario);
    QObject::connect(&inScenarioIncludedIncidentController, &AdminInScenarioIncludedIncidentBoxLayoutController::incidentsRemovedFromScenario, &inScenarioFreeIncidentController, &AdminInScenarioFreeIncidentBoxLayoutController::slotUnincludeIncidentsFromScenario);


    /// Блок связи сигналов о нажатии кнопок Добавить/Удалить выбранное в сценариях
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddScenarioButtonPressed, &adminScenarioController, &AdminScenarioBoxLayoutController::slotAddScenarioButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalDeleteSelectedScenariesButtonPressed, &adminScenarioController, &AdminScenarioBoxLayoutController::slotDeleteSelectedScenariesButtonPressed);


    /// Блок связи сигналов о нажатии кнопок Добавить выбранное в сценарий/Удалить выбранное из сценария
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddToScenarioButtonPressed, &inScenarioFreeIncidentController, &AdminInScenarioFreeIncidentBoxLayoutController::slotAddSelectedIncidentsToScenarioButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalRemoveFromScenarioButtonPressed, &inScenarioIncludedIncidentController, &AdminInScenarioIncludedIncidentBoxLayoutController::slotRemoveSelectedIncidentsFromScenarioButtonPressed);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранные сценарии
    QObject::connect(&adminScenarioController, &AdminScenarioBoxLayoutController::signalSelectedScenariesNotEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedScenariesButtonEnabled);
    QObject::connect(&adminScenarioController, &AdminScenarioBoxLayoutController::signalSelectedScenariesEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedScenariesButtonDisabled);


    /// Блок связи сигналов о доступности/недоступности кнопки Добавить выбранное в сценарий
    QObject::connect(&inScenarioFreeIncidentController, &AdminInScenarioFreeIncidentBoxLayoutController::signalSelectedFreeIncidentsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetAddToScenarioButtonEnabled);
    QObject::connect(&inScenarioFreeIncidentController, &AdminInScenarioFreeIncidentBoxLayoutController::signalSelectedFreeIncidentsEmpty, &editMenuController, &AdminEditMenuController::slotSetAddToScenarioButtonDisabled);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранное из сценария
    QObject::connect(&inScenarioIncludedIncidentController, &AdminInScenarioIncludedIncidentBoxLayoutController::signalSelectedIncludedIncidentsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetRemoveFromScenarioButtonEnabled);
    QObject::connect(&inScenarioIncludedIncidentController, &AdminInScenarioIncludedIncidentBoxLayoutController::signalSelectedIncludedIncidentsEmpty, &editMenuController, &AdminEditMenuController::slotSetRemoveFromScenarioButtonDisabled);



    // Инициализация контроллеров пользовательского интерфейса
    controller.init(mainWindow);

    categoryEventController.init(mainWindow->getMainMenuWidget());
    incidentController.init(mainWindow->getIncidentMenuWidget());
    scenarioRecommendationController.init(mainWindow->getScenarioMenuWidget());

    // Инициализация контроллеров административного интерфейса
    editMenuController.init(mainWindow->getEditMenuWidget());

    adminEventCategoryController.init(mainWindow->getEditMenuWidget()->getBoxLayoutCategories());
    inCategoryFreeEventController.init(mainWindow->getEditMenuWidget()->getBoxLayoutInCategoryFreeEvents());
    inCategoryIncludedEventController.init(mainWindow->getEditMenuWidget()->getBoxLayoutInCategoryIncludedEvents());

    adminEventContoller.init(mainWindow->getEditMenuWidget()->getBoxLayoutEvents());

    adminIncidentController.init(mainWindow->getEditMenuWidget()->getBoxLayoutIncidents());
    inIncidentFreeEventController.init(mainWindow->getEditMenuWidget()->getBoxLayoutInIncidentFreeEvents());
    inIncidentIncludedEventController.init(mainWindow->getEditMenuWidget()->getBoxLayoutInIncidentIncludedEvents());

    adminScenarioController.init(mainWindow->getEditMenuWidget()->getBoxLayoutScenaries());
    inScenarioFreeIncidentController.init(mainWindow->getEditMenuWidget()->getBoxLayoutInScenarioFreeIncidents());
    inScenarioIncludedIncidentController.init(mainWindow->getEditMenuWidget()->getBoxLayoutInScenarioIncludedIncidents());

    // Инициализация ядря
    core.init();

    // Старт интерфейса
    controller.show();

    return a.exec();
}
