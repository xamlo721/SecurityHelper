#include <QApplication>

#include "src/controllers/MainWindowController.h"
#include "src/logic/Database.h"
#include "src/logic/XMLHelper.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Database db = XMLHelper::readDatabase("../SecurityHelper/storage/");


    MainWindowController c;
    c.init();
    c.setCategoryList(db.categories.values());
    c.show();
    return a.exec();
}
