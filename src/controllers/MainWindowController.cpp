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



void MainWindowController::shutdown() {
    delete w;
}


void MainWindowController::onAdminButtonPressed() {
    /*
        TODO №1: создать класс Interface для управления контроллерами и разбить MainWindowController на несколько контроллеров.

        TODO №2: реализовать виджет с кнопками режима админа:
    a) редактировать ( редактировать только тот этап, на котором была нажата кнопка, второе её нажатие должно отменить режим редактирования);
    б) отменить ( отмена последнего действия, возможность откатить несколько действий );
    в) повторить ( возврат последнего действия, возможность вернуть несколько действий );
    г) сбросить ( сброс до состояния, в котором была дб при входе );
    д) сохранить ( сохранить изменения );
    е) назад ( возвращение к MainWindow ).
    */
    this->setAdminCategoryList(this->categories);
    this->setAdminEventList(this->availableEvents);
}

void MainWindowController::onResetButtonPressed() {
    this->availableEvents.clear();
    this->activeEvents.clear();
    this->w->clearCategoryEventList();
    this->w->clearSelectedEventList();
    this->w->openMainMenu();

}

void MainWindowController::onIncidentsButtonPressed() {
    emit signalCalculateIncident(this->activeEvents);
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
