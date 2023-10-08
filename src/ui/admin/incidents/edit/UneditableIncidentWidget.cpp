#include "UneditableIncidentWidget.h"
#include "ui_UneditableIncidentWidget.h"

UneditableIncidentWidget::UneditableIncidentWidget(const quint32 id, const QString title, QWidget *parent) : QWidget(parent), ui(new Ui::UneditableIncidentWidget) {
    ui->setupUi(this);
    /// Задаем минимальный размер кнопки
    this->ui->pushButton_incident->setMinimumSize(200, 60);
    /// Инициализируем поля класса
    this->id = id;
    this->title = title;

    this->ui->checkBox->setChecked(false);
    /// Устанавливаем текст на кнопке
    this->ui->pushButton_incident->setText(title);

    QObject::connect(this->ui->checkBox, &QCheckBox::clicked, this, &UneditableIncidentWidget::onCheckBoxClicked);
}

UneditableIncidentWidget::~UneditableIncidentWidget() {
    delete ui;

    delete customMenu;
}

void UneditableIncidentWidget::onCheckBoxClicked() {
    switch (this->ui->checkBox->isChecked()) {
    case true:

        emit signalIncidentSelected(this->getID());
        break;

    case false:

        emit signalIncidentUnselected(this->getID());
        break;
    }
}

void UneditableIncidentWidget::initMenu() {
    customMenu = new UneditableItemMenu();

    /// Установка и инициализация меню
    customMenu->setup();
    customMenu->init();

    QObject::connect(this->customMenu, &UneditableItemMenu::signalEditCategory, this, &UneditableIncidentWidget::slotEditIncident);
    QObject::connect(this->customMenu, &UneditableItemMenu::signalDeleteCategory, this, &UneditableIncidentWidget::slotDeleteIncident);

    QObject::connect(this->ui->pushButton_incident, &QPushButton::clicked, this, &UneditableIncidentWidget::slotEditIncident);
    QObject::connect(this->ui->pushButton_incident, &QPushButton::customContextMenuRequested, this, &UneditableIncidentWidget::callCustomMenu);

    /// Установка политики меню, позволяющая показывать кастомное контекстное меню и использовать сигнал &QPushButton::customContextMenuRequested
    this->ui->pushButton_incident->setContextMenuPolicy(Qt::CustomContextMenu);
}


void UneditableIncidentWidget::callCustomMenu(const QPoint mousePosition) {
    /// Вызов кастомного контекстного меню по позиции курсора
    customMenu->call(this->ui->pushButton_incident->mapToGlobal(mousePosition));
}

void UneditableIncidentWidget::setTitle(const QString title) {
    this->title = title;
    this->ui->pushButton_incident->setText(this->title);
}

void UneditableIncidentWidget::setUnselected() {
    /// Делаем checkBox не выбранным
    this->ui->checkBox->setChecked(false);
    /// Отправляем сигнал о том, что выбор checkBox отменяется ( см. UneditableEventWidget::onCheckBoxClicked() )
    emit this->ui->checkBox->clicked();
}

void UneditableIncidentWidget::slotEditIncident() {
    emit signalEditIncident(this);
}

void UneditableIncidentWidget::slotDeleteIncident() {
    emit signalDeleteIncident(this);
}
