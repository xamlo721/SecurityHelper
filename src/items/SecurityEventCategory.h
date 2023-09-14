#ifndef SECURITY_EVENT_CATEGORY_H
#define SECURITY_EVENT_CATEGORY_H

#include <QObject>

class SecurityEventCategory : public QObject {

    Q_OBJECT

    public:
        explicit SecurityEventCategory(quint32 id, QString text, QList<quint32> incidentes, QObject *parent = nullptr);
        SecurityEventCategory() {};

        SecurityEventCategory(const SecurityEventCategory& other);

        SecurityEventCategory& operator=(const SecurityEventCategory& other);
        bool operator==(const SecurityEventCategory& other) const;
        bool operator!=(const SecurityEventCategory& other) const;
        bool operator<(const SecurityEventCategory& other) const;
        bool operator>(const SecurityEventCategory& other) const;

        quint32 getId();
        QString getText();
        QList<quint32> getEventIds();

    private:
        quint32 id;
        QString text;
        QList<quint32> events;

    signals:

};

#endif // SECURITY_EVENT_CATEGORY_H
