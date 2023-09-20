#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

#include "src/ui/user/EventWidget.h"
#include "src/ui/user/IncidentWidget.h"
#include "src/ui/user/ScenarioWidget.h"
#include "src/ui/MainWindow.h"

#include "src/ui/user/MainMenuWidget.h"
#include "src/ui/user/ScenarioMenuWidget.h"
#include "src/ui/user/IncidentMenuWidget.h"
#include "src/ui/user/RecommendationsWidget.h"

#include "src/ui/user/EventCategoryWidget.h"

#include "src/items/SecurityIncident.h"
#include "src/items/SecurityScenario.h"
#include "src/items/SecurityRecommendations.h"

class MainWindowController : public QObject {

    Q_OBJECT

    public:
        explicit MainWindowController(QObject *parent = nullptr);

        void init(MainWindow *mainWindow);

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

        void setIncidentList(QList<SecurityIncident> incidents);
        void setScenariesList(QList<SecurityScenario> scenaries);
        void setRecommendationsList(QList<SecurityRecommendations> scenaries);

    signals:
        void signalCalculateIncident();
        void signalOpenIncident(quint32 id);
        void signalOpenScenario(quint32 id);

        void signalResetButtonPressed();

    private:
        MainWindow * w;

    private slots:
        void onClarifyEvents();

};

#endif // MAINWINDOWCONTROLLER_H
