#include "ScenarioMenuWidget.h"
#include "ui_ScenarioMenuWidget.h"

ScenarioMenuWidget::ScenarioMenuWidget( QWidget *parent) : QWidget(parent), ui(new Ui::ScenarioMenuWidget) {
    ui->setupUi(this);
}

void ScenarioMenuWidget::clear() {
    QWidget * m_view = this->ui->scrollAreaWidgetContents;
    if ( m_view->layout() != NULL ) {
        QLayoutItem* item;
        while ( ( item = m_view->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;

        }
        //delete m_view->layout();
    }
}

void ScenarioMenuWidget::addScenarioWidget(ScenarioWidget *widget) {
    //FIXME: Починить баг отображения. Не скролятся виджеты!
    this->ui->scrollAreaWidgetContents->layout()->addWidget(widget);
}

void ScenarioMenuWidget::closeScenarioWidget(ScenarioWidget *widget) {
    delete widget;
}//

ScenarioMenuWidget::~ScenarioMenuWidget() {
    delete ui;
}
