#ifndef INCIDENTCATEGORY_H
#define INCIDENTCATEGORY_H

#include <QObject>

class IncidentCategory : public QObject {

    Q_OBJECT

    public:
        explicit IncidentCategory(int id, QString text, QList<int> incidentes, QObject *parent = nullptr);

        IncidentCategory(const IncidentCategory& other);

        IncidentCategory& operator=(const IncidentCategory& other);
        bool operator==(const IncidentCategory& other) const;
        bool operator!=(const IncidentCategory& other) const;
        bool operator<(const IncidentCategory& other) const;
        bool operator>(const IncidentCategory& other) const;

        int getId();
        QString getText();
        QList<int> getIncidentesId();

    private:
        int id;
        QString text;
        QList<int> incidentes;

    signals:

};

#endif // INCIDENTCATEGORY_H
