#include "ScenarioMenu.h"
#include "ui_ScenarioMenu.h"

ScenarioMenu::ScenarioMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScenarioMenu)
{
    ui->setupUi(this);
}

ScenarioMenu::~ScenarioMenu()
{
    delete ui;
}
