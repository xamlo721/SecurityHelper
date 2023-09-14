#ifndef SECURITYRECOMMENDATIONS_H
#define SECURITYRECOMMENDATIONS_H

#include <QObject>

class SecurityRecommendations : public QObject {

    Q_OBJECT

    public:
        explicit SecurityRecommendations(quint32 id, QString textContainment, QString textFixes, QString textRestore, QList<quint32> scenaries, QObject *parent = nullptr);
        SecurityRecommendations(const SecurityRecommendations& other);

        SecurityRecommendations& operator=(const SecurityRecommendations& other);
        bool operator==(const SecurityRecommendations& other) const;
        bool operator!=(const SecurityRecommendations& other) const;
        bool operator<(const SecurityRecommendations& other) const;
        bool operator>(const SecurityRecommendations& other) const;

        quint32 getId();
        QString getTextContainment();
        QString getTextFixes();
        QString getTextRestore();
        QList<quint32> getScenaries();

    private:
        quint32 id;
        QString textContainment;
        QString textFixes;
        QString textRestore;
        QList<quint32> scenaries;

    signals:

};

#endif // SECURITYRECOMMENDATIONS_H
