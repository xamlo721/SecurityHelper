#include "EventWidget.h"
#include "ui_EventWidget.h"

EventWidget::EventWidget(int id, QString text, bool isChecked, QWidget *parent) : QWidget(parent), ui(new Ui::EventWidget) {
    ui->setupUi(this);
    this->id = id;
    this->ui->checkBox->setChecked(isChecked);
    this->ui->label_event_title->setText(text);

    QObject::connect(this->ui->checkBox, &QCheckBox::clicked, this, &EventWidget::onCheckBoxClicked);
}

void EventWidget::onCheckBoxClicked() {
    emit signalEventSelected(this->id);
}

EventWidget::~EventWidget() {
    delete ui;
}
