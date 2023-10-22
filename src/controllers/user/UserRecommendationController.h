#ifndef USERRECOMMENDATIONCONTROLLER_H
#define USERRECOMMENDATIONCONTROLLER_H

#include <QObject>
#include "src/ui/user/RecommendationsWidget.h"
#include "src/items/SecurityRecommendations.h"

class UserRecommendationController : public QObject {

    Q_OBJECT

    private:
        RecommendationsWidget *ui;

    public:
        UserRecommendationController(QObject *parent = nullptr);

        void init(RecommendationsWidget *recommendationWidget);

        void setRecommendation(SecurityRecommendations recommendation);

};

#endif // USERRECOMMENDATIONCONTROLLER_H
