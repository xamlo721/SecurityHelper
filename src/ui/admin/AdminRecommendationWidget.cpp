#include "AdminRecommendationWidget.h"
#include "ui_AdminRecommendationWidget.h"

AdminRecommendationWidget::AdminRecommendationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminRecommendationWidget)
{
    ui->setupUi(this);
}

AdminRecommendationWidget::~AdminRecommendationWidget()
{
    delete ui;
}
