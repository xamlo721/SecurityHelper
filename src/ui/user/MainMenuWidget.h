#ifndef MAINMENU_WIDGET_H
#define MAINMENU_WIDGET_H

#include <QWidget>
#include <QList>
#include <QPushButton>

#include "src/ui/SelectedWidget.h"

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

        void addCategory(SelectedWidget * category);
        void addEvent(SelectedWidget * event);
        void addSelectedEvent(SelectedWidget * event);

        void openMainMenu();

    public slots:
        //void onCategoryClicked(int categoryId);

    signals:
        void signalCategoryClicked(int categoryId);

        void signalAddCategoryButtonPressed();
        void signalDeleteCategoriesButtonPressed();

        void signalAddEventButtonPressed();
        void signalDeleteEventButtonPressed();

    private:
        Ui::MainMenuWidget *ui;
        QList<QPushButton *> categoriesWidgetList;
};

#endif // MAINMENU_H
