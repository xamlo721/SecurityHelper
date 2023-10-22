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

void RecommendationsWidget::setTextContaiment(QString textContainment) {
    this->ui->textEdit_cont->setText(textContainment);

}

void RecommendationsWidget::setTextFixes(QString textFixes) {
    this->ui->textEdit_fixes->setText(textFixes);

}

void RecommendationsWidget::setTextRestore(QString textRestore) {
    this->ui->textEdit_restore->setText(textRestore);

}

void RecommendationsWidget::clear() {
    this->ui->textEdit_cont->setText("");
    this->ui->textEdit_fixes->setText("");
    this->ui->textEdit_restore->setText("");
}

RecommendationsWidget::~RecommendationsWidget() {
    delete ui;
}
