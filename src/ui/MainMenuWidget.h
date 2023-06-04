#ifndef MAINMENU_WIDGET_H
#define MAINMENU_WIDGET_H

#include <QWidget>
#include <QList>
#include <QPushButton>

#include "src/ui/EventCategoryWidget.h"

namespace Ui {
    class MainMenuWidget;
}

class MainMenuWidget : public QWidget {

    Q_OBJECT

    public:
        explicit MainMenuWidget(QWidget *parent = nullptr);
        ~MainMenuWidget();

        void clearCategories();

        void addCategory(EventCategoryWidget * category);

    public slots:
        void onCategoryClicked(int categoryId);
    private:
        Ui::MainMenuWidget *ui;
        QList<QPushButton *> categoriesWidgetList;
};

#endif // MAINMENU_H
