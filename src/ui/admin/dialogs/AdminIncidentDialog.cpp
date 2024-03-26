#include "AdminIncidentDialog.h"
#include "ui_AdminIncidentDialog.h"

#include <QPushButton>

AdminIncidentDialog::AdminIncidentDialog(QWidget *parent)
    : QDialog(parent),  ui(new Ui::AdminIncidentDialog) {
    ui->setupUi(this);

    QObject::connect(this->ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::clicked, this, &AdminIncidentDialog::onSaveButtonPressed);

}

AdminIncidentDialog::~AdminIncidentDialog() {
    delete ui;
}

void AdminIncidentDialog::setEditableText(QString name) {
    this->ui->lineEditName->setText(name);
}

void AdminIncidentDialog::onSaveButtonPressed() {
    emit signalItemNameChanged(this->ui->lineEditName->text());
}
