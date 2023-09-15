#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenuWidget) {
    ui->setupUi(this);
    ui->scrollAreaWidgetContents_categories->setLayout(new QVBoxLayout());
    ui->scrollAreaWidgetContents_events->setLayout(new QVBoxLayout());
    ui->scrollAreaWidgetContents_selectes_eventes->setLayout(new QVBoxLayout());
}

void MainMenuWidget::clearCategories() {
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

void MainMenuWidget::addCategory(EventCategoryWidget * category) {
    QLayout * layout = this->ui->scrollAreaWidgetContents_categories->layout(); //->addScrollBarWidget(category, Qt::AlignTop);
    layout->addWidget(category);
}

void MainMenuWidget::clearAvailableEvents() {
    QWidget * m_view = this->ui->scrollAreaWidgetContents_events;
    if ( m_view->layout() != NULL ) {
        QLayoutItem* item;
        while ( ( item = m_view->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
        //delete m_view->layout();
    }
}

void MainMenuWidget::addEvent(EventWidget * event) {
    QLayout * layout = this->ui->scrollAreaWidgetContents_events->layout(); //->addScrollBarWidget(category, Qt::AlignTop);
    layout->addWidget(event);
}

void MainMenuWidget::clearSelectedEvents() {
    QWidget * m_view = this->ui->scrollAreaWidgetContents_selectes_eventes;
    if ( m_view->layout() != NULL ) {
        QLayoutItem* item;
        while ( ( item = m_view->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
        //delete m_view->layout();
    }
}

void MainMenuWidget::addSelectedEvent(EventWidget * event) {
    QLayout * layout = this->ui->scrollAreaWidgetContents_selectes_eventes->layout(); //->addScrollBarWidget(category, Qt::AlignTop);
    layout->addWidget(event);
}

void MainMenuWidget::addEditableCategory(EditableEventCategoryWidget * editableCategory) {
    QLayout * layout = this->ui->scrollAreaWidgetContents_categories->layout(); //->addScrollBarWidget(category, Qt::AlignTop);
    layout->addWidget(editableCategory);
}

void MainMenuWidget::addEditableEvent(EditableEventWidget * editableEvent) {
    QLayout * layout = this->ui->scrollAreaWidgetContents_events->layout(); //->addScrollBarWidget(category, Qt::AlignTop);
    layout->addWidget(editableEvent);
}

MainMenuWidget::~MainMenuWidget() {
    delete ui;
}
