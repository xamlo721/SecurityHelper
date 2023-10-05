#include "InCategoryEventWidget.h"
#include "ui_InCategoryEventWidget.h"

InCategoryEventWidget::InCategoryEventWidget(const quint32 id, const QString title, QWidget *parent) : QWidget(parent), ui(new Ui::InCategoryEventWidget) {
    ui->setupUi(this);
    /// Задаем минимальный размер кнопки
    this->ui->label_eventTitle->setMinimumSize(200, 60);
    /// Инициализируем поля класса
    this->id = id;
    this->title = title;

    this->ui->checkBox->setChecked(false);
    /// Устанавливаем текст на кнопке
    this->ui->label_eventTitle->setText(title);

    QObject::connect(this->ui->checkBox, &QCheckBox::clicked, this, &InCategoryEventWidget::onCheckBoxClicked);
}


InCategoryEventWidget::~InCategoryEventWidget() {
    delete ui;
}

void InCategoryEventWidget::onCheckBoxClicked() {
    switch (this->ui->checkBox->isChecked()) {
    case true:

        emit signalEventSelected(this->getID());
        break;

    case false:

        emit signalEventUnselected(this->getID());
        break;
    }
}

void InCategoryEventWidget::setTitle(const QString title) {
    this->title = title;
    this->ui->label_eventTitle->setText(this->title);
}

void InCategoryEventWidget::setUnselected() {
    /// Делаем checkBox не выбранным
    this->ui->checkBox->setChecked(false);
    /// Отправляем сигнал о том, что выбор checkBox отменяется
    emit this->ui->checkBox->clicked();
}
