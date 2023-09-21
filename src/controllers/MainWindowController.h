#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

#include "src/ui/MainWindow.h"

#include "src/ui/user/RecommendationsWidget.h"

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

        void onOpenScenarioMenu();
        void onOpenRecommendationMenu();
        void setRecommendationWidget(RecommendationsWidget * widget);

        void onClarifyEvents();

    signals:
        void signalCalculateIncident();

        void signalResetButtonPressed();

    private:
        MainWindow * w;

    private slots:

};

#endif // MAINWINDOWCONTROLLER_H
