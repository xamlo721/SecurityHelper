#include "AdminEditMenuWidget.h"
#include "ui_AdminEditMenuWidget.h"

/**
 *  @brief AdminEditMenuWidget - конструктор по умолчанию
 *  @param parent - родительский объект в иерархии Qt.
 *  В данном конструкторе производится установка UI.
 */
AdminEditMenuWidget::AdminEditMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AdminEditMenuWidget) {
    this->ui->setupUi(this);

    QObject::connect(this->ui->pushButton_addCategory, &QPushButton::clicked, this, &AdminEditMenuWidget::signalAddCategoryButtonPressed);
    QObject::connect(this->ui->pushButton_deleteCategory, &QPushButton::clicked, this, &AdminEditMenuWidget::signalDeleteCategoryButtonPressed);
}

/**
 *  @brief setupScrollAreas - метод, выделяющий память под
 *  указатели на QVBoxLayout для каждого item'а и добавляющий их в
 *  соответствующие scrollArea.
 */
void AdminEditMenuWidget::setupScrollAreas() {
    /// Инициализируем boxLayout для каждой scrollArea
    boxLayoutCategories = new QVBoxLayout();
    boxLayoutEvents = new QVBoxLayout();
    boxLayoutIncidents = new QVBoxLayout();
    boxLayoutScenaries = new QVBoxLayout();

    /// Устанавливаем во все scrollArea соответствущие boxLayout
    this->ui->scrollAreaWidgetContents_categories->setLayout(boxLayoutCategories);
    this->ui->scrollAreaWidgetContents_events->setLayout(boxLayoutEvents);
    this->ui->scrollAreaWidgetContents_incidents->setLayout(boxLayoutIncidents);
    this->ui->scrollAreaWidgetContents_scenaries->setLayout(boxLayoutScenaries);
}

/**
 *  @brief getBoxLayoutCategories - метод, позволяющий получить бокс категорий.
 */
QVBoxLayout *AdminEditMenuWidget::getBoxLayoutCategories() {
    return this->boxLayoutCategories;
}
/**
 *  @brief getBoxLayoutEvents - метод, позволяющий получить бокс событий.
 */
QVBoxLayout *AdminEditMenuWidget::getBoxLayoutEvents() {
    return this->boxLayoutEvents;
}
/**
 *  @brief getBoxLayoutIncidents - метод, позволяющий получить бокс инцидентов.
 */
QVBoxLayout *AdminEditMenuWidget::getBoxLayoutIncidents() {
    return this->boxLayoutIncidents;
}
/**
 *  @brief getBoxLayoutScenaries - метод, позволяющий получить бокс сценариев.
 */
QVBoxLayout *AdminEditMenuWidget::getBoxLayoutScenaries() {
    return this->boxLayoutScenaries;
}
/**
 *  @brief ~AdminEditMenuWidget - деструктор по умолчанию, используется для
 * высвобождения памяти.
 */
AdminEditMenuWidget::~AdminEditMenuWidget() {
    delete boxLayoutCategories;
    delete boxLayoutEvents;
    delete boxLayoutIncidents;
    delete boxLayoutScenaries;

    delete ui;
}
