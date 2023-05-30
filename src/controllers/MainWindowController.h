#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

#include "src/ui/MainWindow.h"
#include "src/ui/MainMenu.h"
#include "src/ui/EventWidget.h"
#include "src/ui/Incident.h"
#include "src/ui/Recommendations.h"
#include "src/ui/Scenario.h"

class MainWindowController : public QObject {

    Q_OBJECT

    public:
        explicit MainWindowController(QObject *parent = nullptr);

        void init();

        void show();

        void shutdown();

        ~MainWindowController();

    private:
        MainWindow * w;

    signals:

};

#endif // MAINWINDOWCONTROLLER_H
