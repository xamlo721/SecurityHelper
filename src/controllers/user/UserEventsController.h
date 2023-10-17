#ifndef USERCATEGORYEVENTWIDGETCONTROLLER_H
#define USERCATEGORYEVENTWIDGETCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEventCategory.h"
#include "src/items/SecurityEvent.h"

#include "src/logic/Database.h"

#include "src/ui/user/MainMenuWidget.h"

class UserEventsController : public QObject {

    Q_OBJECT

    private:
        MainMenuWidget *mainMenuWidget;
        QMap<quint32, SecurityEventCategory> categories;
        QMap<quint32, SecurityEvent> allEvents;
        QList<SecurityEvent> availableEvents;
        QList<SecurityEvent> selectedEvents;

    public:
        UserEventsController(QObject *parent = nullptr);

        void init(MainMenuWidget *menuWidget);

    public slots:
        void onDatabaseUpdated(const Database & db);

        void resetWidget();


    private slots:
        void onCetegorySelected(quint32 categoryID);
        void onEventSelected(quint32 eventID);
        void onEventUnselected(quint32 eventID);

};

#endif // USERCATEGORYEVENTWIDGETCONTROLLER_H
