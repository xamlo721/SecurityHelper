#ifndef USERCATEGORYEVENTWIDGETCONTROLLER_H
#define USERCATEGORYEVENTWIDGETCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEventCategory.h"
#include "src/items/SecurityEvent.h"

#include "src/ui/user/MainMenuWidget.h"

class UserEventsController : public QObject {

    Q_OBJECT

    public:
        explicit UserEventsController(QObject *parent = nullptr);

        void init(MainMenuWidget *menuWidget);

    public slots:
        void setCategoryList(QMap<quint32, SecurityEventCategory> categories);
        void setEventList(QMap<quint32, SecurityEvent> events);

        void onCalculateIncident();

        void clearWidget();

    private:
        MainMenuWidget *mainMenuWidget;
        QMap<quint32, SecurityEventCategory> categories;
        QMap<quint32, SecurityEvent> allEvents;
        QList<SecurityEvent> availableEvents;
        QList<SecurityEvent> selectedEvents;

    private slots:
        void onCetegorySelected(quint32 categoryID);
        void onEventSelected(quint32 eventID);
        void onEventUnselected(quint32 eventID);

    signals:
        void signalOpenCategory(quint32 id, const bool isForAdminMode = false);
        void signalCalculateIncident(QList<SecurityEvent> selectedEvents);

};

#endif // USERCATEGORYEVENTWIDGETCONTROLLER_H
