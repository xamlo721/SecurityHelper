#ifndef ILLEGALARGUMENTEXCEPTION_H
#define ILLEGALARGUMENTEXCEPTION_H

#include <QObject>

#include "src/exception/Exception.h"

/**
 * @brief The IllegalArgumentExcetion class - исключение бросается,
 * когда происходит вызов функции с некоректными значениями аргументов
 */
class IllegalArgumentExcetion : public Exception {

    public:
        /**
         * @brief IllegalArgumentExcetion
         */
        IllegalArgumentExcetion() : Exception("IllegalArgumentExcetion") {
            //NO-OP
        }

        /**
         * @brief IllegalArgumentExcetion
         */
        IllegalArgumentExcetion(QString message) : Exception(message) {
            //NO-OP
        }

        /**
         * @brief getExceptionName - метод для получения строкового имени исключения
         * @return Имя исключения
         */
        virtual QString getExceptionName() override {
            return "IllegalArgumentExcetion";
        }

};

#endif // ILLEGALARGUMENTEXCEPTION_H
