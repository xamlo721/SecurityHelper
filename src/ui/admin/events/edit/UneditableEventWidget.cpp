#include "UneditableEventWidget.h"
#include "ui_UneditableEventWidget.h"

UneditableEventWidget::UneditableEventWidget(const quint32 id, const QString title, QWidget *parent) : QWidget(parent), ui(new Ui::UneditableEventWidget) {
    ui->setupUi(this);
    /// Задаем минимальный размер кнопки
    this->ui->pushButton_event->setMinimumSize(200, 60);
    /// Инициализируем поля класса
    this->id = id;
    this->title = title;

    this->ui->checkBox->setChecked(false);
    /// Устанавливаем текст на кнопке
    this->ui->pushButton_event->setText(title);

    QObject::connect(this->ui->checkBox, &QCheckBox::clicked, this, &UneditableEventWidget::onCheckBoxClicked);
}

UneditableEventWidget::~UneditableEventWidget() {
    delete ui;

    delete customMenu;
}

void UneditableEventWidget::onCheckBoxClicked() {
    switch (this->ui->checkBox->isChecked()) {
    case true:

        emit signalEventSelected(this->getID());
        break;

    case false:

        emit signalEventUnselected(this->getID());
        break;
    }
}

void UneditableEventWidget::initMenu() {
    customMenu = new UneditableItemMenu();

    /// Установка и инициализация меню
    customMenu->setup();
    customMenu->init();

    QObject::connect(this->customMenu, &UneditableItemMenu::signalEditCategory, this, &UneditableEventWidget::slotEditEvent);
    QObject::connect(this->customMenu, &UneditableItemMenu::signalDeleteCategory, this, &UneditableEventWidget::slotDeleteEvent);

    QObject::connect(this->ui->pushButton_event, &QPushButton::clicked, this, &UneditableEventWidget::slotEditEvent);
    QObject::connect(this->ui->pushButton_event, &QPushButton::customContextMenuRequested, this, &UneditableEventWidget::callCustomMenu);

    /// Установка политики меню, позволяющая показывать кастомное контекстное меню и использовать сигнал &QPushButton::customContextMenuRequested
    this->ui->pushButton_event->setContextMenuPolicy(Qt::CustomContextMenu);
}


void UneditableEventWidget::callCustomMenu(const QPoint mousePosition) {
    /// Вызов кастомного контекстного меню по позиции курсора
    customMenu->call(this->ui->pushButton_event->mapToGlobal(mousePosition));
}

void UneditableEventWidget::setTitle(const QString title) {
    this->title = title;
    this->ui->pushButton_event->setText(this->title);
}

void UneditableEventWidget::setUnselected() {
    /// Делаем checkBox не выбранным
    this->ui->checkBox->setChecked(false);
    /// Отправляем сигнал о том, что выбор checkBox отменяется ( см. UneditableEventWidget::onCheckBoxClicked() )
    emit this->ui->checkBox->clicked();
}

void UneditableEventWidget::slotEditEvent() {
    emit signalEditEvent(this);
}

void UneditableEventWidget::slotDeleteEvent() {
    emit signalDeleteEvent(this);
}
