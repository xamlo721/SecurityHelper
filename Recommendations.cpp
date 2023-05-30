#include "Recommendations.h"
#include "ui_Recommendations.h"

Recommendations::Recommendations(QWidget *parent) : QWidget(parent), ui(new Ui::Recommendations) {
    ui->setupUi(this);
}

Recommendations::~Recommendations() {
    delete ui;
}
