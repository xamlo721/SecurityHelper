#include "RecommendationsWidget.h"
#include "ui_RecommendationsWidget.h"

RecommendationsWidget::RecommendationsWidget(QWidget *parent) : QWidget(parent), ui(new Ui::RecommendationsWidget) {
    ui->setupUi(this);
}

RecommendationsWidget::~RecommendationsWidget() {
    delete ui;
}
