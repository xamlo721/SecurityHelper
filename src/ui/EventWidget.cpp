#include "EventWidget.h"
#include "ui_EventWidget.h"

EventWidget::EventWidget(int id, QString text, QWidget *parent) : QWidget(parent), ui(new Ui::EventWidget) {
    ui->setupUi(this);
    this->id = id;
    this->ui->label_event_title->text();
}

EventWidget::~EventWidget() {
    delete ui;
}
