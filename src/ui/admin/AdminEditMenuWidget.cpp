#include "AdminEditMenuWidget.h"

/**
 *  @brief AdminEditMenuWidget - конструктор по умолчанию
 *  @param parent - родительский объект в иерархии Qt.
 *  В данном конструкторе производится установка UI.
 */
AdminEditMenuWidget::AdminEditMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AdminEditMenuWidget) {
    this->ui->setupUi(this);

    /// Блокируем все кнопки Добавить выбранное в {item}, т.к. каждой кнопке необходим свой активный виджет для возможности добавления куда-либо
    //this->setAllAddToButtonsDisabled();
    /// Блокируем все кнопки Удалить выбранное и Удалить выбранное из {item}, т.к. каждой кнопке необходим свой активный виджет для возможности удаления виджета
    //this->setAllDeleteButtonsDisabled();
}

/**
 *  @brief setupScrollAreas - метод, выделяющий память под
 *  указатели на QVBoxLayout для каждого item'а и добавляющий их в
 *  соответствующие scrollArea.
 */
void AdminEditMenuWidget::setupScrollAreas() {
    /// Инициализируем boxLayout для каждой scrollArea

    /// Инициализируем boxLayout для вкладки Категории событий
    boxLayoutCategories = new QVBoxLayout();
    boxLayoutInCategoryFreeEvents = new QVBoxLayout();
    boxLayoutInCategoryContainedEvents = new QVBoxLayout();

    /// Инициализируем boxLayout для вкладки События
    boxLayoutEvents = new QVBoxLayout();

    /// Инициализируем boxLayout для вкладки Инциденты
    boxLayoutIncidents = new QVBoxLayout();
    boxLayoutInIncidentFreeEvents = new QVBoxLayout();
    boxLayoutInIncidentContainedEvents = new QVBoxLayout();

    /// Инициализируем boxLayout для вкладки Сценарии
    boxLayoutScenaries = new QVBoxLayout();
    boxLayoutInScenarioFreeIncidents = new QVBoxLayout();
    boxLayoutInScenarioContainedIncidents = new QVBoxLayout();


    /// Устанавливаем во все scrollArea соответствущие boxLayout
//    this->ui->scrollAreaWidgetContents_categories->setLayout(boxLayoutCategories);
//    this->ui->scrollAreaWidgetContents_categories_freeEvents->setLayout(boxLayoutInCategoryFreeEvents);
//    this->ui->scrollAreaWidgetContents_categories_includedEvent->setLayout(boxLayoutInCategoryContainedEvents);


//    this->ui->scrollAreaWidgetContents_events->setLayout(boxLayoutEvents);


//    this->ui->scrollAreaWidgetContents_incidents->setLayout(boxLayoutIncidents);
//    this->ui->scrollAreaWidgetContents_incidents_freeEvents->setLayout(boxLayoutInIncidentFreeEvents);
//    this->ui->scrollAreaWidgetContents_incidents_includedEvent->setLayout(boxLayoutInIncidentContainedEvents);

//    this->ui->scrollAreaWidgetContents_scenaries->setLayout(boxLayoutScenaries);
//    this->ui->scrollAreaWidgetContents_scenaries_freeIncidents->setLayout(boxLayoutInScenarioFreeIncidents);
//    this->ui->scrollAreaWidgetContents_scenaries_includedIncidents->setLayout(boxLayoutInScenarioContainedIncidents);
}


/**
 *  @brief getBoxLayoutCategories - метод, позволяющий получить бокс категорий.
 */
QVBoxLayout *AdminEditMenuWidget::getBoxLayoutCategories() {
    return this->boxLayoutCategories;
}

QVBoxLayout *AdminEditMenuWidget::getBoxLayoutInCategoryFreeEvents() {
    return this->boxLayoutInCategoryFreeEvents;
}

QVBoxLayout *AdminEditMenuWidget::getBoxLayoutInCategoryIncludedEvents() {
    return this->boxLayoutInCategoryContainedEvents;
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

QVBoxLayout *AdminEditMenuWidget::getBoxLayoutInIncidentFreeEvents() {
    return this->boxLayoutInIncidentFreeEvents;
}

QVBoxLayout *AdminEditMenuWidget::getBoxLayoutInIncidentIncludedEvents() {
    return this->boxLayoutInIncidentContainedEvents;
}

/**
 *  @brief getBoxLayoutScenaries - метод, позволяющий получить бокс сценариев.
 */
QVBoxLayout *AdminEditMenuWidget::getBoxLayoutScenaries() {
    return this->boxLayoutScenaries;
}

QVBoxLayout *AdminEditMenuWidget::getBoxLayoutInScenarioFreeIncidents () {
    return this->boxLayoutInScenarioFreeIncidents;
}

QVBoxLayout *AdminEditMenuWidget::getBoxLayoutInScenarioIncludedIncidents() {
    return this->boxLayoutInScenarioContainedIncidents;
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

