#include "AdminScenariesDialog.h"

#include <QPushButton>

#include "ui_AdminScenariesDialog.h"

AdminScenariesDialog::AdminScenariesDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AdminScenariesDialog) {
    ui->setupUi(this);


    QObject::connect(this->ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::clicked, this, &AdminScenariesDialog::onSaveButtonPressed);

}

AdminScenariesDialog::~AdminScenariesDialog() {
    delete ui;
}

void AdminScenariesDialog::setEditableText(QString name) {
    this->ui->lineEdit->setText(name);
}

void AdminScenariesDialog::onSaveButtonPressed() {
    emit signalItemNameChanged(this->ui->lineEdit->text());
}
