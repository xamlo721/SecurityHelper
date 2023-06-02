#include <QApplication>

#include "src/controllers/MainWindowController.h"
#include "src/logic/Database.h"
#include "src/logic/XMLHelper.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QList<SecurityEventCategory> categories;

    QList<int> incidents;
    categories.append(SecurityEventCategory(0, "Я категория", incidents ));
    categories.append(SecurityEventCategory(1, "Я категория", incidents ));
    categories.append(SecurityEventCategory(2, "Я категория", incidents ));
    categories.append(SecurityEventCategory(3, "Я категория", incidents ));
    categories.append(SecurityEventCategory(4, "Я категория", incidents ));

    Database db = XMLHelper::readDatabase("C:/workspace/SecurityHelper/storage/");


    MainWindowController c;
    c.init();
    c.show();
    return a.exec();
}
