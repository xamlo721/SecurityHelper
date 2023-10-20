#ifndef ADMININCIDENTSWIDGET_H
#define ADMININCIDENTSWIDGET_H

#include <QWidget>
#include "src/ui/SelectedWidget.h"

namespace Ui {
    class AdminIncidentsWidget;
}

class AdminIncidentsWidget : public QWidget {

    Q_OBJECT

    private:
        Ui::AdminIncidentsWidget *ui;

    public:
        AdminIncidentsWidget(QWidget *parent = nullptr);
        ~AdminIncidentsWidget();

        /**
         * @brief clearIncidents - очищает на экране список инцидентов
         */
        void clearIncidents();

        /**
         * @brief clearAvailableEvents - очищает на экране список доступных событий
         */
        void clearAvailableEvents();

        /**
         * @brief clearSelectedEvents - очищает на экране список выбранных событий
         */
        void clearSelectedEvents();

        /**
         * @brief addIncident - добавляет в отображаемый
         * список инцидентов новый виджет инцедента
         * @param incident - заранее сделанный виджет
         */
        void addIncident(SelectedWidget * incident);

        /**
         * @brief addEvent - добавляет в отображаемый
         * список доступных для выделения событий новый виджет
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
         * @brief signalIncidentClicked - сигнал вызывается
         * при кажатии администратором на кнопку инцидента
         * @param incidentId - ID выбранного инцидента
         */
        void signalIncidentClicked(quint32 incidentId);

        /**
         * @brief signalAddCategoryClicked - сигнал вызывается
         * при кажатии администратором на кнопку добавления категории
         */
        void signalAddCategoryClicked();

        /**
         * @brief signalEditCategoryClicked - сигнал вызывается
         * при кажатии администратором на кнопку редактирования категории
         * @param categoryId - ID выбранной категории
         * @param containedEvents - Новый набор входящих событий
         */
        void signalEditIncidentClicked(quint32 incidentId, QString categoryName);

        /**
         * @brief signalDelIncidentClicked - сигнал вызывается
         * при кажатии администратором на кнопку удаления инцидента
         * @param incidentId - ID выбранного инцидента
         */
        void signalDelIncidentClicked(quint32 incidentId);

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
        void onAddIncidentButtonPressed();
        void onEditIncidentButtonPressed();
        void onDelIncidentButtonPressed();
        void onSaveIncidentButtonPressed();


};

#endif // ADMININCIDENTSWIDGET_H
