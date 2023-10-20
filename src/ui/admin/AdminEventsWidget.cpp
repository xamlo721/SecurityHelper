#include "AdminEventsWidget.h"
#include "ui_AdminEventsWidget.h"

AdminEventsWidget::AdminEventsWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AdminEventsWidget) {
    ui->setupUi(this);
    QObject::connect(this->ui->pushButton_addEvent, &QPushButton::clicked, this, &AdminEventsWidget::onAddEventButtonPressed);
    QObject::connect(this->ui->pushButton_editEvent, &QPushButton::clicked, this, &AdminEventsWidget::onEditEventButtonPressed);
    QObject::connect(this->ui->pushButton_deleteSelectedEvents, &QPushButton::clicked, this, &AdminEventsWidget::onDelEventButtonPressed);

}

AdminEventsWidget::~AdminEventsWidget() {
    delete ui;
}

/**
 * @brief clearEvents - очищает визуальный список событий
 */
void AdminEventsWidget::clearEvents() {
    this->ui->scrollArea_events->clear();
}

/**
 * @brief addEvent - добавляет в отображаемый список событий новый виджет
 * @param event - заранее сделанный виджет
 */
void AdminEventsWidget::addEvent(SelectedWidget * event) {
    QObject::connect(event, &SelectedWidget::signalSelected, this, &AdminEventsWidget::signalEventClicked);
    this->ui->scrollArea_events->addWidget(event->getId(), event);
}

void AdminEventsWidget::onAddEventButtonPressed() {
    this->ui->scrollArea_events->unselect();
    emit signalAddEventClicked();
}

void AdminEventsWidget::onEditEventButtonPressed() {
    //TODO: открыть окно редактирования

}

void AdminEventsWidget::onDelEventButtonPressed() {
    emit signalDelEventClicked(this->ui->scrollArea_events->getSelectedWidgetID());
}
