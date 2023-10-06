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

    AdminEventCategoryBoxLayoutController eventCategoryContoller;
    AdminInCategoryFreeEventBoxLayoutController inCategoryFreeEventController;
    AdminInCategoryIncludedEventBoxLayoutController inCategoryIncludedEventController;

    AdminEventBoxLayoutController eventBoxContoller;



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
    QObject::connect(&core, &CoreApp::signalAdminOpenCategories, &eventCategoryContoller, &AdminEventCategoryBoxLayoutController::setCategoryList);
    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::categoriesSet, &core, &CoreApp::formEvents);
    QObject::connect(&core, &CoreApp::eventsFormed, &eventBoxContoller, &AdminEventBoxLayoutController::setEventList);
    QObject::connect(&core, &CoreApp::freeEventsFormed, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::setFreeEventList);




    // Блок связи сигналов для вкладки Категории событий

    /// Блок связи сигналов о присутствии/отсутствии активной категории
    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::categoryIsActive, &editMenuController, &AdminEditMenuController::slotSetCategoriesActive);
    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::categoryIsActive, &editMenuController, &AdminEditMenuController::slotSetAddCategoryButtonDisabled);

    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::categoryIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAllTabsEnable);
    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::categoryIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAddCategoryButtonEnabled);


    /// Блок связи сигналов об установке/очистке списка открытой категории
    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::categoryIsOpened, &core, &CoreApp::onOpenCategory);
    QObject::connect(&core, &CoreApp::signalOpenAdminCategory, &inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::setIncludedEventList);
    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::categoryIsActive, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::enableAllFreeEvents);

    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::categoryIsClosed, &inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::clearIncludedEventList);
    //QObject::connect(&inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::categoryEventsMustBeSaved, идет в бд или в ядро, где данные events сохраняются в категорию по categoryID);
    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::categoryIsNotActive, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::unselectAllFreeEvents);
    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::categoryIsNotActive, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::disableAllFreeEvents);


    /// Блок связи сигналов о появлении свободных событий при удалении категории
    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::categoryIsDeleted, &core, &CoreApp::onOpenDeletedCategory);
    QObject::connect(&core, &CoreApp::signalOpenAdminDeletedCategory, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::addFreeEventsFromDeletedCategory);


    /// Блок связи сигналов о:  добавлении в категорию событий/удалении событий из категории
    QObject::connect(&inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::freeEventsIncludedInCategory, &inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::slotIncludeFreeEventsToCategory);
    QObject::connect(&inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::eventsRemovedFromCategory, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::slotUnincludeEventsFromCategory);


    /// Блок связи сигналов о нажатии кнопок Добавить/Удалить выбранное в категориях
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddCategoryButtonPressed, &eventCategoryContoller, &AdminEventCategoryBoxLayoutController::slotAddCategoryButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalDeleteSelectedCategoriesButtonPressed, &eventCategoryContoller, &AdminEventCategoryBoxLayoutController::slotDeleteSelectedCategoriesButtonPressed);


    /// Блок связи сигналов о нажатии кнопок Добавить выбранное в категорию/Удалить выбранное из категории
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddToCategoryButtonPressed, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::slotAddSelectedEventsToCategoryButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalRemoveFromCategoryButtonPressed, &inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::slotRemoveSelectedEventsFromCategoryButtonPressed);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранные категории
    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::signalSelectedCategoriesNotEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedCategoriesButtonEnabled);
    QObject::connect(&eventCategoryContoller, &AdminEventCategoryBoxLayoutController::signalSelectedCategoriesEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedCategoriesButtonDisabled);


    /// Блок связи сигналов о добавлении/переименовании/удалении события для вкладки Категории событий
    QObject::connect(&eventBoxContoller, &AdminEventBoxLayoutController::eventAdded, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::addDisabledFreeEvent);
    QObject::connect(&eventBoxContoller, &AdminEventBoxLayoutController::eventRenamed, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::renameFreeEvent);
    QObject::connect(&eventBoxContoller, &AdminEventBoxLayoutController::eventDeleted, &inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::slotDeleteFreeEvent);


    /// Блок связи сигналов о доступности/недоступности кнопки Добавить выбранное в категорию
    QObject::connect(&inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::signalSelectedFreeEventsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetAddToCategoryButtonEnabled);
    QObject::connect(&inCategoryFreeEventController, &AdminInCategoryFreeEventBoxLayoutController::signalSelectedFreeEventsEmpty, &editMenuController, &AdminEditMenuController::slotSetAddToCategoryButtonDisabled);


    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранное из категории
    QObject::connect(&inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::signalSelectedIncludedEventsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetRemoveFromCategoryButtonEnabled);
    QObject::connect(&inCategoryIncludedEventController, &AdminInCategoryIncludedEventBoxLayoutController::signalSelectedIncludedEventsEmpty, &editMenuController, &AdminEditMenuController::slotSetRemoveFromCategoryButtonDisabled);



    // Блок связи сигналов для вкладки События

    /// Блок связи сигналов о присутствии/отсутствии активного события
    QObject::connect(&eventBoxContoller, &AdminEventBoxLayoutController::eventIsActive, &editMenuController, &AdminEditMenuController::slotSetEventsActive);
    QObject::connect(&eventBoxContoller, &AdminEventBoxLayoutController::eventIsActive, &editMenuController, &AdminEditMenuController::slotSetAddEventButtonDisabled);

    QObject::connect(&eventBoxContoller, &AdminEventBoxLayoutController::eventIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAllTabsEnable);
    QObject::connect(&eventBoxContoller, &AdminEventBoxLayoutController::eventIsNotActive, &editMenuController, &AdminEditMenuController::slotSetAddEventButtonEnabled);

    /// Блок связи сигналов о нажатии кнопок Добавить/Удалить выбранное в событиях
    QObject::connect(&editMenuController, &AdminEditMenuController::signalAddEventButtonPressed, &eventBoxContoller, &AdminEventBoxLayoutController::slotAddEventButtonPressed);
    QObject::connect(&editMenuController, &AdminEditMenuController::signalDeleteSelectedEventsButtonPressed, &eventBoxContoller, &AdminEventBoxLayoutController::slotDeleteSelectedEventsButtonPressed);

    /// Блок связи сигналов о доступности/недоступности кнопки Удалить выбранные события
    QObject::connect(&eventBoxContoller, &AdminEventBoxLayoutController::signalSelectedEventsNotEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedEventsButtonEnabled);
    QObject::connect(&eventBoxContoller, &AdminEventBoxLayoutController::signalSelectedEventsEmpty, &editMenuController, &AdminEditMenuController::slotSetDeleteSelectedEventsButtonDisabled);

    // Инициализация контроллеров пользовательского интерфейса
    controller.init(mainWindow);

    categoryEventController.init(mainWindow->getMainMenuWidget());
    incidentController.init(mainWindow->getIncidentMenuWidget());
    scenarioRecommendationController.init(mainWindow->getScenarioMenuWidget());

    // Инициализация контроллеров административного интерфейса
    editMenuController.init(mainWindow->getEditMenuWidget());

    eventCategoryContoller.init(mainWindow->getEditMenuWidget()->getBoxLayoutCategories());
    inCategoryFreeEventController.init(mainWindow->getEditMenuWidget()->getBoxLayoutInCategoryFreeEvents());
    inCategoryIncludedEventController.init(mainWindow->getEditMenuWidget()->getBoxLayoutInCategoryIncludedEvents());

    eventBoxContoller.init(mainWindow->getEditMenuWidget()->getBoxLayoutEvents());

    // Инициализация ядря
    core.init();

    // Старт интерфейса
    controller.show();

    return a.exec();
}
