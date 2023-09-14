#ifndef FILEOPERATIONEXCEPTION_H
#define FILEOPERATIONEXCEPTION_H

#include <QObject>

#include "src/exception/Exception.h"

/**
 * @brief The FileOperationException class - исключение бросается,
 * когда происходит какая-либо проблема при работе с файлом
 */
class FileOperationException : public Exception {

    public:
        /**
         * @brief FileOperationException
         */
        FileOperationException() : Exception("FileOperationException") {
            //NO-OP
        }

        /**
         * @brief FileOperationException
         */
        FileOperationException(QString message) : Exception(message) {
            //NO-OP
        }

        /**
         * @brief getExceptionName - метод для получения строкового имени исключения
         * @return Имя исключения
         */
        virtual QString getExceptionName() override {
            return "FileOperationException";
        }

};


#endif // FILEOPERATIONEXCEPTION_H
