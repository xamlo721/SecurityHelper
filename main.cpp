#include "MainWindow.h"

#include <QApplication>
#include <QDesktopWidget>

#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
