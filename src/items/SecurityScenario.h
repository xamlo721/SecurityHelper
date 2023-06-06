#ifndef SECURITYSCENARIO_H
#define SECURITYSCENARIO_H

#include <QObject>
#include <QList>

class SecurityScenario : public QObject {

    Q_OBJECT

    public:
        explicit SecurityScenario(int id, QString text, QList<int> incidents, QObject *parent = nullptr);
        SecurityScenario(const SecurityScenario& other);

        SecurityScenario& operator=(const SecurityScenario& other);
        bool operator==(const SecurityScenario& other) const;
        bool operator!=(const SecurityScenario& other) const;
        bool operator<(const SecurityScenario& other) const;
        bool operator>(const SecurityScenario& other) const;

        int getId();
        QString getText();
        QList<int> getIncidents();

    private:
        int id;
        QString text;
        QList<int> incidents;

    signals:

};

#endif // SECURITYSCENARIO_H
