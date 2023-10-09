#include "UneditableEventWidget.h"
#include "ui_UneditableEventWidget.h"

UneditableEventWidget::UneditableEventWidget(const quint32 id, const QString title, QWidget *parent) : QWidget(parent), ui(new Ui::UneditableEventWidget) {
    ui->setupUi(this);

    this->ui->pushButton_event->setMinimumSize(200, 60);

    this->id = id;
    this->title = title;

    this->ui->checkBox->setChecked(false);

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


    customMenu->setup();
    customMenu->init();

    QObject::connect(this->customMenu, &UneditableItemMenu::signalEditCategory, this, &UneditableEventWidget::slotEditEvent);
    QObject::connect(this->customMenu, &UneditableItemMenu::signalDeleteCategory, this, &UneditableEventWidget::slotDeleteEvent);

    QObject::connect(this->ui->pushButton_event, &QPushButton::clicked, this, &UneditableEventWidget::slotEditEvent);
    QObject::connect(this->ui->pushButton_event, &QPushButton::customContextMenuRequested, this, &UneditableEventWidget::callCustomMenu);


    this->ui->pushButton_event->setContextMenuPolicy(Qt::CustomContextMenu);
}


void UneditableEventWidget::callCustomMenu(const QPoint mousePosition) {

    customMenu->call(this->ui->pushButton_event->mapToGlobal(mousePosition));
}

void UneditableEventWidget::setTitle(const QString title) {
    this->title = title;
    this->ui->pushButton_event->setText(this->title);
}

void UneditableEventWidget::setUnselected() {

    this->ui->checkBox->setChecked(false);

    emit this->ui->checkBox->clicked();
}

void UneditableEventWidget::slotEditEvent() {
    emit signalEditEvent(this);
}

void UneditableEventWidget::slotDeleteEvent() {
    emit signalDeleteEvent(this);
}
