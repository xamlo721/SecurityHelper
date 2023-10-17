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

private:
    Ui::MainMenuWidget *ui;

    public:
        MainMenuWidget(QWidget *parent = nullptr);
        ~MainMenuWidget();

        /**
         * @brief clearCategories - очищает визуальный
         * список категорий событий
         */
        void clearCategories();

        /**
         * @brief clearAvailableEvents - очищает визуальный
         * список доступных событий
         */
        void clearAvailableEvents();

        /**
         * @brief clearSelectedEvents - очищает визуальный
         * список выбранных событий
         */
        void clearSelectedEvents();

        /**
         * @brief addCategory - добавляет в отображаемый
         * список категорий новый виджет категории
         * @param category - заранее сделанный виджет
         */
        void addCategory(SelectedWidget * category);

        /**
         * @brief addEvent - добавляет в отображаемый
         * список доступных для выделения событий
         * новый виджет
         * @param event - заранее сделанный виджет
         */
        void addAvalilableEvent(SelectedWidget * event);

        /**
         * @brief addSelectedEvent - добавляет в отображаемый
         * список выбранных событий новый виджет
         * @param event - заранее сделанный виджет
         */
        void addSelectedEvent(SelectedWidget * event);

    signals:

        /**
         * @brief signalCategoryClicked - сигнал вызывается
         * при кажатии пользователем на кнопку категории
         * @param categoryId - ID выбранной категории
         */
        void signalCategoryClicked(quint32 categoryId);

        /**
         * @brief signalUnselectedEventClicked - сигнал вызывается
         * при кажатии пользователем на кнопку доступного события
         * @param eventID - ID события
         */
        void signaAvailableEventClicked(quint32 eventID);

        /**
         * @brief signalSelectedEventClicked - сигнал вызывается
         * при кажатии пользователем на кнопку уже выбранного события
         * @param eventID - ID события
         */
        void signalSelectedEventClicked(quint32 eventID);

};

#endif // MAINMENU_H
