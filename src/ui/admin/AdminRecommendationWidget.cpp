#include "AdminRecommendationWidget.h"
#include "ui_AdminRecommendationWidget.h"

AdminRecommendationWidget::AdminRecommendationWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AdminRecommendationWidget) {
    ui->setupUi(this);
    QObject::connect(this->ui->pushButton_addRecommendation, &QPushButton::clicked, this, &AdminRecommendationWidget::onAddRecomendationButtonPressed);
    QObject::connect(this->ui->pushButton_editRecommendation, &QPushButton::clicked, this, &AdminRecommendationWidget::onEditRecomendationButtonPressed);
    QObject::connect(this->ui->pushButton_deleteRecommendation, &QPushButton::clicked, this, &AdminRecommendationWidget::onDelRecomendationButtonPressed);

    QObject::connect(this->ui->pushButton_saveRecommendation, &QPushButton::clicked, this, &AdminRecommendationWidget::onSaveRecomendationButtonPressed);

}

void AdminRecommendationWidget::clearRecomendations() {
    this->ui->scrollArea_recommendations->clear();
}

void AdminRecommendationWidget::clearAvailableScenaries() {
    this->ui->scrollArea_free_scenaries->clear();

}

void AdminRecommendationWidget::clearSelectedScenaries(){
    this->ui->scrollArea_included_scenaries->clear();

}


void AdminRecommendationWidget::addRecomendation(SelectedWidget * recomendation){
    QObject::connect(recomendation, &SelectedWidget::signalSelected, this, &AdminRecommendationWidget::signalRecomendationSelected);
    QObject::connect(recomendation, &SelectedWidget::signalUnselected, this, &AdminRecommendationWidget::signalRecomendationUnselected);
    this->ui->scrollArea_recommendations->addWidget(recomendation->getId(), recomendation);

}

void AdminRecommendationWidget::addAvalilableScenary(SelectedWidget * scenary){
    QObject::connect(scenary, &SelectedWidget::signalSelected, this, &AdminRecommendationWidget::signaAvailableScenaryClicked);
    this->ui->scrollArea_free_scenaries->addWidget(scenary->getId(), scenary);
}


void AdminRecommendationWidget::addSelectedScenary(SelectedWidget * scenary){
    QObject::connect(scenary, &SelectedWidget::signalSelected, this, &AdminRecommendationWidget::signalSelectedScenaryClicked);
    this->ui->scrollArea_included_scenaries->addWidget(scenary->getId(), scenary);
}

void AdminRecommendationWidget::setRecommendationText(QString TextContainment, QString TextFixes, QString TextRestore) {
    this->ui->textEdit->setText(TextContainment);
    this->ui->textEdit_2->setText(TextFixes);
    this->ui->textEdit_4->setText(TextRestore);
}

void AdminRecommendationWidget::onAddRecomendationButtonPressed() {
    this->ui->scrollArea_recommendations->unselect();
    emit signalAddRecomendationClicked();
}

void AdminRecommendationWidget::onEditRecomendationButtonPressed() {
    //TODO: Оставить возможность редактировать только если выбраная рекомендация
    emit signalEditRecomendationClicked(this->ui->scrollArea_recommendations->getSelectedWidgetID());

}

void AdminRecommendationWidget::onDelRecomendationButtonPressed() {
    emit signalDelRecomendationClicked(this->ui->scrollArea_recommendations->getSelectedWidgetID());

}

void AdminRecommendationWidget::onSaveRecomendationButtonPressed() {
    SelectedWidget * selected =  this->ui->scrollArea_recommendations->getSelectedWidget();
    emit signalSaveRecomendationClicked(selected->getId(), selected->getText(), this->ui->textEdit->toPlainText(), this->ui->textEdit_2->toPlainText(), this->ui->textEdit_4->toPlainText());

}

/**
 * @brief enableEditButton - включить доступность кнопки
 * "Редактировать" на пакели событий
 */
void AdminRecommendationWidget::enableEditButton() {
    this->ui->pushButton_editRecommendation->setEnabled(true);
}

/**
 * @brief disableEditButton - выключить доступность кнопки
 * "Редактировать" на пакели событий
 */
void AdminRecommendationWidget::disableEditButton() {
    this->ui->pushButton_editRecommendation->setEnabled(false);
}

/**
 * @brief enableSaveButton - включить доступность кнопки
 * "Сохранить" на пакели событий
 */
void AdminRecommendationWidget::enableSaveButton() {
    this->ui->pushButton_saveRecommendation->setEnabled(true);
}

/**
 * @brief disableSaveButton - выключить доступность кнопки
 * "Сохранить" на пакели событий
 */
void AdminRecommendationWidget::disableSaveButton() {
    this->ui->pushButton_saveRecommendation->setEnabled(false);
}

/**
 * @brief enableDeleteButton - включить доступность кнопки
 * "Удалить" на пакели событий
 */
void AdminRecommendationWidget::enableDeleteButton() {
    this->ui->pushButton_deleteRecommendation->setEnabled(true);
}

/**
 * @brief disableDeleteButton - выключить доступность кнопки
 * "Удалить" на пакели событий
 */
void AdminRecommendationWidget::disableDeleteButton() {
    this->ui->pushButton_deleteRecommendation->setEnabled(false);
}

AdminRecommendationWidget::~AdminRecommendationWidget() {
    delete ui;
}
