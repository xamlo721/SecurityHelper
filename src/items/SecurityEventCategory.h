#ifndef SECURITY_EVENT_CATEGORY_H
#define SECURITY_EVENT_CATEGORY_H

#include <QObject>

class SecurityEventCategory : public QObject {

    Q_OBJECT

    public:
        explicit SecurityEventCategory(int id, QString text, QList<int> incidentes, QObject *parent = nullptr);

        SecurityEventCategory(const SecurityEventCategory& other);

        SecurityEventCategory& operator=(const SecurityEventCategory& other);
        bool operator==(const SecurityEventCategory& other) const;
        bool operator!=(const SecurityEventCategory& other) const;
        bool operator<(const SecurityEventCategory& other) const;
        bool operator>(const SecurityEventCategory& other) const;

        int getId();
        QString getText();
        QList<int> getEventIds();

    private:
        int id;
        QString text;
        QList<int> events;

    signals:

};

#endif // SECURITY_EVENT_CATEGORY_H
