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
#include "src/items/SecurityScenario.h"
#include "src/items/SecurityRecommendations.h"

#include "src/ui/EditableEventCategoryWidget.h"
#include "src/ui/EditableEventWidget.h"

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

        void onUndoButtonPressed();
        void onRedoButtonPressed();
        void onResetEditButtonPressed();
        void onEditButtonPressed();
        void onBackButtonPressed();

        void onAddCategoryButtonPressed();
        void onDeleteCategoriesButtonPressed();

        void onAddEventButtonPressed();
        void onDeleteEventsButtonPressed();

        void setCategoryList(QList<SecurityEventCategory> categories);
        void setEventList(QList<SecurityEvent> events);
        void setIncidentList(QList<SecurityIncident> incidents);
        void setScenariesList(QList<SecurityScenario> scenaries);
        void setRecommendationsList(QList<SecurityRecommendations> scenaries);

        void setAdminCategoryList(QList<SecurityEventCategory> categories);
        void setAdminEventList(QList<SecurityEvent> events);

    signals:
        void signalOpenCategory(quint32 id);
        void signalCalculateIncident(QList<SecurityEvent> activeEvents);
        void signalOpenIncident(quint32 id);
        void signalOpenScenario(quint32 id);

    private:
        MainWindow * w;
        QList<SecurityEventCategory> categories;
        QList<SecurityEvent> availableEvents;
        QList<SecurityEvent> activeEvents;

    private slots:
        void onEventSelected(quint32 eventID);
        void onEventUnselected(quint32 eventID);
        void onClarifyEvents();

    signals:

};

#endif // MAINWINDOWCONTROLLER_H
