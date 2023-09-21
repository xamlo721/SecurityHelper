#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/ui/user/MainMenuWidget.h"
#include "src/ui/user/IncidentMenuWidget.h"
#include "src/ui/user/ScenarioMenuWidget.h"
#include "src/ui/user/RecommendationsWidget.h"

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

        //TODO: Странная проектировка, возможно переписать
        void openMainMenu();
        void openIncidentMenu();
        void openScenarioMenu();
        void openRecommendationMenu();

        void openUserToolbar();
        void openAdminToolbar();

        void setRemmendationWidget(RecommendationsWidget * widget);

    signals:
        void signalAdminButtonPressed();
        void signalResetButtonPressed();
        void signalIncidentsButtonPressed();
        void signalSettingsButtonPressed();
        void signalExitButtonPressed();
        void signalCategoryClicked(quint32 categoryID);

        void signalUndoButtonPressed();
        void signalRedoButtonPressed();
        void signalResetEditButtonPressed();
        void signalEditButtonPressed();
        void signalBackButtonPressed();

    private:
        Ui::MainWindow *ui;

    protected:
        virtual void resizeEvent(QResizeEvent *evt) override;

};
#endif // MAINWINDOW_H
