#ifndef SECURITYRECOMMENDATIONS_H
#define SECURITYRECOMMENDATIONS_H

#include <QObject>

class SecurityRecommendations : public QObject {

    Q_OBJECT

    public:
        explicit SecurityRecommendations(int id, QString textContainment, QString textFixes, QString textRestore, QList<int> scenaries, QObject *parent = nullptr);
        SecurityRecommendations(const SecurityRecommendations& other);

        SecurityRecommendations& operator=(const SecurityRecommendations& other);
        bool operator==(const SecurityRecommendations& other) const;
        bool operator!=(const SecurityRecommendations& other) const;
        bool operator<(const SecurityRecommendations& other) const;
        bool operator>(const SecurityRecommendations& other) const;

        int getId();
        QString getTextContainment();
        QString getTextFixes();
        QString getTextRestore();
        QList<int> getScenaries();

    private:
        int id;
        QString textContainment;
        QString textFixes;
        QString textRestore;
        QList<int> scenaries;

    signals:

};

#endif // SECURITYRECOMMENDATIONS_H
