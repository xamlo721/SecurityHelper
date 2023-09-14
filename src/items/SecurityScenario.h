#ifndef SECURITYSCENARIO_H
#define SECURITYSCENARIO_H

#include <QObject>
#include <QList>

class SecurityScenario : public QObject {

    Q_OBJECT

    public:
        explicit SecurityScenario(quint32 id, QString text, QList<quint32> incidents, QObject *parent = nullptr);
        SecurityScenario(const SecurityScenario& other);

        SecurityScenario& operator=(const SecurityScenario& other);
        bool operator==(const SecurityScenario& other) const;
        bool operator!=(const SecurityScenario& other) const;
        bool operator<(const SecurityScenario& other) const;
        bool operator>(const SecurityScenario& other) const;

        quint32 getId();
        QString getText();
        QList<quint32> getIncidents();

    private:
        quint32 id;
        QString text;
        QList<quint32> incidents;

    signals:

};

#endif // SECURITYSCENARIO_H
