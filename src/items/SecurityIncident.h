#ifndef SECURITYINCIDENT_H
#define SECURITYINCIDENT_H

#include <QObject>

class SecurityIncident : public QObject {

    Q_OBJECT

    public:
        explicit SecurityIncident(int id, QString text, QList<int> events, QObject *parent = nullptr);
        SecurityIncident(const SecurityIncident& other);

        SecurityIncident& operator=(const SecurityIncident& other);
        bool operator==(const SecurityIncident& other) const;
        bool operator!=(const SecurityIncident& other) const;
        bool operator<(const SecurityIncident& other) const;
        bool operator>(const SecurityIncident& other) const;

        int getId();
        QString getText();
        QList<int> getEventIds();

    private:
        int id;
        QString text;
        QList<int> events;

    signals:

};

#endif // SECURITYINCIDENT_H
