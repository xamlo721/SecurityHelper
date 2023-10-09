#include "UneditableIncidentWidget.h"
#include "ui_UneditableIncidentWidget.h"

UneditableIncidentWidget::UneditableIncidentWidget(const quint32 id, const QString title, QWidget *parent) : QWidget(parent), ui(new Ui::UneditableIncidentWidget) {
    ui->setupUi(this);

    this->ui->pushButton_incident->setMinimumSize(200, 60);

    this->id = id;
    this->title = title;

    this->ui->checkBox->setChecked(false);

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


    customMenu->setup();
    customMenu->init();

    QObject::connect(this->customMenu, &UneditableItemMenu::signalEditCategory, this, &UneditableIncidentWidget::slotEditIncident);
    QObject::connect(this->customMenu, &UneditableItemMenu::signalDeleteCategory, this, &UneditableIncidentWidget::slotDeleteIncident);

    QObject::connect(this->ui->pushButton_incident, &QPushButton::clicked, this, &UneditableIncidentWidget::slotEditIncident);
    QObject::connect(this->ui->pushButton_incident, &QPushButton::customContextMenuRequested, this, &UneditableIncidentWidget::callCustomMenu);

    this->ui->pushButton_incident->setContextMenuPolicy(Qt::CustomContextMenu);
}


void UneditableIncidentWidget::callCustomMenu(const QPoint mousePosition) {
    customMenu->call(this->ui->pushButton_incident->mapToGlobal(mousePosition));
}

void UneditableIncidentWidget::setTitle(const QString title) {
    this->title = title;
    this->ui->pushButton_incident->setText(this->title);
}

void UneditableIncidentWidget::setUnselected() {
    this->ui->checkBox->setChecked(false);

    emit this->ui->checkBox->clicked();
}

void UneditableIncidentWidget::slotEditIncident() {
    emit signalEditIncident(this);
}

void UneditableIncidentWidget::slotDeleteIncident() {
    emit signalDeleteIncident(this);
}
