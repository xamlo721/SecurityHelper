#include "AdminEditMenuWidget.h"
#include "ui_AdminEditMenuWidget.h"

/**
 *  @brief AdminEditMenuWidget - конструктор по умолчанию
 *  @param parent - родительский объект в иерархии Qt.
 *  В данном конструкторе производится установка UI.
 */
AdminEditMenuWidget::AdminEditMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AdminEditMenuWidget) {
    this->ui->setupUi(this);

    /// Блокируем все кнопки Удалить, т.к. каждой кнопке необходим свой активный виджет для возможности удаления виджета
    this->setAllDeleteButtonsDisabled();

    QObject::connect(this->ui->pushButton_addCategory, &QPushButton::clicked, this, &AdminEditMenuWidget::signalAddCategoryButtonPressed);
    QObject::connect(this->ui->pushButton_deleteSelectedCategories, &QPushButton::clicked, this, &AdminEditMenuWidget::signalDeleteSelectedCategoriesButtonPressed);

    QObject::connect(this->ui->pushButton_addEvent, &QPushButton::clicked, this, &AdminEditMenuWidget::signalAddEventButtonPressed);
    QObject::connect(this->ui->pushButton_deleteSelectedEvents, &QPushButton::clicked, this, &AdminEditMenuWidget::signalDeleteSelectedEventsButtonPressed);

    this->ui->pushButton_deleteSelectedCategories->setMouseTracking(true);
    this->ui->pushButton_deleteSelectedCategories->installEventFilter(this);
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

void AdminEditMenuWidget::setAllTabsEnable() {
    /// Делаем все вкладки доступными
    this->ui->categories->setEnabled(true);
    this->ui->events->setEnabled(true);
    this->ui->incidents->setEnabled(true);
    this->ui->scenaries->setEnabled(true);
    this->ui->recommendations->setEnabled(true);
}

void AdminEditMenuWidget::setCategoriesActive() {
    /// Делаем все вкладки, кроме категорий, недоступными
    this->ui->events->setEnabled(false);
    this->ui->incidents->setEnabled(false);
    this->ui->scenaries->setEnabled(false);
    this->ui->recommendations->setEnabled(false);
}

void AdminEditMenuWidget::setEventsActive() {
    /// Делаем все вкладки, кроме событий, недоступными
    this->ui->categories->setEnabled(false);
    this->ui->incidents->setEnabled(false);
    this->ui->scenaries->setEnabled(false);
    this->ui->recommendations->setEnabled(false);
}

void AdminEditMenuWidget::setIncidentsActive() {
    /// Делаем все вкладки, кроме инцидентов, недоступными
    this->ui->categories->setEnabled(false);
    this->ui->events->setEnabled(false);
    this->ui->scenaries->setEnabled(false);
    this->ui->recommendations->setEnabled(false);
}

void AdminEditMenuWidget::setScenariesActive() {
    /// Делаем все вкладки, кроме сценариев, недоступными
    this->ui->categories->setEnabled(false);
    this->ui->events->setEnabled(false);
    this->ui->incidents->setEnabled(false);
    this->ui->recommendations->setEnabled(false);
}

void AdminEditMenuWidget::setRecommendtaionsActive() {
    /// Делаем все вкладки, кроме рекоммендаций, недоступными
    this->ui->categories->setEnabled(false);
    this->ui->events->setEnabled(false);
    this->ui->incidents->setEnabled(false);
    this->ui->scenaries->setEnabled(false);
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

void AdminEditMenuWidget::setAllDeleteButtonsDisabled() {
    this->ui->pushButton_deleteSelectedCategories->setEnabled(false);
    this->ui->pushButton_deleteSelectedEvents->setEnabled(false);
    this->ui->pushButton_deleteIncident->setEnabled(false);
    this->ui->pushButton_deleteScenario->setEnabled(false);
    this->ui->pushButton_deleteRecommendation->setEnabled(false);

    this->ui->pushButton_removeInCategoryEvent->setEnabled(false);
    this->ui->pushButton_removeInIncidentEvent->setEnabled(false);
    this->ui->pushButton_removeInScenarioIncident->setEnabled(false);

}


// Блок управления кнопками категорий
void AdminEditMenuWidget::setAddCategoryButtonEnabled() {
    this->ui->pushButton_addCategory->setEnabled(true);
}

void AdminEditMenuWidget::setAddCategoryButtonDisabled() {
    this->ui->pushButton_addCategory->setEnabled(false);
}

void AdminEditMenuWidget::setDeleteSelectedCategoriesButtonEnabled() {
    this->ui->pushButton_deleteSelectedCategories->setEnabled(true);
}

void AdminEditMenuWidget::setDeleteSelectedCategoriesButtonDisabled() {
    this->ui->pushButton_deleteSelectedCategories->setEnabled(false);
}


// Блок управления кнопками событий
void AdminEditMenuWidget::setAddEventButtonEnabled() {
    this->ui->pushButton_addEvent->setEnabled(true);
}

void AdminEditMenuWidget::setAddEventButtonDisabled() {
    this->ui->pushButton_addEvent->setEnabled(false);
}

void AdminEditMenuWidget::setDeleteSelectedEventsButtonEnabled() {
    this->ui->pushButton_deleteSelectedEvents->setEnabled(true);
}

void AdminEditMenuWidget::setDeleteSelectedEventsButtonDisabled() {
    this->ui->pushButton_deleteSelectedEvents->setEnabled(false);
}
