#ifndef MAINMENU_WIDGET_H
#define MAINMENU_WIDGET_H

#include <QWidget>

#include "src/ui/IncidentCategoryWidget.h"

namespace Ui {
    class MainMenuWidget;
}

class MainMenuWidget : public QWidget {

    Q_OBJECT

    public:
        explicit MainMenuWidget(QWidget *parent = nullptr);
        ~MainMenuWidget();

        void clearCategories();

        void addCategory(IncidentCategoryWidget * category);

    private:
        Ui::MainMenuWidget *ui;
};

#endif // MAINMENU_H
