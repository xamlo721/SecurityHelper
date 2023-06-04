#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenuWidget) {
    ui->setupUi(this);
    ui->scrollAreaWidgetContents_categories->setLayout(new QVBoxLayout());
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

void MainMenuWidget::addCategory(EventCategoryWidget * category) {
    QLayout * layout = this->ui->scrollAreaWidgetContents_categories->layout(); //->addScrollBarWidget(category, Qt::AlignTop);
    layout->addWidget(category);
    QObject::connect(category, &EventCategoryWidget::signalOpenIncident, this, &MainMenuWidget::onCategoryClicked);

}

void MainMenuWidget::onCategoryClicked(int categoryId) {

}


MainMenuWidget::~MainMenuWidget() {
    delete ui;
}
