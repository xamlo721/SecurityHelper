#ifndef USERCATEGORYEVENTWIDGETCONTROLLER_H
#define USERCATEGORYEVENTWIDGETCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEventCategory.h"
#include "src/items/SecurityEvent.h"

#include "src/ui/user/MainMenuWidget.h"

class UserCategoryEventWidgetController : public QObject {

    Q_OBJECT

    public:
        explicit UserCategoryEventWidgetController(QObject *parent = nullptr);

        void init(MainMenuWidget *menuWidget);

    public slots:
        void setCategoryList(QList<SecurityEventCategory> categories);
        void setEventList(QList<SecurityEvent> events);

        void onCalculateIncident();

        void clearWidget();

    private:
        MainMenuWidget *mainMenuWidget;
        QList<SecurityEventCategory> categories;
        QList<SecurityEvent> availableEvents;
        QList<SecurityEvent> activeEvents;

    private slots:
        void onEventSelected(quint32 eventID);
        void onEventUnselected(quint32 eventID);

    signals:
        void signalOpenCategory(quint32 id, const bool isForAdminMode = false);
        void signalCalculateIncident(QList<SecurityEvent> activeEvents);

};

#endif // USERCATEGORYEVENTWIDGETCONTROLLER_H
