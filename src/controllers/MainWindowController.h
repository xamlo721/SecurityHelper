#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

#include "src/ui/EventWidget.h"
#include "src/ui/IncidentWidget.h"
#include "src/ui/ScenarioWidget.h"
#include "src/ui/MainWindow.h"

#include "src/ui/MainMenuWidget.h"
#include "src/ui/ScenarioMenuWidget.h"
#include "src/ui/IncidentMenuWidget.h"
#include "src/ui/RecommendationsWidget.h"

#include "src/ui/EventCategoryWidget.h"

#include "src/items/SecurityEventCategory.h"
#include "src/items/SecurityEvent.h"
#include "src/items/SecurityIncident.h"

class MainWindowController : public QObject {

    Q_OBJECT

    public:
        explicit MainWindowController(QObject *parent = nullptr);

        void init();

        void show();


        void shutdown();

        ~MainWindowController();

    public slots:
        void onAdminButtonPressed();
        void onResetButtonPressed();
        void onIncidentsButtonPressed();
        void onSettingsButtonPressed();
        void onExitButtonPressed();

        void setCategoryList(QList<SecurityEventCategory> categories);
        void setEventList(QList<SecurityEvent> events);
        void setIncidentList(QList<SecurityIncident> incidents);

    signals:
        void signalOpenCategory(int id);
        void signalCalculateIncident(QList<SecurityEvent> activeEvents);
        void signalOpenIncident(int id);

    private:
        MainWindow * w;
        QList<SecurityEventCategory> categories;
        QList<SecurityEvent> availableEvents;
        QList<SecurityEvent> activeEvents;

    private slots:
        void onEventSelected(int eventID);
        void onEventUnselected(int eventID);

    signals:

};

#endif // MAINWINDOWCONTROLLER_H
