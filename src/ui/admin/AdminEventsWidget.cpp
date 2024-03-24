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
    QObject::connect(event, &SelectedWidget::signalSelected, this, &AdminEventsWidget::signalEventSelected);
    QObject::connect(event, &SelectedWidget::signalUnselected, this, &AdminEventsWidget::signalEventUnselected);
    this->ui->scrollArea_events->addWidget(event->getId(), event);
}


/**
 * @brief enableEditButton - включить доступность кнопки
 * "Редактировать" на пакели событий
 */
void AdminEventsWidget::enableEditButton() {
    this->ui->pushButton_editEvent->setEnabled(true);
}

/**
 * @brief disableEditButton - выключить доступность кнопки
 * "Редактировать" на пакели событий
 */
void AdminEventsWidget::disableEditButton() {
    this->ui->pushButton_editEvent->setEnabled(false);
}

/**
 * @brief enableDeleteButton - включить доступность кнопки
 * "Удалить" на пакели событий
 */
void AdminEventsWidget::enableDeleteButton() {
    this->ui->pushButton_deleteSelectedEvents->setEnabled(true);
}

/**
 * @brief disableDeleteButton - выключить доступность кнопки
 * "Удалить" на пакели событий
 */
void AdminEventsWidget::disableDeleteButton() {
    this->ui->pushButton_deleteSelectedEvents->setEnabled(false);
}


/**
 * @brief onAddEventButtonPressed - слот, активируемый при нажатии
 * накнопку "Добавить" в списке событий
 */
void AdminEventsWidget::onAddEventButtonPressed() {
    this->ui->scrollArea_events->unselect();
    emit signalAddEventClicked();
}

/**
 * @brief onEditEventButtonPressed - слот, активируемый при нажатии
 * на кнопку "Редактировать" в списке событий
 */
void AdminEventsWidget::onEditEventButtonPressed() {
    //TODO: Оставить возможность редактировать только если выбрано событие
    emit signalEditEventClicked(this->ui->scrollArea_events->getSelectedWidgetID());
}

/**
 * @brief onDelEventButtonPressed - слот, активируемый при нажатии
 * на кнопку "Удалить" в списке событий
 */
void AdminEventsWidget::onDelEventButtonPressed() {
    emit signalDelEventClicked(this->ui->scrollArea_events->getSelectedWidgetID());
}
