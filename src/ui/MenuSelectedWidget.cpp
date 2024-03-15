#include "MenuSelectedWidget.h"
#include "ui_MenuSelectedWidget.h"

MenuSelectedWidget::MenuSelectedWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MenuSelectedWidget) {
    ui->setupUi(this);
    this->selectedID = -1;

    QVBoxLayout*  menuLayout = new QVBoxLayout();
    ui->scrollArea_selectedWidgets->widget()->setLayout(menuLayout);
    menuLayout->setAlignment(Qt::AlignTop);
}

void MenuSelectedWidget::addWidgets(QList<SelectedWidget *> widgets) {
    for (SelectedWidget * w : widgets) {
        this->widgets.insert(w->getId(), w);
        this->ui->scrollArea_selectedWidgets->widget()->layout()->addWidget(w);
        QObject::connect(w, &SelectedWidget::signalSelected, this, &MenuSelectedWidget::onWidgetSelected);
        QObject::connect(w, &SelectedWidget::signalUnselected, this, &MenuSelectedWidget::onWidgetUnselected);
    }
}


void MenuSelectedWidget::addWidget(qint32 widgetID,  SelectedWidget * widget) {
    this->widgets.insert(widgetID, widget);
    this->ui->scrollArea_selectedWidgets->widget()->layout()->addWidget(widget);
    QObject::connect(widget, &SelectedWidget::signalSelected, this, &MenuSelectedWidget::onWidgetSelected);
    QObject::connect(widget, &SelectedWidget::signalUnselected, this, &MenuSelectedWidget::onWidgetUnselected);
}

SelectedWidget * MenuSelectedWidget::getSelectedWidget() {
    return this->widgets.values().at(this->selectedID);
}

quint32 MenuSelectedWidget::getSelectedWidgetID() {
    return this->selectedID;
}


void MenuSelectedWidget::removeWidget(qint32 widgetID) {
    //TODO: вынуть из виджета

    SelectedWidget * widget = this->widgets.values().at(widgetID);
    this->widgets.remove(widgetID);

    QObject::disconnect(widget, &SelectedWidget::signalSelected, this, &MenuSelectedWidget::onWidgetSelected);
    QObject::disconnect(widget, &SelectedWidget::signalUnselected, this, &MenuSelectedWidget::onWidgetUnselected);


    QWidget * m_view = this->ui->scrollArea_selectedWidgets->widget();
    if ( m_view->layout() != NULL ) {
        QLayoutItem* item;
        for (int i = 0; i < m_view->layout()->count(); i++) {

        }
        while ( ( item = m_view->layout()->takeAt( 0 ) ) != NULL ) {
            //TODO: disconnect
            delete item->widget();
            delete item;
        }
        //delete m_view->layout();
    }
}

void MenuSelectedWidget::unselect() {
    this->selectedID = -1;

    for (SelectedWidget * w : this->widgets) {
        w->unselect();
    }
}


void MenuSelectedWidget::clear() {
    QWidget * m_view = this->ui->scrollArea_selectedWidgets->widget();
    if ( m_view->layout() != NULL ) {
        QLayoutItem* item;
        while ( ( item = m_view->layout()->takeAt( 0 ) ) != NULL ) {
            //TODO: disconnect
            delete item->widget();
            delete item;
        }
        //delete m_view->layout();
    }
}

void MenuSelectedWidget::onWidgetSelected(qint32 widgetID) {
    this->selectedID = widgetID;

    for (SelectedWidget * w : this->widgets) {
        if (w->getId() != widgetID) {
            w->unselect();
        }
    }
    emit signalOnWidgetSelected(widgetID);

}

void MenuSelectedWidget::onWidgetUnselected(qint32 widgetID) {
    this->selectedID = -1;
    emit signalOnWidgetUnselected(widgetID);
}

MenuSelectedWidget::~MenuSelectedWidget() {
    delete ui;
}
