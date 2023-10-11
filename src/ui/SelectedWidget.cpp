#include "SelectedWidget.h"
#include "ui_SelectedWidget.h"

SelectedWidget::SelectedWidget(quint32 id, QString title, QWidget *parent) : QWidget(parent), ui(new Ui::SelectedWidget) {
    ui->setupUi(this);
    this->ui->pushButton->setMinimumSize(200, 60);
    this->id = id;
    this->text = title;
    this->ui->pushButton->setText(title);
    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, &SelectedWidget::onOpenIncidentButtonClicked);
}

SelectedWidget::SelectedWidget(quint32 id, QString title, bool isSelected , QWidget *parent): QWidget(parent), ui(new Ui::SelectedWidget)  {
    ui->setupUi(this);
    this->ui->pushButton->setMinimumSize(200, 60);
    this->id = id;
    this->text = title;
    this->ui->pushButton->setText(title);
    this->ui->pushButton->setDown(isSelected);
    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, &SelectedWidget::onOpenIncidentButtonClicked);

}

quint32 SelectedWidget::getId() {
    return this->id;
}

QString SelectedWidget::getText() {
    return this->text;
}

void SelectedWidget::setText(QString title) {
    this->ui->pushButton->setText(title);
}

void SelectedWidget::select() {
    this->ui->pushButton->setDown(true);
}

void SelectedWidget::unselect() {
    this->ui->pushButton->setDown(false);
}

void SelectedWidget::onOpenIncidentButtonClicked() {

    if (this->ui->pushButton->isDown()) {
        emit signalSelected(this->id);
    } else {
        emit signalUnselected(this->id);
    }

}

SelectedWidget::~SelectedWidget() {
    delete ui;
}
