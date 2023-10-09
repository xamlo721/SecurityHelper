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
    ui/admin/scenaries/includedIncidents/InScenarioIncidentWidget.ui \
    ui/admin/scenaries/edit/EditableScenarioWidget.ui \
    ui/admin/scenaries/edit/UneditableScenarioWidget.ui \
    ui/admin/incidents/includedEvents/InIncidentEventWidget.ui \
    ui/admin/incidents/edit/EditableIncidentWidget.ui \
    ui/admin/incidents/edit/UneditableIncidentWidget.ui \
    ui/admin/categories/includedEvents/InCategoryEventWidget.ui \
    ui/admin/events/edit/UneditableEventWidget.ui \
    ui/admin/categories/edit/UneditableEventCategoryWidget.ui \
    ui/admin/AdminEditMenuWidget.ui \
    ui/admin/categories/edit/EditableEventCategoryWidget.ui \
    ui/admin/events/edit/EditableEventWidget.ui \
    ui/user/EventWidget.ui \
    ui/user/IncidentCategoryWidget.ui \
    ui/user/IncidentMenuWidget.ui \
    ui/user/IncidentWidget.ui \
    ui/user/MainMenuWidget.ui \
    ui/user/RecommendationsWidget.ui \
    ui/user/ScenarioMenuWidget.ui \
    ui/user/ScenarioWidget.ui

HEADERS += \
    src/controllers/MainWindowController.h \
    src/controllers/admin/AdminEditMenuController.h \
    src/controllers/admin/categories/includedEvents/AdminInCategoryFreeEventBoxLayoutController.h \
    src/controllers/admin/categories/includedEvents/AdminInCategoryIncludedEventBoxLayoutController.h \
    src/controllers/admin/events/edit/AdminEventBoxLayoutController.h \
    src/controllers/admin/categories/edit/AdminEventCategoryBoxLayoutController.h \
    src/controllers/admin/incidents/IncludedEvents/AdminInIncidentFreeEventBoxLayoutController.h \
    src/controllers/admin/incidents/IncludedEvents/AdminInIncidentIncludedEventBoxLayoutController.h \
    src/controllers/admin/incidents/edit/AdminIncidentBoxLayoutController.h \
    src/controllers/admin/scenaries/IncludedIncidents/AdminInScenarioFreeIncidentBoxLayoutController.h \
    src/controllers/admin/scenaries/IncludedIncidents/AdminInScenarioIncludedIncidentBoxLayoutController.h \
    src/controllers/admin/scenaries/edit/AdminScenarioBoxLayoutController.h \
    src/controllers/user/UserScenarioRecommendationWidgetController.h \
    src/controllers/user/UserCategoryEventWidgetController.h \
    src/controllers/user/UserIncidentWidgetController.h \
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
    src/ui/admin/AdminEditMenuWidget.h \
    src/items/BaseItem.h \
    src/ui/admin/EnumMessageBoxItemVariants.h \
    src/ui/admin/EnumMessageBoxVariants.h \
    src/ui/admin/ItemDeletionMessageBox.h \
    src/ui/admin/categories/edit/AdminEventCategoryBoxLayout.h \
    src/ui/admin/UneditableItemMenu.h \
    src/ui/admin/categories/edit/EditableEventCategoryWidget.h \
    src/ui/admin/categories/includedEvents/AdminInCategoryEventBoxLayout.h \
    src/ui/admin/categories/includedEvents/InCategoryEventWidget.h \
    src/ui/admin/categories/includedEvents/InCategoryEventWidgetStorage.h \
    src/ui/admin/events/edit/AdminEventBoxLayout.h \
    src/ui/admin/events/edit/EditableEventWidget.h \
    src/ui/admin/categories/edit/EventCategoryWidgetStorage.h \
    src/ui/admin/categories/edit/UneditableEventCategoryWidget.h \
    src/ui/admin/events/edit/EventWidgetStorage.h \
    src/ui/admin/events/edit/UneditableEventWidget.h \
    src/ui/admin/incidents/edit/AdminIncidentBoxLayout.h \
    src/ui/admin/incidents/edit/EditableIncidentWidget.h \
    src/ui/admin/incidents/edit/IncidentWidgetStorage.h \
    src/ui/admin/incidents/edit/UneditableIncidentWidget.h \
    src/ui/admin/incidents/includedEvents/AdminInIncidentEventBoxLayout.h \
    src/ui/admin/incidents/includedEvents/InIncidentEventWidget.h \
    src/ui/admin/incidents/includedEvents/InIncidentEventWidgetStorage.h \
    src/ui/admin/scenaries/edit/AdminScenarioBoxLayout.h \
    src/ui/admin/scenaries/edit/EditableScenarioWidget.h \
    src/ui/admin/scenaries/edit/ScenarioWidgetStorage.h \
    src/ui/admin/scenaries/edit/UneditableScenarioWidget.h \
    src/ui/admin/scenaries/includedIncidents/AdminInScenarioIncidentBoxLayout.h \
    src/ui/admin/scenaries/includedIncidents/InScenarioIncidentWidget.h \
    src/ui/admin/scenaries/includedIncidents/InScenarioIncidentWidgetStorage.h \
    src/ui/user/EventCategoryWidget.h \
    src/ui/user/EventWidget.h \
    src/ui/user/IncidentMenuWidget.h \
    src/ui/user/IncidentWidget.h \
    src/ui/user/MainMenuWidget.h \
    src/ui/user/RecommendationsWidget.h \
    src/ui/user/ScenarioMenuWidget.h \
    src/ui/user/ScenarioWidget.h

SOURCES += \
    src/controllers/MainWindowController.cpp \
    src/controllers/admin/AdminEditMenuController.cpp \
    src/controllers/admin/categories/includedEvents/AdminInCategoryFreeEventBoxLayoutController.cpp \
    src/controllers/admin/categories/includedEvents/AdminInCategoryIncludedEventBoxLayoutController.cpp \
    src/controllers/admin/events/edit/AdminEventBoxLayoutController.cpp \
    src/controllers/admin/categories/edit/AdminEventCategoryBoxLayoutController.cpp \
    src/controllers/admin/incidents/IncludedEvents/AdminInIncidentFreeEventBoxLayoutController.cpp \
    src/controllers/admin/incidents/IncludedEvents/AdminInIncidentIncludedEventBoxLayoutController.cpp \
    src/controllers/admin/incidents/edit/AdminIncidentBoxLayoutController.cpp \
    src/controllers/admin/scenaries/IncludedIncidents/AdminInScenarioFreeIncidentBoxLayoutController.cpp \
    src/controllers/admin/scenaries/IncludedIncidents/AdminInScenarioIncludedIncidentBoxLayoutController.cpp \
    src/controllers/admin/scenaries/edit/AdminScenarioBoxLayoutController.cpp \
    src/controllers/user/UserScenarioRecommendationWidgetController.cpp \
    src/controllers/user/UserCategoryEventWidgetController.cpp \
    src/controllers/user/UserIncidentWidgetController.cpp \
    src/items/SecurityEvent.cpp \
    src/items/SecurityEventCategory.cpp \
    src/items/SecurityIncident.cpp \
    src/items/SecurityRecommendations.cpp \
    src/items/SecurityScenario.cpp \
    src/logic/CoreApp.cpp \
    src/logic/Database.cpp \
    src/logic/XMLHelper.cpp \
    src/logic/XmlUtils.cpp \
    src/main.cpp \
    src/ui/MainWindow.cpp \
    src/ui/admin/AdminEditMenuWidget.cpp \
    src/ui/admin/ItemDeletionMessageBox.cpp \
    src/ui/admin/categories/edit/AdminEventCategoryBoxLayout.cpp \
    src/ui/admin/UneditableItemMenu.cpp \
    src/ui/admin/categories/edit/EditableEventCategoryWidget.cpp \
    src/ui/admin/categories/includedEvents/AdminInCategoryEventBoxLayout.cpp \
    src/ui/admin/categories/includedEvents/InCategoryEventWidget.cpp \
    src/ui/admin/categories/includedEvents/InCategoryEventWidgetStorage.cpp \
    src/ui/admin/events/edit/AdminEventBoxLayout.cpp \
    src/ui/admin/events/edit/EditableEventWidget.cpp \
    src/ui/admin/categories/edit/EventCategoryWidgetStorage.cpp \
    src/ui/admin/categories/edit/UneditableEventCategoryWidget.cpp \
    src/ui/admin/events/edit/EventWidgetStorage.cpp \
    src/ui/admin/events/edit/UneditableEventWidget.cpp \
    src/ui/admin/incidents/edit/AdminIncidentBoxLayout.cpp \
    src/ui/admin/incidents/edit/EditableIncidentWidget.cpp \
    src/ui/admin/incidents/edit/IncidentWidgetStorage.cpp \
    src/ui/admin/incidents/edit/UneditableIncidentWidget.cpp \
    src/ui/admin/incidents/includedEvents/AdminInIncidentEventBoxLayout.cpp \
    src/ui/admin/incidents/includedEvents/InIncidentEventWidget.cpp \
    src/ui/admin/incidents/includedEvents/InIncidentEventWidgetStorage.cpp \
    src/ui/admin/scenaries/edit/AdminScenarioBoxLayout.cpp \
    src/ui/admin/scenaries/edit/EditableScenarioWidget.cpp \
    src/ui/admin/scenaries/edit/ScenarioWidgetStorage.cpp \
    src/ui/admin/scenaries/edit/UneditableScenarioWidget.cpp \
    src/ui/admin/scenaries/includedIncidents/AdminInScenarioIncidentBoxLayout.cpp \
    src/ui/admin/scenaries/includedIncidents/InScenarioIncidentWidget.cpp \
    src/ui/admin/scenaries/includedIncidents/InScenarioIncidentWidgetStorage.cpp \
    src/ui/user/EventCategoryWidget.cpp \
    src/ui/user/EventWidget.cpp \
    src/ui/user/IncidentMenuWidget.cpp \
    src/ui/user/IncidentWidget.cpp \
    src/ui/user/MainMenuWidget.cpp \
    src/ui/user/RecommendationsWidget.cpp \
    src/ui/user/ScenarioMenuWidget.cpp \
    src/ui/user/ScenarioWidget.cpp

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
