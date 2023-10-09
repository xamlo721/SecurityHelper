#include "UneditableScenarioWidget.h"
#include "ui_UneditableScenarioWidget.h"

UneditableScenarioWidget::UneditableScenarioWidget(const quint32 id, const QString title, QWidget *parent) : QWidget(parent), ui(new Ui::UneditableScenarioWidget) {
    ui->setupUi(this);

    this->ui->pushButton_scenario->setMinimumSize(200, 60);

    this->id = id;
    this->title = title;

    this->ui->checkBox->setChecked(false);

    this->ui->pushButton_scenario->setText(title);

    QObject::connect(this->ui->checkBox, &QCheckBox::clicked, this, &UneditableScenarioWidget::onCheckBoxClicked);
}

UneditableScenarioWidget::~UneditableScenarioWidget() {
    delete ui;

    delete customMenu;
}

void UneditableScenarioWidget::onCheckBoxClicked() {
    switch (this->ui->checkBox->isChecked()) {
    case true:

        emit signalScenarioSelected(this->getID());
        break;

    case false:

        emit signalScenarioUnselected(this->getID());
        break;
    }
}

void UneditableScenarioWidget::initMenu() {
    customMenu = new UneditableItemMenu();

    customMenu->setup();
    customMenu->init();

    QObject::connect(this->customMenu, &UneditableItemMenu::signalEditCategory, this, &UneditableScenarioWidget::slotEditScenario);
    QObject::connect(this->customMenu, &UneditableItemMenu::signalDeleteCategory, this, &UneditableScenarioWidget::slotDeleteScenario);

    QObject::connect(this->ui->pushButton_scenario, &QPushButton::clicked, this, &UneditableScenarioWidget::slotEditScenario);
    QObject::connect(this->ui->pushButton_scenario, &QPushButton::customContextMenuRequested, this, &UneditableScenarioWidget::callCustomMenu);


    this->ui->pushButton_scenario->setContextMenuPolicy(Qt::CustomContextMenu);
}


void UneditableScenarioWidget::callCustomMenu(const QPoint mousePosition) {
    customMenu->call(this->ui->pushButton_scenario->mapToGlobal(mousePosition));
}

void UneditableScenarioWidget::setTitle(const QString title) {
    this->title = title;
    this->ui->pushButton_scenario->setText(this->title);
}

void UneditableScenarioWidget::setUnselected() {
    this->ui->checkBox->setChecked(false);

    emit this->ui->checkBox->clicked();
}

void UneditableScenarioWidget::slotEditScenario() {
    emit signalEditScenario(this);
}

void UneditableScenarioWidget::slotDeleteScenario() {
    emit signalDeleteScenario(this);
}
