#include "AdminEditCatorgyDialog.h"
#include "ui_AdminEditCatorgyDialog.h"

AdminEditCatorgyDialog::AdminEditCatorgyDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AdminEditCatorgyDialog) {
    ui->setupUi(this);

}

AdminEditCatorgyDialog::~AdminEditCatorgyDialog() {
    delete ui;
}
