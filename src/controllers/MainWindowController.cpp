#include "MainWindowController.h"

MainWindowController::MainWindowController(QObject *parent) : QObject(parent) {

}


void MainWindowController::init() {
    w = new MainWindow();
    QObject::connect(this->w, &MainWindow::signalAdminButtonPressed, this, &MainWindowController::onAdminButtonPressed);
    QObject::connect(this->w, &MainWindow::signalResetButtonPressed, this, &MainWindowController::onResetButtonPressed);
    QObject::connect(this->w, &MainWindow::signalIncidentsButtonPressed, this, &MainWindowController::onIncidentsButtonPressed);
    QObject::connect(this->w, &MainWindow::signalSettingsButtonPressed, this, &MainWindowController::onSettingsButtonPressed);
    QObject::connect(this->w, &MainWindow::signalExitButtonPressed, this, &MainWindowController::onExitButtonPressed);


    w->openMainMenu();

}

void MainWindowController::show() {
    w->showMaximized();
}

void MainWindowController::setCategoryList(QList<SecurityEventCategory> categories) {
    this->categories = categories;
    this->w->clearCategoryList();
    for (SecurityEventCategory cat : categories) {
        EventCategoryWidget * categoryWidget = new EventCategoryWidget(cat.getId(), cat.getText());
        QObject::connect(categoryWidget, &EventCategoryWidget::signalOpenIncident, this, &MainWindowController::signalOpenCategory);

        this->w->addCategory(categoryWidget);
    }
}

void MainWindowController::setEventList(QList<SecurityEvent> events) {
    this->availableEvents = events;

    //TODO: Вычесть те, которые уже отображены
    this->w->clearCategoryEventList();

    for (SecurityEvent event : events) {
        EventWidget * eventWidget = new EventWidget(event.getId(), event.getText(), false);
        QObject::connect(eventWidget, &EventWidget::signalEventSelected, this, &MainWindowController::onEventSelected);

        this->w->addCategoryEvent(eventWidget);
    }

}
void MainWindowController::onEventSelected(int eventID) {

    ///1) Найти и переложить событие

    //TODO: Проверка, что он его вообще содержит!
    for (int i = 0; i < availableEvents.size(); i++) {
        SecurityEvent event = availableEvents.at(i);
        if (event.getId() == eventID) {
            this->activeEvents.append(availableEvents.takeAt(i));
        }
    }

    ///2) Почистить доступные ивенты от него

    //TODO: Вычесть те, которые уже отображены
    this->w->clearCategoryEventList();
    for (SecurityEvent event : availableEvents) {
        EventWidget * eventWidget = new EventWidget(event.getId(), event.getText(), false);
        QObject::connect(eventWidget, &EventWidget::signalEventSelected, this, &MainWindowController::onEventSelected);
        this->w->addCategoryEvent(eventWidget);
    }

    ///3) обновить выбранные ивенты
    this->w->clearSelectedEventList();
    for (SecurityEvent event : activeEvents) {
        EventWidget * eventWidget = new EventWidget(event.getId(), event.getText(), true);
        QObject::connect(eventWidget, &EventWidget::signalEventSelected, this, &MainWindowController::onEventUnselected);
        this->w->addSelectedEvent(eventWidget);
    }


}

void MainWindowController::onEventUnselected(int eventID) {

    ///1) Найти и переложить событие

    //TODO: Проверка, что он его вообще содержит!
    for (int i = 0; i < activeEvents.size(); i++) {
        SecurityEvent event = activeEvents.at(i);
        if (event.getId() == eventID) {
            this->availableEvents.append(activeEvents.takeAt(i));
        }
    }


    ///2) Почистить доступные ивенты от него

    //TODO: Вычесть те, которые уже отображены
    this->w->clearCategoryEventList();
    for (SecurityEvent event : availableEvents) {
        EventWidget * eventWidget = new EventWidget(event.getId(), event.getText(), false);
        QObject::connect(eventWidget, &EventWidget::signalEventSelected, this, &MainWindowController::onEventSelected);
        this->w->addCategoryEvent(eventWidget);
    }


    ///3) обновить выбранные ивенты
    this->w->clearSelectedEventList();
    for (SecurityEvent event : activeEvents) {
        EventWidget * eventWidget = new EventWidget(event.getId(), event.getText(), true);
        QObject::connect(eventWidget, &EventWidget::signalEventSelected, this, &MainWindowController::onEventUnselected);
        this->w->addSelectedEvent(eventWidget);
    }


}


void MainWindowController::shutdown() {
    delete w;
}


void MainWindowController::onAdminButtonPressed() {

}

void MainWindowController::onResetButtonPressed() {

}

void MainWindowController::onIncidentsButtonPressed() {
    emit signalOpenIncident(this->activeEvents);
    this->w->openIncidentMenu();

}

void MainWindowController::onSettingsButtonPressed() {

}

void MainWindowController::onExitButtonPressed() {
    this->w->close();

}


MainWindowController::~MainWindowController() {
    this->shutdown();
}
