#ifndef XMLUTILS_H
#define XMLUTILS_H

#include <QObject>
#include <QXmlStreamReader>

#include <QtXml/QDomAttr>
#include <QtXml/QDomCDATASection>
#include <QtXml/QDomCharacterData>
#include <QtXml/QDomComment>
#include <QtXml/QDomDocument>
#include <QtXml/QDomDocumentFragment>
#include <QtXml/QDomDocumentType>
#include <QtXml/QDomElement>
#include <QtXml/QDomEntity>
#include <QtXml/QDomEntityReference>

/**
 * @brief XmlUtils class
 * Класс, для работой с XMLUtils для чтения и записи простых элементов в XML файл
 * Чтение и запись элементов, списков элементов, node
 **/

class XmlUtils : public QObject {

    Q_OBJECT

    public:
    /**
     * @brief checkFile - функция проверки файла для чтения
     * @param databasePath - путь xml-файла
     **/
    static bool checkFile(QString databasePath);

    /**
     * @brief read *TYPE* - блок функций чтения записей по тэгу
     * @param element - элемент дерева, из которого требуется считать запись
     * @param searchElementName - тэг, элемент для поиска соответсвующей записи
     **/
    static qint8 readChar(QDomElement element, QString searchElementName);

    static quint8 readUChar(QDomElement element, QString searchElementName);

    static qint16 readShort(QDomElement element, QString searchElementName);

    static quint16 readUShort(QDomElement element, QString searchElementName);

    static qint32 readint(QDomElement element, QString searchElementName);

    static quint32 readUint(QDomElement element, QString searchElementName);

    static quint64 readLong(QDomElement element, QString searchElementName);//Кажется quint64 на многих платформах 32

    static quint64 readULong(QDomElement element, QString searchElementName);

    static QString readText(QDomElement element, QString searchElementName);

    static QList<qint8> readChars(QDomElement element, QString searchElementName);

    static QList<quint8> readUChars(QDomElement element, QString searchElementName);

    static QList<qint16> readShorts(QDomElement element, QString searchElementName);

    static QList<quint16> readUShorts(QDomElement element, QString searchElementName);

    static QList<qint32> readints(QDomElement element, QString searchElementName);

    static QList<quint32> readUints(QDomElement element, QString searchElementName);

    static QList<quint64> readLongs(QDomElement element, QString searchElementName);//Кажется quint64 на многих платформах 32

    static QList<quint64> readULongs(QDomElement element, QString searchElementName);

    static QList<QString> readTexts(QDomElement element, QString searchElementName);


    /**
     * @brief write *TYPE* - блок функций чтения записей по тэгу
     * @param domDocument - dom документ xml-файла, в который пишется всё
     * @param element - элемент дерева, в которого будет производится запись
     * @param newElementName - название нового элемента
     * @param value - значение нового элемента
     **/

    static void writeChar(QDomDocument domDocument, QDomElement element, QString newElementName, qint8 value);

    static void writeUChar(QDomDocument domDocument, QDomElement element, QString newElementName, quint8 value);

    static void writeShort(QDomDocument domDocument, QDomElement element, QString newElementName, qint16 value);

    static void writeUShort(QDomDocument domDocument, QDomElement element, QString newElementName, quint16 value);

    static void writeint(QDomDocument domDocument, QDomElement element, QString newElementName, qint32 value);

    static void writeUint(QDomDocument domDocument, QDomElement element, QString newElementName, quint32 value);

    static void writeLong(QDomDocument domDocument, QDomElement element, QString newElementName, quint64 value);//Кажется quint64 на многих платформах 32

    static void writeULong(QDomDocument domDocument, QDomElement element, QString newElementName, quint64 value);

    static void writeText(QDomDocument domDocument, QDomElement element, QString newElementName, QString value);

    static void writeChars(QDomDocument domDocument, QDomElement element, QString newElementName, QList<qint8> value);

    static void writeUChars(QDomDocument domDocument, QDomElement element, QString newElementName, QList<quint8> value);

    static void writeShorts(QDomDocument domDocument, QDomElement element, QString newElementName, QList<qint16> value);

    static void writeUShorts(QDomDocument domDocument, QDomElement element, QString newElementName, QList<quint16> value);

    static void writeInts(QDomDocument domDocument, QDomElement element, QString newElementName, QList<qint32> value);

    static void writeUints(QDomDocument domDocument, QDomElement element, QString newElementName, QList<quint32> value);

    static void writeLongs(QDomDocument domDocument, QDomElement element, QString newElementName, QList<quint64> value);//Кажется quint64 на многих платформах 32

    static void writeULongs(QDomDocument domDocument, QDomElement element, QString newElementName, QList<quint64> value);

    static void writeTexts(QDomDocument domDocument, QDomElement element, QString newchElementName, QList<QString> value);

    /**
     * @brief writeXMLHeader - функция добавления заголовка в документ
     * @param domDocument - документ
     **/
    static void writeXMLHeader(QDomDocument *domDocument);

    static QDomElement writeXMLStructTree(QDomDocument *domDocument, QString nameElement);

    /**
     * @brief searchSingleNode - функция проверяет наличие указанной node в элементе
     * @param element - элемент дерева, в котором будет осуществлен node
     * @param searchElementName - тэг, элемент для поиска соответсвующей node
     **/
    static bool checkSingleNode(QDomElement element, QString searchElementName);

    /**
     * @brief readSingleNode - функция чтения одной node по тэгу
     * @param element - элемент дерева, из которого требуется считать node
     * @param searchElementName - тэг, элемент для поиска соответсвующей node
     **/
    static QDomElement readSingleNode(QDomElement element, QString searchElementName);

    /**
     * @brief readMultiNode - функция чтения нескольких node по тэгу
     * @param element - элемент дерева, из которого требуется считать node
     * @param searchElementName - тэг, элемент для поиска соответсвующих node
     **/
    static QList<QDomElement> readMultiNode(QDomElement element, QString searchElementName);

};

#endif // XMLUTILS_H
