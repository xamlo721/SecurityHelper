#ifndef MAINMENU_WIDGET_H
#define MAINMENU_WIDGET_H

#include <QWidget>
#include <QList>
#include <QPushButton>

#include "src/ui/user/EventCategoryWidget.h"
#include "src/ui/user/EventWidget.h"

#include "src/ui/admin/EditableEventCategoryWidget.h"
#include "src/ui/admin/EditableEventWidget.h"

namespace Ui {
    class MainMenuWidget;
}

class MainMenuWidget : public QWidget {

    Q_OBJECT

    public:
        explicit MainMenuWidget(QWidget *parent = nullptr);
        ~MainMenuWidget();

        void clearCategories();
        void clearAvailableEvents();
        void clearSelectedEvents();

        void addCategory(EventCategoryWidget * category);
        void addEvent(EventWidget * event);
        void addSelectedEvent(EventWidget * event);

        void addCategoryToAdmin(EventCategoryWidget * category);
        void addEventToAdmin(EventWidget * event);

        void addEditableCategory(EditableEventCategoryWidget * editableCategory);
        void addEditableEvent(EditableEventWidget * editableEvent);

        void openUserMainMenu();
        void openAdminMainMenu();

    public slots:
        //void onCategoryClicked(int categoryId);

    signals:
        //void signalCategoryClicked(int categoryId);

        void signalAddCategoryButtonPressed();
        void signalDeleteCategoriesButtonPressed();

        void signalAddEventButtonPressed();
        void signalDeleteEventButtonPressed();

    private:
        Ui::MainMenuWidget *ui;
        QList<QPushButton *> categoriesWidgetList;
};

#endif // MAINMENU_H
