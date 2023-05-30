#include "Incident.h"
#include "ui_Incident.h"

Incident::Incident(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Incident)
{
    ui->setupUi(this);
}

Incident::~Incident()
{
    delete ui;
}
