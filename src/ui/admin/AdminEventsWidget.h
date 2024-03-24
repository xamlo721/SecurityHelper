#ifndef ADMINEVENTSWIDGET_H
#define ADMINEVENTSWIDGET_H

#include <QWidget>
#include "src/ui/SelectedWidget.h"

namespace Ui {
    class AdminEventsWidget;
}

class AdminEventsWidget : public QWidget {

    Q_OBJECT


    private:
        Ui::AdminEventsWidget *ui;

    public:
        AdminEventsWidget(QWidget *parent = nullptr);
        ~AdminEventsWidget();

        /**
         * @brief clearEvents - очищает визуальный список событий
         */
        void clearEvents();


        /**
         * @brief addEvent - добавляет в отображаемый список событий новый виджет
         * @param event - заранее сделанный виджет
         */
        void addEvent(SelectedWidget * event);

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
         * @brief signalAddEventClicked - сигнал вызывается
         * при кажатии администратором на кнопку добавления события
         */
        void signalAddEventClicked();

        /**
         * @brief signalEditEventClicked - сигнал вызывается
         * при кажатии администратором на кнопку редактирования события
         * @param eventID - ID выбранного события
         * @param containedEvents - Новый набор входящих событий
         */
        void signalSaveEventClicked(quint32 eventID, QString categoryName);

        /**
         * @brief signalEditEventClicked - сигнал вызывается
         * при кажатии администратором на кнопку редактирования события
         * @param eventID - ID выбранного события
         */
        void signalEditEventClicked(quint32 eventID);

        /**
         * @brief signalDelEventClicked - сигнал вызывается
         * при кажатии администратором на кнопку удаления события
         * @param eventID - ID выбранного события
         */
        void signalDelEventClicked(quint32 eventID);

        /**
         * @brief signaEventClicked - сигнал вызывается
         * при кажатии администратором на событие
         * @param eventID - ID события
         */
        void signalEventSelected(quint32 eventID);

        /**
         * @brief signalEventUnselected - сигнал вызывается
         * при кажатии администратором на событие
         * @param eventID - ID события
         */
        void signalEventUnselected(quint32 eventID);

    private slots:


        /**
         * @brief onAddEventButtonPressed - слот, активируемый при нажатии
         * накнопку "Добавить" в списке событий
         */
        void onAddEventButtonPressed();

        /**
         * @brief onEditEventButtonPressed - слот, активируемый при нажатии
         * на кнопку "Редактировать" в списке событий
         */
        void onEditEventButtonPressed();

        /**
         * @brief onDelEventButtonPressed - слот, активируемый при нажатии
         * на кнопку "Удалить" в списке событий
         */
        void onDelEventButtonPressed();

};

#endif // ADMINEVENTSWIDGET_H
