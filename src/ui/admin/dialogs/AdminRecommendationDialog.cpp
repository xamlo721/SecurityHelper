#include "AdminRecommendationDialog.h"
#include "ui_AdminRecommendationDialog.h"

AdminRecommendationDialog::AdminRecommendationDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AdminRecommendationDialog) {
    ui->setupUi(this);


}

AdminRecommendationDialog::~AdminRecommendationDialog() {
    delete ui;
}

void AdminRecommendationDialog::setEditableText(QString name) {
    this->ui->lineEditName->setText(name);
}
