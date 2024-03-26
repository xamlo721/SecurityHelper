#include "AdminEditCatorgyDialog.h"

#include <QPushButton>

#include "ui_AdminEditCatorgyDialog.h"

AdminEditCatorgyDialog::AdminEditCatorgyDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AdminEditCatorgyDialog) {
    ui->setupUi(this);

    QObject::connect(this->ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::clicked, this, &AdminEditCatorgyDialog::onSaveButtonPressed);

}

AdminEditCatorgyDialog::~AdminEditCatorgyDialog() {
    delete ui;
}

void AdminEditCatorgyDialog::setEditableText(QString name) {
    this->ui->lineEditName->setText(name);
}

void AdminEditCatorgyDialog::onSaveButtonPressed() {
    emit signalItemNameChanged(this->ui->lineEditName->text());
}
