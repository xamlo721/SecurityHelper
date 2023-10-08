#ifndef SECURITYRECOMMENDATIONS_H
#define SECURITYRECOMMENDATIONS_H

#include <QObject>

/**
 * @brief The SecurityRecommendations class - Data-class, описывающий
 * понятие рекомендаций ИБ
 *
 * Рекомендации ИБ содержат текстовый набор инструкций трёх категорий
 * 1) сдерживание угрозы
 * 2) устранение угрозы
 * 3) восстановление системы
 */
class SecurityRecommendations : public QObject {

    Q_OBJECT

    private:
        ///Цифровой целочисленный ID для однозначной идентификации и учёта объекта
        quint32 id;
        ///Набор инструкций для сдерживания игрозы, задаваемый администратором
        QString textContainment;
        ///Набор инструкций для устранения угрозы, задаваемый администратором
        QString textFixes;
        ///Набор инструкций для восстановления системы, задаваемый администратором
        QString textRestore;
        ///Перечень SecurityScenario информационной безопасности, которые
        /// могут быть исправлены этими рекомендациями
        QList<quint32> scenaries;

    public:
        /**
         * @brief SecurityRecommendations - базовый конструктор по умолчанию
         * Он необходим для того, чтобы объект можно было хранить
         * в контейнерах Qlist, QMap и т.д
         */
        SecurityRecommendations();

        /**
         * @brief SecurityRecommendations - конструктор копирования объектов
         * @param other - объект, используемый как источник данных
         */
        SecurityRecommendations(const SecurityRecommendations& other);
        /**
         * @brief SecurityRecommendations
         * @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
         * @param textContainment - Набор инструкций для сдерживания игрозы, задаваемый администратором
         * @param textFixes - Набор инструкций для устранения угрозы, задаваемый администратором
         * @param textRestore - Набор инструкций для восстановления системы, задаваемый администратором
         * @param scenaries - Перечень SecurityScenario информационной безопасности, которые
         * могут быть исправлены этими рекомендациями
         * @param parent - родительский объект в иерархии Qt.
         */
        SecurityRecommendations(quint32 id, QString textContainment, QString textFixes, QString textRestore, QList<quint32> scenaries, QObject *parent = nullptr);

        /**
         * @brief getId - получить ID рекомендации
         * @return
         */
        quint32 getId();

        /**
         * @brief getTextContainment - получить текст рекомендации для сдерживания
         * @return
         */
        QString getTextContainment();

        /**
         * @brief getTextFixes - получить текст рекомендации для устранения
         * @return
         */
        QString getTextFixes();

        /**
         * @brief getTextRestore - получить текст рекомендации для восстановления
         * @return
         */
        QString getTextRestore();

        /**
         * @brief getScenaries - получить перечень возможных сценариев
         * @return
         */
        QList<quint32> getScenaries();

        /**
         * @brief setId - установить ID рекомендации
         * @return
         */
        void setId(quint32 const id);

        /**
         * @brief setTextContainment - установить текст рекомендации для сдерживания
         * @return
         */
        void setTextContainment(QString const textContainment);

        /**
         * @brief setTextFixes - установить текст рекомендации для устранения
         * @return
         */
        void setTextFixes(QString const textFixes);

        /**
         * @brief setTextRestore - установить текст рекомендации для восстановления
         * @return
         */
        void setTextRestore(QString const textRestore);

        /**
         * @brief setScenaries - установить перечень возможных сценариев
         * @return
         */
        void setScenaries(QList<quint32> const scenaries);

        /**
         * @brief operator =
         * @param other
         * @return
         */
        SecurityRecommendations& operator=(const SecurityRecommendations& other);

        /**
         * @brief operator ==
         * @param other
         * @return
         */
        bool operator==(const SecurityRecommendations& other) const;

        /**
         * @brief operator !=
         * @param other
         * @return
         */
        bool operator!=(const SecurityRecommendations& other) const;

        /**
         * @brief operator <
         * @param other
         * @return
         */
        bool operator<(const SecurityRecommendations& other) const;

        /**
         * @brief operator >
         * @param other
         * @return
         */
        bool operator>(const SecurityRecommendations& other) const;

        /**
         * @brief operator >=
         * @param other
         * @return
         */
        bool operator>=(const SecurityRecommendations& other) const;

        /**
         * @brief operator <=
         * @param other
         * @return
         */
        bool operator<=(const SecurityRecommendations& other) const;



};

#endif // SECURITYRECOMMENDATIONS_H
