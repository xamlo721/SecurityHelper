#ifndef USERCATEGORYEVENTWIDGETCONTROLLER_H
#define USERCATEGORYEVENTWIDGETCONTROLLER_H

#include <QObject>

class UserCategoryEventWidgetController : public QObject {

    Q_OBJECT

    public:
        explicit UserCategoryEventWidgetController(QObject *parent = nullptr);

    signals:

};

#endif // USERCATEGORYEVENTWIDGETCONTROLLER_H
