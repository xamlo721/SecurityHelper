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
        explicit AdminEventsWidget(QWidget *parent = nullptr);
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
        void signalEventClicked(quint32 eventID);

    private slots:
        void onAddEventButtonPressed();
        void onEditEventButtonPressed();
        void onDelEventButtonPressed();

};

#endif // ADMINEVENTSWIDGET_H
