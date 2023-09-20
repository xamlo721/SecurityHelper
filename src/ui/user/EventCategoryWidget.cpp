#include "EventCategoryWidget.h"
#include "ui_IncidentCategoryWidget.h"

EventCategoryWidget::EventCategoryWidget(quint32 id, QString title, QWidget *parent) : QWidget(parent), ui(new Ui::EventCategoryWidget) {
    ui->setupUi(this);
    this->ui->pushButton->setMinimumSize(200, 60);
    this->id = id;
    this->text = title;
    this->ui->pushButton->setText(title);
    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, &EventCategoryWidget::onOpenIncidentButtonClicked);
}

quint32 EventCategoryWidget::getId() {
    return this->id;
}

QString EventCategoryWidget::getText() {
    return this->text;
}

void EventCategoryWidget::onOpenIncidentButtonClicked() {
    emit signalOpenIncident(this->id);
}

EventCategoryWidget::~EventCategoryWidget() {
    delete ui;
}
