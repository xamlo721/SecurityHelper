#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/ui/EventCategoryWidget.h"
#include "src/ui/EventWidget.h"
#include "src/ui/IncidentWidget.h"
#include "src/ui/ScenarioWidget.h"
#include "src/ui/RecommendationsWidget.h"

#include "src/ui/EditableEventCategoryWidget.h"
#include "src/ui/EditableEventWidget.h"

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
        void addCategory(EventCategoryWidget * category);

        void clearCategoryEventList();
        void addCategoryEvent(EventWidget * event);

        void clearSelectedEventList();
        void addSelectedEvent(EventWidget * event);

        void clearIncidentList();
        void addIncidentWidget(IncidentWidget * widget);

        void clearScenarioList();
        void addScenarioWidget(ScenarioWidget * widget);

        void setRemmendationWidget(RecommendationsWidget * widget);

        void addEditableCategory(EditableEventCategoryWidget * editableCategory);
        void addEditableCategoryEvent(EditableEventWidget * editableEvent);

    signals:
        void signalAdminButtonPressed();
        void signalResetButtonPressed();
        void signalIncidentsButtonPressed();
        void signalSettingsButtonPressed();
        void signalExitButtonPressed();
        void signalCategoryClicked(quint32 categoryID);

    private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
