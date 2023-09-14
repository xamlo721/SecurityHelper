#include "IncidentWidget.h"
#include "ui_IncidentWidget.h"

IncidentWidget::IncidentWidget(quint32 id, QString text, QWidget *parent) :  QWidget(parent), ui(new Ui::IncidentWidget) {
    ui->setupUi(this);
    this->id = id;
    this->ui->textEdit_incident_description->append(text);
    this->ui->label_incident_title->setText("Предполагаемый инцидент №" +QString::number(id));
    QObject::connect(this->ui->pushButton_openScenario, &QPushButton::clicked, this, &IncidentWidget::onPuttonClicked);

}

void IncidentWidget::onPuttonClicked() {
    emit signalIncidentOpen(this->id);
}

IncidentWidget::~IncidentWidget() {
    delete ui;
}
