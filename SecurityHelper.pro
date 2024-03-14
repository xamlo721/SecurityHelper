QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


FORMS += ui/MainWindow.ui \
    ui/MenuSelectedWidget.ui \
    ui/admin/AdminCategoriesWidget.ui \
    ui/admin/AdminEditMenuWidget.ui \
    ui/admin/AdminEventsWidget.ui \
    ui/admin/AdminIncidentsWidget.ui \
    ui/admin/AdminRecommendationWidget.ui \
    ui/admin/AdminScenariesWidget.ui \
    ui/admin/dialogs/AdminEditCatorgyDialog.ui \
    ui/admin/dialogs/AdminEventDialog.ui \
    ui/admin/dialogs/AdminIncidentDialog.ui \
    ui/admin/dialogs/AdminRecommendationDialog.ui \
    ui/admin/dialogs/AdminScenariesDialog.ui \
    ui/user/IncidentMenuWidget.ui \
    ui/user/IncidentWidget.ui \
    ui/user/MainMenuWidget.ui \
    ui/user/RecommendationsWidget.ui \
    ui/user/ScenarioMenuWidget.ui \
    ui/user/ScenarioWidget.ui \
    ui/SelectedWidget.ui

HEADERS += \
    src/controllers/MainWindowController.h \
    src/controllers/admin/AdminEditMenuController.h \
    src/controllers/admin/AdminEventsController.h \
    src/controllers/admin/CategoryController.h \
    src/controllers/admin/IncidentController.h \
    src/controllers/admin/AdminRecommendationsController.h \
    src/controllers/admin/ScenariesController.h \
    src/controllers/user/UserEventsController.h \
    src/controllers/user/UserIncidentWidgetController.h \
    src/controllers/user/UserRecommendationController.h \
    src/controllers/user/UserScenarioController.h \
    src/exception/Exception.h \
    src/exception/FileOperationException.h \
    src/exception/IllegalArgumentException.h \
    src/exception/ParsingException.h \
    src/exception/UnsupportedOperationException.h \
    src/items/SecurityEvent.h \
    src/items/SecurityEventCategory.h \
    src/items/SecurityIncident.h \
    src/items/SecurityRecommendations.h \
    src/items/SecurityScenario.h \
    src/logic/CoreApp.h \
    src/logic/Database.h \
    src/logic/XMLHelper.h \
    src/logic/XmlUtils.h \
    src/ui/EnumMenuPages.h \
    src/ui/EnumToolbarPages.h \
    src/ui/MainWindow.h \
    src/ui/SelectedWidget.h \
    src/ui/admin/AdminEditMenuWidget.h \
    src/items/BaseItem.h \
    src/ui/admin/EnumMessageBoxItemVariants.h \
    src/ui/admin/EnumMessageBoxVariants.h \
    src/ui/admin/ItemDeletionMessageBox.h \
    src/ui/user/IncidentMenuWidget.h \
    src/ui/user/IncidentWidget.h \
    src/ui/user/MainMenuWidget.h \
    src/ui/user/RecommendationsWidget.h \
    src/ui/user/ScenarioMenuWidget.h \
    src/ui/user/ScenarioWidget.h \
    src/ui/admin/AdminCategoriesWidget.h \
    src/ui/admin/AdminEventsWidget.h \
    src/ui/admin/AdminIncidentsWidget.h \
    src/ui/admin/AdminRecommendationWidget.h \
    src/ui/admin/AdminScenariesWidget.h \
    src/ui/MenuSelectedWidget.h \
    src/ui/admin/dialogs/AdminEditCatorgyDialog.h \
    src/ui/admin/dialogs/AdminEventDialog.h \
    src/ui/admin/dialogs/AdminIncidentDialog.h \
    src/ui/admin/dialogs/AdminRecommendationDialog.h \
    src/ui/admin/dialogs/AdminScenariesDialog.h

SOURCES += \
    src/controllers/MainWindowController.cpp \
    src/controllers/admin/AdminEditMenuController.cpp \
    src/controllers/admin/AdminEventsController.cpp \
    src/controllers/admin/CategoryController.cpp \
    src/controllers/admin/IncidentController.cpp \
    src/controllers/admin/AdminRecommendationsController.cpp \
    src/controllers/admin/ScenariesController.cpp \
    src/controllers/user/UserEventsController.cpp \
    src/controllers/user/UserIncidentWidgetController.cpp \
    src/controllers/user/UserRecommendationController.cpp \
    src/controllers/user/UserScenarioController.cpp \
    src/items/SecurityEvent.cpp \
    src/items/SecurityEventCategory.cpp \
    src/items/SecurityIncident.cpp \
    src/items/SecurityRecommendations.cpp \
    src/items/SecurityScenario.cpp \
    src/logic/CoreApp.cpp \
    src/logic/CoreAppUserLogic.cpp \
    src/logic/Database.cpp \
    src/logic/XMLHelper.cpp \
    src/logic/XmlUtils.cpp \
    src/main.cpp \
    src/ui/MainWindow.cpp \
    src/ui/SelectedWidget.cpp \
    src/ui/admin/AdminEditMenuWidget.cpp \
    src/ui/admin/ItemDeletionMessageBox.cpp \
    src/ui/user/IncidentMenuWidget.cpp \
    src/ui/user/IncidentWidget.cpp \
    src/ui/user/MainMenuWidget.cpp \
    src/ui/user/RecommendationsWidget.cpp \
    src/ui/user/ScenarioMenuWidget.cpp \
    src/ui/user/ScenarioWidget.cpp \
    src/ui/admin/AdminCategoriesWidget.cpp \
    src/ui/admin/AdminEventsWidget.cpp \
    src/ui/admin/AdminIncidentsWidget.cpp \
    src/ui/admin/AdminRecommendationWidget.cpp \
    src/ui/admin/AdminScenariesWidget.cpp \
    src/ui/MenuSelectedWidget.cpp \
    src/ui/admin/dialogs/AdminEditCatorgyDialog.cpp \
    src/ui/admin/dialogs/AdminEventDialog.cpp \
    src/ui/admin/dialogs/AdminIncidentDialog.cpp \
    src/ui/admin/dialogs/AdminRecommendationDialog.cpp \
    src/ui/admin/dialogs/AdminScenariesDialog.cpp

DISTFILES += \
    rss/StockDatabase/Categories.xml \
    rss/StockDatabase/Events.xml \
    rss/StockDatabase/Incidents.xml \
    rss/StockDatabase/Recommendations.xml \
    rss/StockDatabase/Scenaries.xml \
    storage/Categories.xml \
    storage/Events.xml \
    storage/Incidents.xml \
    storage/Recommendations.xml \
    storage/Scenaries.xml

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rss/images.qrc
