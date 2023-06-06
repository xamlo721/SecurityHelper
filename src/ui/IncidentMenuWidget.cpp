#include "IncidentMenuWidget.h"
#include "ui_IncidentMenuWidget.h"

IncidentMenuWidget::IncidentMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::IncidentMenuWidget) {
    ui->setupUi(this);

}

void IncidentMenuWidget::clear() {
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

void IncidentMenuWidget::addcIncidentWidget(IncidentWidget * widget) {
    //FIXME: Починить баг отображения. Не скролятся виджеты!
    this->ui->scrollAreaWidgetContents->layout()->addWidget(widget);
}

IncidentMenuWidget::~IncidentMenuWidget() {
    delete ui;
}
