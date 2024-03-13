#include "AdminIncidentDialog.h"
#include "ui_AdminIncidentDialog.h"

AdminIncidentDialog::AdminIncidentDialog(QWidget *parent)
    : QDialog(parent),  ui(new Ui::AdminIncidentDialog) {
    ui->setupUi(this);

}

AdminIncidentDialog::~AdminIncidentDialog() {
    delete ui;
}
