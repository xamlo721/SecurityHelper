#ifndef ADMINSCENARIESWIDGET_H
#define ADMINSCENARIESWIDGET_H

#include <QWidget>
#include "src/ui/SelectedWidget.h"

namespace Ui {
class AdminScenariesWidget;
}

class AdminScenariesWidget : public QWidget {

    Q_OBJECT

    private:
        Ui::AdminScenariesWidget *ui;

    public:
        AdminScenariesWidget(QWidget *parent = nullptr);
        ~AdminScenariesWidget();

        /**
         * @brief clearScenaries - очищает визуальный список сценариев
         */
        void clearScenaries();

        /**
         * @brief clearAvailableIncidents - очищает визуальный список инцидентов
         */
        void clearAvailableIncidents();

        /**
         * @brief clearSelectedIncidents - очищает визуальный список выбранных инцидентов
         */
        void clearSelectedIncidents();

        /**
         * @brief addScenary - добавляет в отображаемый список сценарариев новый виджет
         * @param scenary - заранее сделанный виджет
         */
        void addScenary(SelectedWidget * scenary);

        /**
         * @brief addAvalilableIncident - добавляет в отображаемый список доступных для выделения инцидентов новый виджет
         * @param incident - заранее сделанный виджет
         */
        void addAvalilableIncident(SelectedWidget * incident);

        /**
         * @brief addSelectedIncident - добавляет в отображаемый список выбранных инцидентов новый виджет
         * @param incident - заранее сделанный виджет
         */
        void addSelectedIncident(SelectedWidget * incident);

        /**
         * @brief enableEditButton - включить доступность кнопки
         * "Редактировать" на пакели инцидентов
         */
        void enableEditButton();

        /**
         * @brief disableEditButton - выключить доступность кнопки
         * "Редактировать" на пакели инцидентов
         */
        void disableEditButton();

        /**
         * @brief enableDeleteButton - включить доступность кнопки
         * "Удалить" на пакели инцидентов
         */
        void enableDeleteButton();

        /**
         * @brief disableDeleteButton - выключить доступность кнопки
         * "Удалить" на пакели инцидентов
         */
        void disableDeleteButton();

    signals:

        /**
         * @brief signalScenaryClicked - сигнал вызывается при кажатии администратором на кнопку сценарариев
         * @param scenaryId - ID выбранной категории
         */
        void signalScenarySelected(quint32 scenaryId);

        /**
         * @brief signalScenaryUnselected - сигнал вызывается при кажатии администратором на кнопку сценарариев
         * @param scenaryId - ID выбранной категории
         */
        void signalScenaryUnselected(quint32 scenaryId);

        /**
         * @brief signalAddScenaryClicked - сигнал вызывается при кажатии администратором на кнопку добавления сценарариев
         */
        void signalAddScenaryClicked();

        /**
         * @brief signalEditScenaryClicked - сигнал вызывается при кажатии администратором на кнопку редактирования сценарариев
         * @param scenaryId - ID выбранного сценарария
         * @param containedEvents - Новый набор входящих инцидентов
         */
        void signaSaveScenaryClicked(quint32 scenaryId, QString scenaryName);

        /**
         * @brief signalEditScenaryClicked - сигнал вызывается при кажатии администратором на кнопку редактирования сценарариев
         * @param scenaryId - ID выбранного сценарария
         */
        void signaEditScenaryClicked(quint32 scenaryId);

        /**
         * @brief signalDelScenaryClicked - сигнал вызывается при кажатии администратором на кнопку удаления категории
         * @param scenaryId - ID выбранного сценарария
         */
        void signalDelScenaryClicked(quint32 scenaryId);

        /**
         * @brief signaAvailableIncidentClicked - сигнал вызывается при кажатии администратором на кнопку доступного инцидента
         * @param incidentID - ID выбранного инцидента
         */
        void signaAvailableIncidentClicked(quint32 incidentID);

        /**
         * @brief signalSelectedIncidentClicked - сигнал вызывается при кажатии администратором на кнопку уже выбранного инцидента
         * @param incidentID - ID выбранного инцидента
         */
        void signalSelectedIncidentClicked(quint32 incidentID);


    private slots:
        void onAddScenaryButtonPressed();
        void onEditScenaryButtonPressed();
        void onDelScenaryButtonPressed();
        void onSaveScenaryButtonPressed();
};

#endif // ADMINSCENARIESWIDGET_H
