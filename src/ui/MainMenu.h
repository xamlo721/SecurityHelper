#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

#include "src/ui/IncidentCategoryWidget.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget {

    Q_OBJECT

    public:
        explicit MainMenu(QWidget *parent = nullptr);
        ~MainMenu();

        void clearCategories();

        void addCategory(IncidentCategoryWidget * category);

    private:
        Ui::MainMenu *ui;
};

#endif // MAINMENU_H
