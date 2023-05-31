#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenuWidget) {
    ui->setupUi(this);
}

void MainMenuWidget::clearCategories() {
    QScrollArea * m_view = this->ui->scrollArea_categories;
    if ( m_view->layout() != NULL ) {
        QLayoutItem* item;
        while ( ( item = m_view->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
        delete m_view->layout();
    }
}

void MainMenuWidget::addCategory(IncidentCategoryWidget * category) {
    this->ui->scrollArea_categories->layout()->addWidget(category);
}


MainMenuWidget::~MainMenuWidget() {
    delete ui;
}
