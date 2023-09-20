#include "RecommendationsWidget.h"
#include "ui_RecommendationsWidget.h"

RecommendationsWidget::RecommendationsWidget(QWidget *parent) : QWidget(parent), ui(new Ui::RecommendationsWidget) {
    ui->setupUi(this);
}

RecommendationsWidget::RecommendationsWidget(QString textContainment, QString textFixes, QString textRestore,QWidget *parent) : QWidget(parent), ui(new Ui::RecommendationsWidget) {
    ui->setupUi(this);
    this->ui->textEdit_cont->setText(textContainment);
    this->ui->textEdit_fixes->setText(textFixes);
    this->ui->textEdit_restore->setText(textRestore);
}

RecommendationsWidget::~RecommendationsWidget() {
    delete ui;
}
