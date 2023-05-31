#include "IncidentMenu.h"
#include "ui_IncidentMenu.h"

IncidentMenu::IncidentMenu(QWidget *parent) : QWidget(parent), ui(new Ui::IncidentMenu) {
    ui->setupUi(this);
}

IncidentMenu::~IncidentMenu() {
    delete ui;
}
