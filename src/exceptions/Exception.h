#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QObject>

/**
 * @brief The Exception class - родительский класс, для всех исключений проекта
 */
class Exception {


    protected:

        QString message;

    public:

        /**
         * @brief Exception
         */
        Exception() {
            this->message = "Exception";
        }

        /**
         * @brief Exception
         */
        Exception(QString message) {
            this->message = message;
        }

        /**
         * @brief getExceptionName - метод для получения строкового имени исключения
         * @return Имя исключения
         */
        virtual QString getExceptionName() = 0;


        virtual QString getMessage() {
            return this->message;
        }
};

#endif // EXCEPTION_H
