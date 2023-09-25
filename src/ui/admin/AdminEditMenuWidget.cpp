#include "AdminEditMenuWidget.h"
#include "ui_AdminEditMenuWidget.h"

//#include "ui_EditableEventCategoryWidget.h"

AdminEditMenuWidget::AdminEditMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AdminEditMenuWidget) {
    this->ui->setupUi(this);
    // Создаем QVBoxLayout для возможности использовать метод insert ( вставить на нужное место виджет )
    box_layout = new QVBoxLayout();
    this->ui->scrollAreaWidgetContents_categories->setLayout(box_layout);
}

void AdminEditMenuWidget::initUneditableCategory(UneditableEventCategoryWidget *uneditableCategory) {
    QObject::connect(uneditableCategory, &UneditableEventCategoryWidget::signalEditCategory, this, &AdminEditMenuWidget::signalEditCategory);
    //QObject::connect(uneditableCategory, &UneditableEventCategoryWidget::signalDeleteCategory, this, &AdminEditMenuWidget::signalDeleteCategory);
}

void AdminEditMenuWidget::initEditableCategory(EditableEventCategoryWidget *editableCategory) {
    QObject::connect(editableCategory, &EditableEventCategoryWidget::editingFinished, this, &AdminEditMenuWidget::editingFinished);
}

void AdminEditMenuWidget::addCategory(UneditableEventCategoryWidget *uneditableCategory) {
    uneditableCategory->initMenu();
    this->initUneditableCategory(uneditableCategory);
    QLayout * layout = this->ui->scrollAreaWidgetContents_categories->layout();
    layout->addWidget(uneditableCategory);
}

void AdminEditMenuWidget::clearCategories() {
    QWidget * m_view = this->ui->scrollAreaWidgetContents_categories;
    if ( m_view->layout() != NULL ) {
        QLayoutItem* item;
        while ( ( item = m_view->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
        //delete m_view->layout();
    }
}

void AdminEditMenuWidget::makeCategoryEditable(UneditableEventCategoryWidget *uneditableCategory) {
    /// Берем номер не редактируемого виджета
    quint32 widgetPosition = this->ui->scrollAreaWidgetContents_categories->layout()->indexOf(uneditableCategory);
    /// Инициализируем редактируемый виджет из не редактируемого
    EditableEventCategoryWidget *editableCategory= new EditableEventCategoryWidget(uneditableCategory->getId(), uneditableCategory->getText());
    /// Инициализируем связь сигналов редактируемого виджета с данным меню
    this->initEditableCategory(editableCategory);


    ///     Удаляем не редактируемый виджет из box_layout и удаляем переменную
    /// данного виджета, чтобы не было добавляющихся фантомных виджетов
    box_layout->removeWidget(uneditableCategory);
    delete uneditableCategory;
    /// Вставляем на нужное место редактируемый виджет
    box_layout->insertWidget(widgetPosition, editableCategory);

}

void AdminEditMenuWidget::makeCategoryUneditable(EditableEventCategoryWidget *editableCategory) {
    /// Берем номер редактируемого виджета
    quint32 widgetPosition = this->ui->scrollAreaWidgetContents_categories->layout()->indexOf(editableCategory);
    /// Инициализируем не редактируемый виджет из редактируемого
    UneditableEventCategoryWidget *uneditableCategory= new UneditableEventCategoryWidget(editableCategory->getId(), editableCategory->getText());
    /// Инициализируем контекстное меню не редактируемого виджета
    uneditableCategory->initMenu();
    /// Инициализируем связь сигналов не редактируемого виджета с данным меню
    this->initUneditableCategory(uneditableCategory);


    ///     Удаляем редактируемый виджет из box_layout и удаляем переменную
    /// данного виджета, чтобы не было добавляющихся фантомных виджетов
    box_layout->removeWidget(editableCategory);
    delete editableCategory;
    /// Вставляем на нужное место не редактируемый виджет
    box_layout->insertWidget(widgetPosition, uneditableCategory);
}

AdminEditMenuWidget::~AdminEditMenuWidget() {
    delete ui;
}
