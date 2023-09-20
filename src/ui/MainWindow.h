#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/ui/user/EventCategoryWidget.h"
#include "src/ui/user/EventWidget.h"
#include "src/ui/user/IncidentWidget.h"
#include "src/ui/user/ScenarioWidget.h"
#include "src/ui/user/RecommendationsWidget.h"

#include "src/ui/admin/EditableEventCategoryWidget.h"
#include "src/ui/admin/EditableEventWidget.h"

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
        void openUserMainMenu();
        void openIncidentMenu();
        void openScenarioMenu();
        void openRecommendationMenu();

        void openAdminMainMenu();

        void openUserToolbar();
        void openAdminToolbar();

        void clearCategoryList();
        void addCategory(EventCategoryWidget * category);

        void addCategoryToAdmin(EventCategoryWidget * category);

        void clearCategoryEventList();
        void addCategoryEvent(EventWidget * event);

        void addCategoryEventToAdmin(EventWidget * event);

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

        void signalUndoButtonPressed();
        void signalRedoButtonPressed();
        void signalResetEditButtonPressed();
        void signalEditButtonPressed();
        void signalBackButtonPressed();

        void signalAddCategoryButtonPressed();
        void signalDeleteCategoriesButtonPressed();

        void signalAddEventButtonPressed();
        void signalDeleteEventButtonPressed();

    private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
