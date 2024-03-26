#include "AdminEventDialog.h"
#include "ui_AdminEventDialog.h"

AdminEventDialog::AdminEventDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AdminEventDialog) {
    ui->setupUi(this);

}

AdminEventDialog::~AdminEventDialog() {
    delete ui;
}

void AdminEventDialog::setEditableText(QString name) {
    this->ui->lineEditName->setText(name);
}
