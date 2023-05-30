#include "Scenario.h"
#include "ui_Scenario.h"

Scenario::Scenario(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Scenario)
{
    ui->setupUi(this);
}

Scenario::~Scenario()
{
    delete ui;
}
