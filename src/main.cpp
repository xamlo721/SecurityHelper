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



    // Блок связи сигналов для вкладки Категории событий

    /// Блок связи сигналов о присутствии/отсутствии активной категории
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsActive, &editMenuController, &AdminEditMenuController::slotSetCategoriesActive);
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsActive, &editMenuController, &AdminEditMenuController::slotSetAddCategoryButtonDisabled);

    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAllTabsEnable);
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAddCategoryButtonEnabled);


    /// Блок связи сохранения категории в бд
    //QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoriesMustBeSaved, ...);

    /// Блок связи сигналов об установке/очистке списка открытой категории
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsOpened, &core, &CoreApp::onOpenCategory);
    QObject::connect(&core, &CoreApp::signalOpenAdminCategory, &inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::setIncludedEventList);
    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsActive, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::enableAllFreeEvents);

    QObject::connect(&adminEventCategoryController, &AdminEventCategoryBoxLayoutController::categoryIsClosed, &inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::clearIncludedEventList);

    /// Блок связи записи событий в категорию и сохранение в базу данных
    //QObject::connect(&inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::categoryEventsMustBeSaved, идет в бд или в ядро, где данные events сохраняются в категорию по categoryID);


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
    //QObject::connect(&adminEventController, &AdminEventBoxLayoutController::eventsMustBeSaved, ...);


    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::eventIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAllTabsEnable);
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::eventIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAddEventButtonEnabled);


    /// Блок связи сигналов о нажатии кнопок Добавить/Удалить выбранное в событиях
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddEventButtonPressed, &adminEventContoller, &AdminEventBoxLayoutController::slotAddEventButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalDeleteSelectedEventsButtonPressed, &adminEventContoller, &AdminEventBoxLayoutController::slotDeleteSelectedEventsButtonPressed);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранные события
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::signalSelectedEventsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedEventsButtonEnabled);
    QObject::connect(&adminEventContoller, &AdminEventBoxLayoutController::signalSelectedEventsEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedEventsButtonDisabled);



    // Блок связи сигналов для вкладки Инциденты

    /// Блок связи сигналов о присутствии/отсутствии активной категории
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsActive, &editMenuController, &AdminEditMenuController::slotSetIncidentsActive);
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsActive, &editMenuController, &AdminEditMenuController::slotSetAddIncidentButtonDisabled);

    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAllTabsEnable);
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAddIncidentButtonEnabled);


    /// Блок связи сохранения категории в бд
    //QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentsMustBeSaved, ...);


    /// Блок связи сигналов об установке/очистке списка открытой категории
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsOpened, &core, &CoreApp::onOpenAdminIncident);
    QObject::connect(&core, &CoreApp::signalOpenAdminIncident, &inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::setIncludedEventList);
    QObject::connect(&core, &CoreApp::freeEventsForIncidentFormed, &inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::setFreeEventList);

    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsClosed, &inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::clearIncludedEventList);
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::incidentIsClosed, &inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::clearFreeEventList);

    /// Блок связи записи событий в инцидент и сохранение в базу данных
    //QObject::connect(&inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::incidentEventsMustBeSaved, идет в бд или в ядро, где данные events сохраняются в категорию по incidentID);


    /// Блок связи сигналов о:  добавлении в категорию событий/удалении событий из категории
    QObject::connect(&inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::freeEventsIncludedInIncident, &inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::slotIncludeFreeEventsToIncident);
    QObject::connect(&inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::eventsRemovedFromIncident, &inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::slotUnincludeEventsFromIncident);


    /// Блок связи сигналов о нажатии кнопок Добавить/Удалить выбранное в категориях
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddIncidentButtonPressed, &adminIncidentController, &AdminIncidentBoxLayoutController::slotAddIncidentButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalDeleteSelectedIncidentsButtonPressed, &adminIncidentController, &AdminIncidentBoxLayoutController::slotDeleteSelectedIncidentsButtonPressed);


    /// Блок связи сигналов о нажатии кнопок Добавить выбранное в категорию/Удалить выбранное из категории
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddToIncidentButtonPressed, &inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::slotAddSelectedEventsToIncidentButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalRemoveFromIncidentButtonPressed, &inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::slotRemoveSelectedEventsFromIncidentButtonPressed);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранные категории
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::signalSelectedIncidentsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedIncidentsButtonEnabled);
    QObject::connect(&adminIncidentController, &AdminIncidentBoxLayoutController::signalSelectedIncidentsEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedIncidentsButtonDisabled);


    /// Блок связи сигналов о доступности/недоступности кнопки Добавить выбранное в категорию
    QObject::connect(&inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::signalSelectedFreeEventsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetAddToIncidentButtonEnabled);
    QObject::connect(&inIncidentFreeEventController, &AdminInIncidentFreeEventBoxLayoutController::signalSelectedFreeEventsEmpty, &editMenuController, &AdminEditMenuController::slotSetAddToIncidentButtonDisabled);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранное из категории
    QObject::connect(&inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::signalSelectedIncludedEventsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetRemoveFromIncidentButtonEnabled);
    QObject::connect(&inIncidentIncludedEventController, &AdminInIncidentIncludedEventBoxLayoutController::signalSelectedIncludedEventsEmpty, &editMenuController, &AdminEditMenuController::slotSetRemoveFromIncidentButtonDisabled);



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

    // Инициализация ядря
    core.init();

    // Старт интерфейса
    controller.show();

    return a.exec();
}
