#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

#include "src/ui/EventWidget.h"
#include "src/ui/Incident.h"
#include "src/ui/Scenario.h"
#include "src/ui/MainWindow.h"

#include "src/ui/MainMenu.h"
#include "src/ui/ScenarioMenu.h"
#include "src/ui/IncidentMenu.h"
#include "src/ui/Recommendations.h"

#include "src/ui/IncidentCategoryWidget.h"
#include "src/items/IncidentCategory.h"

class MainWindowController : public QObject {

    Q_OBJECT

    public:
        explicit MainWindowController(QObject *parent = nullptr);

        void init();

        void show();

        void setCategoryList(QList<IncidentCategory> categories);

        void shutdown();

        ~MainWindowController();

    public slots:
        void onAdminButtonPressed();
        void onResetButtonPressed();
        void onIncidentsButtonPressed();
        void onSettingsButtonPressed();
        void onExitButtonPressed();

    private:
        MainWindow * w;
        QList<IncidentCategory> categories;

    signals:

};

#endif // MAINWINDOWCONTROLLER_H
