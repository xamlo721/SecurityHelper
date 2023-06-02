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

SOURCES += \
    src/controllers/MainWindowController.cpp \
    src/items/SecurityEvent.cpp \
    src/items/SecurityEventCategory.cpp \
    src/items/SecurityIncident.cpp \
    src/items/SecurityRecommendations.cpp \
    src/items/SecurityScenario.cpp \
    src/logic/Database.cpp \
    src/logic/XmlHelper.cpp \
    src/logic/XmlUtils.cpp \
    src/ui/EventWidget.cpp \
    src/ui/IncidentCategoryWidget.cpp \
    src/ui/IncidentMenuWidget.cpp \
    src/ui/IncidentWidget.cpp \
    src/ui/MainMenuWidget.cpp \
    src/ui/MainWindow.cpp \
    src/main.cpp \
    src/ui/RecommendationsWidget.cpp \
    src/ui/ScenarioMenuWidget.cpp \
    src/ui/ScenarioWidget.cpp

HEADERS += \
    src/controllers/MainWindowController.h \
    src/items/SecurityEvent.h \
    src/items/SecurityEventCategory.h \
    src/items/SecurityIncident.h \
    src/items/SecurityRecommendations.h \
    src/items/SecurityScenario.h \
    src/logic/Database.h \
    src/logic/XmlHelper.h \
    src/logic/XmlUtils.h \
    src/ui/EventWidget.h \
    src/ui/IncidentCategoryWidget.h \
    src/ui/IncidentMenuWidget.h \
    src/ui/IncidentWidget.h \
    src/ui/MainMenuWidget.h \
    src/ui/MainWindow.h \
    src/ui/RecommendationsWidget.h \
    src/ui/ScenarioMenuWidget.h \
    src/ui/ScenarioWidget.h

FORMS += \
    ui/IncidentCategoryWidget.ui \
    ui/IncidentMenuWidget.ui \
    ui/MainMenuWidget.ui \
    ui/RecommendationsWidget.ui \
    ui/EventWidget.ui \
    ui/IncidentWidget.ui \
    ui/MainWindow.ui \
    ui/ScenarioMenuWidget.ui \
    ui/ScenarioWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    storage/Categories.xml \
    storage/Events.xml \
    storage/Incidents.xml \
    storage/Recommendations.xml \
    storage/Scenaries.xml
