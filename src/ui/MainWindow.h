#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/ui/user/MainMenuWidget.h"
#include "src/ui/user/IncidentMenuWidget.h"
#include "src/ui/user/ScenarioMenuWidget.h"
#include "src/ui/user/RecommendationsWidget.h"

#include "src/ui/admin/AdminEditMenuWidget.h"
#include "src/ui/admin/AdminCategoriesWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        MainMenuWidget *getMainMenuWidget();
        IncidentMenuWidget *getIncidentMenuWidget();
        ScenarioMenuWidget *getScenarioMenuWidget();
        RecommendationsWidget *getRecommendationMenuWidget();
        AdminEditMenuWidget *getEditMenuWidget();

        AdminCategoriesWidget *getAdminCategoryWidget();
        AdminEventsWidget *getAdminEventsWidget();
        AdminIncidentsWidget *getAdminIncidentWidget();
        AdminScenariesWidget *getAdminScenariesWidget();
        AdminRecommendationWidget *getAdminRecommendationsWidget();

        //TODO: Странная проектировка, возможно переписать
        void openMainMenu();
        void openIncidentMenu();
        void openScenarioMenu();
        void openRecommendationMenu();

        void openAdminEditMenu();

    signals:
        void signalAdminButtonPressed();
        void signalResetButtonPressed();
        void signalIncidentsButtonPressed();
        void signalExitButtonPressed();
        void signalCategoryClicked(quint32 categoryID);
        void signalBackButtonPressed();

    private:
        Ui::MainWindow *ui;

    protected:
        virtual void resizeEvent(QResizeEvent *evt) override;

};
#endif // MAINWINDOW_H
