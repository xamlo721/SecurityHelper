#include <QApplication>

#include "src/controllers/MainWindowController.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindowController c;
    c.init();
    c.show();
    return a.exec();
}
