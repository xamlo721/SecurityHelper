QT       += core gui

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
    src/items/IncidentCategory.cpp \
    src/ui/EventWidget.cpp \
    src/ui/Incident.cpp \
    src/ui/IncidentCategoryWidget.cpp \
    src/ui/MainMenu.cpp \
    src/ui/Recommendations.cpp \
    src/ui/Scenario.cpp \
    src/ui/MainWindow.cpp \
    src/ui/IncidentMenu.cpp \
    src/main.cpp \
    src/ui/ScenarioMenu.cpp

HEADERS += \
    src/controllers/MainWindowController.h \
    src/items/IncidentCategory.h \
    src/ui/EventWidget.h \
    src/ui/Incident.h \
    src/ui/IncidentCategoryWidget.h \
    src/ui/MainMenu.h \
    src/ui/MainWindow.h \
    src/ui/Recommendations.h \
    src/ui/Scenario.h \
    src/ui/IncidentMenu.h \
    src/ui/ScenarioMenu.h

FORMS += \
    src/ui/IncidentCategoryWidget.ui \
    ui/ScenarioMenu.ui \
    ui\IncidentMenu.ui \
    ui\EventWidget.ui \
    ui\Incident.ui \
    ui\MainMenu.ui \
    ui\MainWindow.ui \
    ui\Recommendations.ui \
    ui\Scenario.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
