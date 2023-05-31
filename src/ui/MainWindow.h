#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/ui/IncidentCategoryWidget.h"

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

        //TODO: Странная проектировка, возможно переписать
        void openMainMenu();
        void openIncidentMenu();
        void openScenarioMenu();
        void openRecommendationMenu();

        void clearCategoryList();
        void addCategory(IncidentCategoryWidget * category);

    signals:
        void signalAdminButtonPressed();
        void signalResetButtonPressed();
        void signalIncidentsButtonPressed();
        void signalSettingsButtonPressed();
        void signalExitButtonPressed();

    private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
