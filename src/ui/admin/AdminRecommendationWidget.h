#ifndef ADMINRECOMMENDATIONWIDGET_H
#define ADMINRECOMMENDATIONWIDGET_H

#include <QWidget>
#include "src/ui/SelectedWidget.h"


namespace Ui {
    class AdminRecommendationWidget;
}

class AdminRecommendationWidget : public QWidget {

    Q_OBJECT

    public:
        AdminRecommendationWidget(QWidget *parent = nullptr);
        ~AdminRecommendationWidget();



        /**
         * @brief clearRecomendations - очищает на экране список рекомендаций
         */
        void clearRecomendations();


        /**
         * @brief clearAvailableScenarys - очищает на экране список доступных событий
         */
        void clearAvailableScenaries();

        /**
         * @brief clearSelectedScenarys - очищает на экране список выбранных событий
         */
        void clearSelectedScenaries();

        /**
         * @brief addRecomendation - добавляет в отображаемый
         * список рекомендаций новый виджет
         * @param recomendation - заранее сделанный виджет
         */
        void addRecomendation(SelectedWidget * recomendation);

        /**
         * @brief addScenary - добавляет в отображаемый
         * список доступных для выделения событий новый виджет
         * @param event - заранее сделанный виджет
         */
        void addAvalilableScenary(SelectedWidget * event);


        /**
         * @brief addSelectedScenary - добавляет в отображаемый
         * список выбранных событий новый виджет
         * @param event - заранее сделанный виджет
         */
        void addSelectedScenary(SelectedWidget * event);

        /**
         * @brief setRecommendationText - задаёт отображаемый текст рекомендаций по категориям
         * @param TextContainment - Текст для сдерживания
         * @param TextFixes - Текст для устранения
         * @param TextRestore - Текст для восстановления
         */
        void setRecommendationText(QString TextContainment, QString TextFixes, QString TextRestore);


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
         * @brief enableSaveButton - включить доступность кнопки
         * "Сохранить" на пакели событий
         */
        void enableSaveButton();

        /**
         * @brief disableSaveButton - выключить доступность кнопки
         * "Сохранить" на пакели событий
         */
        void disableSaveButton();

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
         * @brief signalRecomendationClicked - сигнал вызывается
         * при кажатии администратором на кнопку рекомендации
         * @param incidentId - ID выбранного инцидента
         */
        void signalRecomendationSelected(quint32 incidentId);

        /**
         * @brief signalRecomendationUnselected - сигнал вызывается
         * при кажатии администратором на кнопку рекомендации
         * @param incidentId - ID выбранного инцидента
         */
        void signalRecomendationUnselected(quint32 incidentId);

        /**
         * @brief signalAddRecomendationClicked - сигнал вызывается
         * при кажатии администратором на кнопку добавления рекомендаций
         */
        void signalAddRecomendationClicked();

        /**
         * @brief signalEditRecomendationClicked - сигнал вызывается
         * при кажатии администратором на кнопку редактирования рекомендаций
         * @param recomendationId - ID выбранной рекомендации
         * @param recomendationName - Название рекомендации
         * @param TextContainment - Текст для сдерживания
         * @param TextFixes - Текст для устранения
         * @param TextRestore - Текст для восстановления
         */
        void signalSaveRecomendationClicked(quint32 recomendationId, QString recomendationName, QString TextContainment, QString TextFixes, QString TextRestore);
        /**
         * @brief signalEditRecomendationClicked - сигнал вызывается
         * при кажатии администратором на кнопку удаления инцидента
         * @param recomendationId - ID выбранной рекомендации
         */
        void signalEditRecomendationClicked(quint32 recomendationId);

        /**
         * @brief signalDelRecomendationClicked - сигнал вызывается
         * при кажатии администратором на кнопку удаления инцидента
         * @param recomendationId - ID выбранной рекомендации
         */
        void signalDelRecomendationClicked(quint32 recomendationId);

        /**
         * @brief signalUnselectedScenaryClicked - сигнал вызывается
         * при кажатии администратором на кнопку доступного события
         * @param scenaryID - ID сценария
         */
        void signaAvailableScenaryClicked(quint32 scenaryID);

        /**
         * @brief signalSelectedScenaryClicked - сигнал вызывается
         * при кажатии администратором на кнопку уже выбранного события
         * @param scenaryID - ID события
         */
        void signalSelectedScenaryClicked(quint32 scenaryID);

    private slots:
        void onAddRecomendationButtonPressed();
        void onEditRecomendationButtonPressed();
        void onDelRecomendationButtonPressed();
        void onSaveRecomendationButtonPressed();


    private:
        Ui::AdminRecommendationWidget *ui;
};

#endif // ADMINRECOMMENDATIONWIDGET_H
