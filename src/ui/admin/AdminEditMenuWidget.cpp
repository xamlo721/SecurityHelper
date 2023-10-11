#include "AdminEditMenuWidget.h"
#include "ui_AdminEditMenuWidget.h"

/**
 *  @brief AdminEditMenuWidget - конструктор по умолчанию
 *  @param parent - родительский объект в иерархии Qt.
 *  В данном конструкторе производится установка UI.
 */
AdminEditMenuWidget::AdminEditMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AdminEditMenuWidget) {
    this->ui->setupUi(this);

    /// Блокируем все кнопки Добавить выбранное в {item}, т.к. каждой кнопке необходим свой активный виджет для возможности добавления куда-либо
    this->setAllAddToButtonsDisabled();
    /// Блокируем все кнопки Удалить выбранное и Удалить выбранное из {item}, т.к. каждой кнопке необходим свой активный виджет для возможности удаления виджета
    this->setAllDeleteButtonsDisabled();



//    QObject::connect(this->ui->pushButton_addCategory, &QPushButton::clicked, this, &AdminEditMenuWidget::signalAddCategoryButtonPressed);
//    QObject::connect(this->ui->pushButton_deleteSelectedCategories, &QPushButton::clicked, this, &AdminEditMenuWidget::signalDeleteSelectedCategoriesButtonPressed);

//    QObject::connect(this->ui->pushButton_addToCategory, &QPushButton::clicked, this, &AdminEditMenuWidget::signalAddToCategoryButtonPressed);
//    QObject::connect(this->ui->pushButton_removeFromCategory, &QPushButton::clicked, this, &AdminEditMenuWidget::signalRemoveFromCategoryButtonPressed);



//    QObject::connect(this->ui->pushButton_addEvent, &QPushButton::clicked, this, &AdminEditMenuWidget::signalAddEventButtonPressed);
//    QObject::connect(this->ui->pushButton_deleteSelectedEvents, &QPushButton::clicked, this, &AdminEditMenuWidget::signalDeleteSelectedEventsButtonPressed);



//    QObject::connect(this->ui->pushButton_addIncident, &QPushButton::clicked, this, &AdminEditMenuWidget::signalAddIncidentButtonPressed);
//    QObject::connect(this->ui->pushButton_deleteSelectedIncidents, &QPushButton::clicked, this, &AdminEditMenuWidget::signalDeleteSelectedIncidentsButtonPressed);

//    QObject::connect(this->ui->pushButton_addToIncident, &QPushButton::clicked, this, &AdminEditMenuWidget::signalAddToIncidentButtonPressed);
//    QObject::connect(this->ui->pushButton_removeFromIncident, &QPushButton::clicked, this, &AdminEditMenuWidget::signalRemoveFromIncidentButtonPressed);



//    QObject::connect(this->ui->pushButton_addScenario, &QPushButton::clicked, this, &AdminEditMenuWidget::signalAddScenarioButtonPressed);
//    QObject::connect(this->ui->pushButton_deleteSelectedScenaries, &QPushButton::clicked, this, &AdminEditMenuWidget::signalDeleteSelectedScenariesButtonPressed);

//    QObject::connect(this->ui->pushButton_addToScenario, &QPushButton::clicked, this, &AdminEditMenuWidget::signalAddToScenarioButtonPressed);
//    QObject::connect(this->ui->pushButton_removeFromScenario, &QPushButton::clicked, this, &AdminEditMenuWidget::signalRemoveFromScenarioButtonPressed);



//    this->ui->pushButton_deleteSelectedCategories->setMouseTracking(true);
//    this->ui->pushButton_deleteSelectedCategories->installEventFilter(this);
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

void AdminEditMenuWidget::setAllAddToButtonsDisabled() {
//    this->ui->pushButton_addToCategory->setEnabled(false);
//    this->ui->pushButton_addToIncident->setEnabled(false);
//    this->ui->pushButton_addToScenario->setEnabled(false);
}

void AdminEditMenuWidget::setAllDeleteButtonsDisabled() {
//    this->ui->pushButton_deleteSelectedCategories->setEnabled(false);
//    this->ui->pushButton_deleteSelectedEvents->setEnabled(false);
//    this->ui->pushButton_deleteSelectedIncidents->setEnabled(false);
//    this->ui->pushButton_deleteSelectedScenaries->setEnabled(false);
//    this->ui->pushButton_deleteRecommendation->setEnabled(false);

//    this->ui->pushButton_removeFromCategory->setEnabled(false);
//    this->ui->pushButton_removeFromIncident->setEnabled(false);
//    this->ui->pushButton_removeFromScenario->setEnabled(false);

}


// Блок управления кнопками вкладки Категории событий

/// Блок управления кнопками категорий событий
void AdminEditMenuWidget::setAddCategoryButtonEnabled() {
//    this->ui->pushButton_addCategory->setEnabled(true);
}

void AdminEditMenuWidget::setAddCategoryButtonDisabled() {
//    this->ui->pushButton_addCategory->setEnabled(false);
}

void AdminEditMenuWidget::setDeleteSelectedCategoriesButtonEnabled() {
//    this->ui->pushButton_deleteSelectedCategories->setEnabled(true);
}

void AdminEditMenuWidget::setDeleteSelectedCategoriesButtonDisabled() {
//    this->ui->pushButton_deleteSelectedCategories->setEnabled(false);
}

/// Блок управления кнопками событий в категориях событий
void AdminEditMenuWidget::setAddToCategoryButtonEnabled() {
//    this->ui->pushButton_addToCategory->setEnabled(true);
}

void AdminEditMenuWidget::setAddToCategoryButtonDisabled() {
//    this->ui->pushButton_addToCategory->setEnabled(false);
}

void AdminEditMenuWidget::setRemoveFromCategoryButtonEnabled() {
//    this->ui->pushButton_removeFromCategory->setEnabled(true);
}

void AdminEditMenuWidget::setRemoveFromCategoryButtonDisabled() {
//    this->ui->pushButton_removeFromCategory->setEnabled(false);
}


// Блок управления кнопками вкладки События
void AdminEditMenuWidget::setAddEventButtonEnabled() {
//    this->ui->pushButton_addEvent->setEnabled(true);
}

void AdminEditMenuWidget::setAddEventButtonDisabled() {
//    this->ui->pushButton_addEvent->setEnabled(false);
}

void AdminEditMenuWidget::setDeleteSelectedEventsButtonEnabled() {
//    this->ui->pushButton_deleteSelectedEvents->setEnabled(true);
}

void AdminEditMenuWidget::setDeleteSelectedEventsButtonDisabled() {
//    this->ui->pushButton_deleteSelectedEvents->setEnabled(false);
}


// Блок управления кнопками вкладки Инциденты

/// Блок управления кнопками инцидентов
void AdminEditMenuWidget::setAddIncidentButtonEnabled() {
//    this->ui->pushButton_addIncident->setEnabled(true);
}

void AdminEditMenuWidget::setAddIncidentButtonDisabled() {
//    this->ui->pushButton_addIncident->setEnabled(false);
}

void AdminEditMenuWidget::setDeleteSelectedIncidentsButtonEnabled() {
//    this->ui->pushButton_deleteSelectedIncidents->setEnabled(true);
}

void AdminEditMenuWidget::setDeleteSelectedIncidentsButtonDisabled() {
//    this->ui->pushButton_deleteSelectedIncidents->setEnabled(false);
}

/// Блок управления кнопками событий в инцидентах
void AdminEditMenuWidget::setAddToIncidentButtonEnabled() {
//    this->ui->pushButton_addToIncident->setEnabled(true);
}

void AdminEditMenuWidget::setAddToIncidentButtonDisabled() {
//    this->ui->pushButton_addToIncident->setEnabled(false);
}

void AdminEditMenuWidget::setRemoveFromIncidentButtonEnabled() {
//    this->ui->pushButton_removeFromIncident->setEnabled(true);
}

void AdminEditMenuWidget::setRemoveFromIncidentButtonDisabled() {
//    this->ui->pushButton_removeFromIncident->setEnabled(false);
}


// Блок управления кнопками вкладки Сценарии

/// Блок управления кнопками сценариев
void AdminEditMenuWidget::setAddScenarioButtonEnabled() {
//    this->ui->pushButton_addScenario->setEnabled(true);
}

void AdminEditMenuWidget::setAddScenarioButtonDisabled() {
//    this->ui->pushButton_addScenario->setEnabled(false);
}

void AdminEditMenuWidget::setDeleteSelectedScenariesButtonEnabled() {
//    this->ui->pushButton_deleteSelectedScenaries->setEnabled(true);
}

void AdminEditMenuWidget::setDeleteSelectedScenariesButtonDisabled() {
//    this->ui->pushButton_deleteSelectedScenaries->setEnabled(false);
}

/// Блок управления кнопками инцидентов в сценариях
void AdminEditMenuWidget::setAddToScenarioButtonEnabled() {
//    this->ui->pushButton_addToScenario->setEnabled(true);
}

void AdminEditMenuWidget::setAddToScenarioButtonDisabled() {
//    this->ui->pushButton_addToScenario->setEnabled(false);
}

void AdminEditMenuWidget::setRemoveFromScenarioButtonEnabled() {
//    this->ui->pushButton_removeFromScenario->setEnabled(true);
}

void AdminEditMenuWidget::setRemoveFromScenarioButtonDisabled() {
//    this->ui->pushButton_removeFromScenario->setEnabled(false);
}
