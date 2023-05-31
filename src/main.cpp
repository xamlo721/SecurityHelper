#include <QApplication>

#include "src/controllers/MainWindowController.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QList<IncidentCategory> categories;

    QList<int> incidents;
    categories.append(IncidentCategory(0, "Я категория", incidents ));
    categories.append(IncidentCategory(1, "Я категория", incidents ));
    categories.append(IncidentCategory(2, "Я категория", incidents ));
    categories.append(IncidentCategory(3, "Я категория", incidents ));
    categories.append(IncidentCategory(4, "Я категория", incidents ));

    MainWindowController c;
    c.init();
    c.show();
    return a.exec();
}
