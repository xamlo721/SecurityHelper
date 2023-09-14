#ifndef UNSUPPORTEDOPERATIONEXCEPTION_H
#define UNSUPPORTEDOPERATIONEXCEPTION_H

#include <QObject>

#include "src/exception/Exception.h"

/**
 * @brief The UnsupportedOperationException class - исключение бросается,
 * когда какая-то часть программы использует не реализрованные компоненты
 */
class UnsupportedOperationException : public Exception {

    public:
        /**
         * @brief UnsupportedOperationException
         */
        UnsupportedOperationException() : Exception("UnsupportedOperationException") {
            //NO-OP
        }

        /**
         * @brief UnsupportedOperationException
         */
        UnsupportedOperationException(QString message) : Exception(message) {
            //NO-OP
        }

        /**
         * @brief getExceptionName - метод для получения строкового имени исключения
         * @return Имя исключения
         */
        virtual QString getExceptionName() override {
            return "UnsupportedOperationException";
        }

};

#endif // UNSUPPORTEDOPERATIONEXCEPTION_H
