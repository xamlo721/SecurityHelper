#include "UserRecommendationController.h"

UserRecommendationController::UserRecommendationController(QObject *parent) : QObject(parent) {

}

void UserRecommendationController::init(RecommendationsWidget * recommendationWidget) {
    ui = recommendationWidget;
}


void UserRecommendationController::setRecommendation(SecurityRecommendations recommendation) {
    this->ui->setTextContaiment(recommendation.getTextContainment());
    this->ui->setTextFixes(recommendation.getTextFixes());
    this->ui->setTextRestore(recommendation.getTextRestore());
}
