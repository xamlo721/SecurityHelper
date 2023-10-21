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
    QObject::connect(recomendation, &SelectedWidget::signalSelected, this, &AdminRecommendationWidget::signalRecomendationClicked);
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
    //TODO: открыть окно редактирования

}

void AdminRecommendationWidget::onDelRecomendationButtonPressed() {
    emit signalDelRecomendationClicked(this->ui->scrollArea_recommendations->getSelectedWidgetID());

}

void AdminRecommendationWidget::onSaveRecomendationButtonPressed() {
    SelectedWidget * selected =  this->ui->scrollArea_recommendations->getSelectedWidget();
    emit signalEditRecomendationClicked(selected->getId(), selected->getText(), this->ui->textEdit->toPlainText(), this->ui->textEdit_2->toPlainText(), this->ui->textEdit_4->toPlainText());

}

AdminRecommendationWidget::~AdminRecommendationWidget() {
    delete ui;
}
