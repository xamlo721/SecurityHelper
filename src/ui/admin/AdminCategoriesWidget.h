#ifndef ADMINCATEGORIESWIDGET_H
#define ADMINCATEGORIESWIDGET_H

#include <QWidget>
#include "src/ui/SelectedWidget.h"

namespace Ui {
    class AdminCategoriesWidget;
}

class AdminCategoriesWidget : public QWidget {

    Q_OBJECT

    private:
        Ui::AdminCategoriesWidget *ui;

    public:
        explicit AdminCategoriesWidget(QWidget *parent = nullptr);
        ~AdminCategoriesWidget();

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

        /**
         * @brief enableEditButton - включить доступность кнопки
         * "Редактировать" на пакели событий
         */
        void enableEditButton();

        /**
         * @brief disableEditButton - выключить доступность кнопки
         * "Редактировать" на пакели событий
         */
        void disableEditButton();

        /**
         * @brief enableDeleteButton - включить доступность кнопки
         * "Удалить" на пакели событий
         */
        void enableDeleteButton();

        /**
         * @brief disableDeleteButton - выключить доступность кнопки
         * "Удалить" на пакели событий
         */
        void disableDeleteButton();

    signals:

        /**
         * @brief signalCategoryClicked - сигнал вызывается
         * при кажатии администратором на кнопку категории
         * @param categoryId - ID выбранной категории
         */
        void signalCategorySelected(quint32 categoryId);

        /**
         * @brief signalCategoryUnselected - сигнал вызывается
         * при кажатии администратором на кнопку категории
         * @param categoryId - ID выбранной категории
         */
        void signalCategoryUnselected(quint32 categoryId);

        /**
         * @brief signalAddCategoryClicked - сигнал вызывается
         * при кажатии администратором на кнопку добавления категории
         */
        void signalAddCategoryClicked();

        /**
         * @brief signalEditCategoryClicked - сигнал вызывается
         * при кажатии администратором на кнопку редактирования категории
         * @param categoryId - ID выбранной категории
         */
        void signalEditCategoryClicked(quint32 categoryId);

        /**
         * @brief signalEditCategoryClicked - сигнал вызывается
         * при кажатии администратором на кнопку редактирования категории
         * @param categoryId - ID выбранной категории
         * @param containedEvents - Новый набор входящих событий
         */
        void signalSaveCategoryClicked(quint32 categoryId, QString categoryName);

        /**
         * @brief signalDelCategoryClicked - сигнал вызывается
         * при кажатии администратором на кнопку удаления категории
         * @param categoryId - ID выбранной категории
         */
        void signalDelCategoryClicked(quint32 categoryId);

        /**
         * @brief signalUnselectedEventClicked - сигнал вызывается
         * при кажатии администратором на кнопку доступного события
         * @param eventID - ID события
         */
        void signaAvailableEventClicked(quint32 eventID);

        /**
         * @brief signalSelectedEventClicked - сигнал вызывается
         * при кажатии администратором на кнопку уже выбранного события
         * @param eventID - ID события
         */
        void signalSelectedEventClicked(quint32 eventID);


    private slots:
        void onAddCategoryButtonPressed();
        void onEditCategoryButtonPressed();
        void onDelCategoryButtonPressed();
        void onSaveCategoryButtonPressed();

};

#endif // ADMINCATEGORIESWIDGET_H
