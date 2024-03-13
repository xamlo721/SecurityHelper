#include "AdminScenariesDialog.h"
#include "ui_AdminScenariesDialog.h"

AdminScenariesDialog::AdminScenariesDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AdminScenariesDialog) {
    ui->setupUi(this);


}

AdminScenariesDialog::~AdminScenariesDialog() {
    delete ui;
}
