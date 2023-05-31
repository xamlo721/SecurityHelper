#include "MainMenu.h"
#include "ui_MainMenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenu) {
    ui->setupUi(this);
}

void MainMenu::clearCategories() {
//    this->ui->scrollArea_categories->layout().re
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

void MainMenu::addCategory(IncidentCategoryWidget * category) {
    this->ui->scrollArea_categories->layout()->addWidget(category);
}


MainMenu::~MainMenu() {
    delete ui;
}
