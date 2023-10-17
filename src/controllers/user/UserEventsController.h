#ifndef USERCATEGORYEVENTWIDGETCONTROLLER_H
#define USERCATEGORYEVENTWIDGETCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEventCategory.h"
#include "src/items/SecurityEvent.h"

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
        void setCategoryList(QMap<quint32, SecurityEventCategory> categories);
        void setEventList(QMap<quint32, SecurityEvent> events);

        void resetWidget();


    private slots:
        void onCetegorySelected(quint32 categoryID);
        void onEventSelected(quint32 eventID);
        void onEventUnselected(quint32 eventID);

};

#endif // USERCATEGORYEVENTWIDGETCONTROLLER_H
