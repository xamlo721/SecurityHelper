#ifndef SECURITYEVENT_H
#define SECURITYEVENT_H

#include <QObject>

class SecurityEvent : public QObject {

    Q_OBJECT

    public:
        explicit SecurityEvent(int id, QString text, QObject *parent = nullptr);
        SecurityEvent(const SecurityEvent& other);
        SecurityEvent() {}
        SecurityEvent& operator=(const SecurityEvent& other);
        bool operator==(const SecurityEvent& other) const;
        bool operator!=(const SecurityEvent& other) const;
        bool operator<(const SecurityEvent& other) const;
        bool operator>(const SecurityEvent& other) const;

        int getId();
        QString getText();

    private:
        int id;
        QString text;

    signals:

};

#endif // SECURITYEVENT_H
