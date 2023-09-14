#ifndef PARSINGEXCEPTION_H
#define PARSINGEXCEPTION_H

#include <QObject>

#include "src/exception/Exception.h"

/**
 * @brief The ParsingException class - исключение бросается,
 * когда происходит нарушения порядка парсинга данных по структуре
 */
class ParsingException : public Exception {

    public:
        /**
         * @brief ObjectNotFoundException
         */
        ParsingException() : Exception("ParsingException") {
            //NO-OP
        }

        /**
         * @brief ObjectNotFoundException
         */
        ParsingException(QString message) : Exception(message) {
            //NO-OP
        }

        /**
         * @brief getExceptionName - метод для получения строкового имени исключения
         * @return Имя исключения
         */
        virtual QString getExceptionName() override {
            return "ParsingException";
        }

};
#endif // PARSINGEXCEPTION_H
