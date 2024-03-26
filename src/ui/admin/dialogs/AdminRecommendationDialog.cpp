#include "AdminRecommendationDialog.h"
#include "ui_AdminRecommendationDialog.h"

#include <QPushButton>

AdminRecommendationDialog::AdminRecommendationDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AdminRecommendationDialog) {
    ui->setupUi(this);

    QObject::connect(this->ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::clicked, this, &AdminRecommendationDialog::onSaveButtonPressed);

}

AdminRecommendationDialog::~AdminRecommendationDialog() {
    delete ui;
}

void AdminRecommendationDialog::setEditableText(QString name) {
    this->ui->lineEditName->setText(name);
}

void AdminRecommendationDialog::onSaveButtonPressed() {
    emit signalItemNameChanged(this->ui->lineEditName->text());
}
