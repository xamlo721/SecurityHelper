#include "InIncidentEventWidget.h"
#include "ui_InIncidentEventWidget.h"

InIncidentEventWidget::InIncidentEventWidget(const quint32 id, const QString title, QWidget *parent) : QWidget(parent), ui(new Ui::InIncidentEventWidget) {
    ui->setupUi(this);

    this->ui->label_eventTitle->setMinimumSize(200, 60);

    this->id = id;
    this->title = title;

    this->ui->checkBox->setChecked(false);

    this->ui->label_eventTitle->setText(title);

    QObject::connect(this->ui->checkBox, &QCheckBox::clicked, this, &InIncidentEventWidget::onCheckBoxClicked);
}

InIncidentEventWidget::~InIncidentEventWidget() {
    delete ui;
}

void InIncidentEventWidget::onCheckBoxClicked() {
    switch (this->ui->checkBox->isChecked()) {
    case true:

        emit signalEventSelected(this->getID());
        break;

    case false:

        emit signalEventUnselected(this->getID());
        break;
    }
}

void InIncidentEventWidget::setTitle(const QString title) {
    this->title = title;
    this->ui->label_eventTitle->setText(this->title);
}

void InIncidentEventWidget::setUnselected() {
    this->ui->checkBox->setChecked(false);

    emit this->ui->checkBox->clicked();
}
