#ifndef SECURITYINCIDENT_H
#define SECURITYINCIDENT_H

#include <QObject>

class SecurityIncident : public QObject {

    Q_OBJECT

    public:
        explicit SecurityIncident(quint32 id, QString text, QList<quint32> events, QObject *parent = nullptr);
        SecurityIncident(const SecurityIncident& other);

        SecurityIncident& operator=(const SecurityIncident& other);
        bool operator==(const SecurityIncident& other) const;
        bool operator!=(const SecurityIncident& other) const;
        bool operator<(const SecurityIncident& other) const;
        bool operator>(const SecurityIncident& other) const;

        quint32 getId();
        QString getText();
        QList<quint32> getEventIds();

    private:
        quint32 id;
        QString text;
        QList<quint32> events;

    signals:

};

#endif // SECURITYINCIDENT_H
