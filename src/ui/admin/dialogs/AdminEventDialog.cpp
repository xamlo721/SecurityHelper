#include "AdminEventDialog.h"

#include <QPushButton>

#include "ui_AdminEventDialog.h"

AdminEventDialog::AdminEventDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AdminEventDialog) {
    ui->setupUi(this);

    QObject::connect(this->ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::clicked, this, &AdminEventDialog::onSaveButtonPressed);
}

AdminEventDialog::~AdminEventDialog() {
    delete ui;
}

void AdminEventDialog::setEditableText(QString name) {
    this->ui->lineEditName->setText(name);
}

void AdminEventDialog::onSaveButtonPressed() {
    emit signalItemNameChanged(this->ui->lineEditName->text());
}
