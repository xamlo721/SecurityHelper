#ifndef SECURITYSCENARIO_H
#define SECURITYSCENARIO_H

#include <QObject>

class SecurityScenario : public QObject {

    Q_OBJECT

    public:
        explicit SecurityScenario(int id, QString text, QObject *parent = nullptr);
        SecurityScenario(const SecurityScenario& other);

        SecurityScenario& operator=(const SecurityScenario& other);
        bool operator==(const SecurityScenario& other) const;
        bool operator!=(const SecurityScenario& other) const;
        bool operator<(const SecurityScenario& other) const;
        bool operator>(const SecurityScenario& other) const;

        int getId();
        QString getText();

    private:
        int id;
        QString text;

    signals:

};

#endif // SECURITYSCENARIO_H
