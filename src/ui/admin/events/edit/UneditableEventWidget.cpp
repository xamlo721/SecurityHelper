#include "UneditableEventWidget.h"
#include "ui_UneditableEventWidget.h"

UneditableEventWidget::UneditableEventWidget(const quint32 id, const QString title, QWidget *parent) : QWidget(parent), ui(new Ui::UneditableEventWidget) {
    ui->setupUi(this);
    /// Задаем минимальный размер кнопки
    this->ui->pushButton_event->setMinimumSize(200, 60);
    /// Инициализируем поля класса
    this->id = id;
    this->text = title;
    this->ui->checkBox->setChecked(false);
    /// Устанавливаем текст на кнопке
    this->ui->pushButton_event->setText(text);

    QObject::connect(this->ui->checkBox, &QCheckBox::clicked, this, &UneditableEventWidget::onCheckBoxClicked);
}

void UneditableEventWidget::onCheckBoxClicked() {
    switch (this->ui->checkBox->isChecked()) {
    case true:

        emit signalCategorySelected(this->getID());
        break;

    case false:

        emit signalCategoryUnselected(this->getID());
        break;
    }
}

void UneditableEventWidget::initMenu() {
    customMenu = new UneditableItemMenu();

    /// Установка и инициализация меню
    customMenu->setup();
    customMenu->init();

    QObject::connect(this->customMenu, &UneditableItemMenu::signalEditCategory, this, &UneditableEventWidget::slotEditCategory);
    QObject::connect(this->customMenu, &UneditableItemMenu::signalDeleteCategory, this, &UneditableEventWidget::slotDeleteCategory);

    QObject::connect(this->ui->pushButton_event, &QPushButton::clicked, this, &UneditableEventWidget::slotEditCategory);
    QObject::connect(this->ui->pushButton_event, &QPushButton::customContextMenuRequested, this, &UneditableEventWidget::callCustomMenu);

    /// Установка политики меню, позволяющая показывать кастомное контекстное меню и использовать сигнал &QPushButton::customContextMenuRequested
    this->ui->pushButton_event->setContextMenuPolicy(Qt::CustomContextMenu);
}


void UneditableEventWidget::callCustomMenu(const QPoint mousePosition) {
    /// Вызов кастомного контекстного меню по позиции курсора
    customMenu->call(this->ui->pushButton_event->mapToGlobal(mousePosition));
}

void UneditableEventWidget::setText(const QString text) {
    this->text = text;
    this->ui->pushButton_event->setText(this->text);
}

void UneditableEventWidget::slotEditCategory() {
    emit signalEditCategory(this);
}

void UneditableEventWidget::slotDeleteCategory() {
    emit signalDeleteCategory(this);
}

UneditableEventWidget::~UneditableEventWidget() {
    delete ui;
    delete customMenu;
}
