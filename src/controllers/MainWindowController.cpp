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

    QObject::connect(this->w, &MainWindow::signalUndoButtonPressed, this, &MainWindowController::onUndoButtonPressed);
    QObject::connect(this->w, &MainWindow::signalRedoButtonPressed, this, &MainWindowController::onRedoButtonPressed);
    QObject::connect(this->w, &MainWindow::signalResetEditButtonPressed, this, &MainWindowController::onResetEditButtonPressed);
    QObject::connect(this->w, &MainWindow::signalEditButtonPressed, this, &MainWindowController::onEditButtonPressed);
    QObject::connect(this->w, &MainWindow::signalBackButtonPressed, this, &MainWindowController::onBackButtonPressed);

    QObject::connect(this->w, &MainWindow::signalAddCategoryButtonPressed, this, &MainWindowController::onAddCategoryButtonPressed);
    QObject::connect(this->w, &MainWindow::signalDeleteCategoriesButtonPressed, this, &MainWindowController::onDeleteCategoriesButtonPressed);

    QObject::connect(this->w, &MainWindow::signalAddEventButtonPressed, this, &MainWindowController::onAddEventButtonPressed);
    QObject::connect(this->w, &MainWindow::signalDeleteEventButtonPressed, this, &MainWindowController::onDeleteEventsButtonPressed);


    w->openUserMainMenu();
    w->openUserToolbar();

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

        TODO №2.5: добавить на тулбар админа кнопки:
    д) сохранить ( сохранить изменения );

        TODO №4: добавить отслеживание активного меню.

    */
    w->openAdminToolbar();
    w->openAdminMainMenu();
}

void MainWindowController::onResetButtonPressed() {
    this->availableEvents.clear();
    this->activeEvents.clear();
    this->w->clearCategoryEventList();
    this->w->clearSelectedEventList();
    this->w->openUserMainMenu();

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

void MainWindowController::onUndoButtonPressed() {

}

void MainWindowController::onRedoButtonPressed() {

}

void MainWindowController::onResetEditButtonPressed() {

}

void MainWindowController::onEditButtonPressed() {
    // замена item-ов на редактируемые
}

void MainWindowController::onAddCategoryButtonPressed() {
    // тут должен отправляться сигнал в ядро о добавлении в лист новой категории или этот лист должен быть в самом контроллере???
}

void MainWindowController::onDeleteCategoriesButtonPressed() {

}

void MainWindowController::onAddEventButtonPressed() {

}

void MainWindowController::onDeleteEventsButtonPressed() {

}

void MainWindowController::onBackButtonPressed() {
    this->setCategoryList(this->categories);
    this->setEventList(this->availableEvents);

    w->openUserMainMenu();
    w->openUserToolbar();
}

MainWindowController::~MainWindowController() {
    this->shutdown();
}
