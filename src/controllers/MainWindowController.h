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

#include "src/ui/IncidentCategoryWidget.h"
#include "src/items/SecurityEventCategory.h"

class MainWindowController : public QObject {

    Q_OBJECT

    public:
        explicit MainWindowController(QObject *parent = nullptr);

        void init();

        void show();

        void setCategoryList(QList<SecurityEventCategory> categories);

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
        QList<SecurityEventCategory> categories;

    signals:

};

#endif // MAINWINDOWCONTROLLER_H
