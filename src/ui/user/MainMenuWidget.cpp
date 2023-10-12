#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"

#include "../EnumMenuPages.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenuWidget) {
    ui->setupUi(this);
    ui->scrollArea_categories->setLayout(new QVBoxLayout());
    ui->scrollArea_categories->layout()->setAlignment(Qt::AlignTop);
    ui->scrollArea_events->setLayout(new QVBoxLayout());
    ui->scrollArea_events->layout()->setAlignment(Qt::AlignTop);
    ui->scrollArea_selectes_eventes->setLayout(new QVBoxLayout());
    ui->scrollArea_selectes_eventes->layout()->setAlignment(Qt::AlignTop);
}

void MainMenuWidget::clearCategories() {
    QWidget * m_view = this->ui->scrollArea_categories;
    if ( m_view->layout() != NULL ) {
        QLayoutItem* item;
        while ( ( item = m_view->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
        //delete m_view->layout();
    }
}

void MainMenuWidget::addCategory(SelectedWidget * category) {
    QLayout * layout = this->ui->scrollArea_categories->layout(); //->addScrollBarWidget(category, Qt::AlignTop);
    layout->addWidget(category);
}

void MainMenuWidget::clearAvailableEvents() {
    QWidget * m_view = this->ui->scrollArea_events;
    if ( m_view->layout() != NULL ) {
        QLayoutItem* item;
        while ( ( item = m_view->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
        //delete m_view->layout();
    }
}

void MainMenuWidget::addEvent(SelectedWidget * event) {
    QLayout * layout = this->ui->scrollArea_events->layout(); //->addScrollBarWidget(category, Qt::AlignTop);
    layout->addWidget(event);
}

void MainMenuWidget::clearSelectedEvents() {
    QWidget * m_view = this->ui->scrollArea_selectes_eventes;
    if ( m_view->layout() != NULL ) {
        QLayoutItem* item;
        while ( ( item = m_view->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
        //delete m_view->layout();
    }
}

void MainMenuWidget::addSelectedEvent(SelectedWidget * event) {
    QLayout * layout = this->ui->scrollArea_selectes_eventes->layout(); //->addScrollBarWidget(category, Qt::AlignTop);
    layout->addWidget(event);
}

void MainMenuWidget::openMainMenu() {
    this->ui->stackedWidget->setCurrentIndex(EnumMenuPages::MainMenu);
}

MainMenuWidget::~MainMenuWidget() {
    delete ui;
}
