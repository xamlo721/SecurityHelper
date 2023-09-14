#include "XmlUtils.h"
#include <QFile>
#include <QDebug>

#include "src/exception/FileOperationException.h"

bool XmlUtils::checkFile(QString databasePath) {

    QFile file(databasePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Failed to open database file";
        return false;
    }

    QDomDocument doc;

    if (!doc.setContent(&file)) {
        file.close();
        return false;
    }

    file.seek(0); // Сбросить позицию чтения файла до начала

    QXmlStreamReader xml(&file);

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::Invalid) {
            qDebug() << "Error: file format is not valid XML";
            return false;
        }
    }

    if (xml.hasError()) {
        qDebug() << "Error:" << xml.errorString();
        return false;
    }

    file.close();

    return true;

}


qint8 XmlUtils::readChar(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().at(0).row();
}

quint8 XmlUtils::readUChar(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().at(0).row();
}

qint16 XmlUtils::readShort(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toShort();
}

quint16 XmlUtils::readUShort(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toUShort();
}

qint32 XmlUtils::readint(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toInt();
}

quint32 XmlUtils::readUint(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toUInt();
}

quint64 XmlUtils::readLong(QDomElement element, QString searchElementName) {    //Кажется quint64 на многих платформах 32
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toLong();
}

quint64 XmlUtils::readULong(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toULong();
}

QString XmlUtils::readText(QDomElement element, QString searchElementName) {
    QString result = element.elementsByTagName(searchElementName).at(0).toElement().text();
    return element.elementsByTagName(searchElementName).at(0).toElement().text();
}

QList<qint8> XmlUtils::readChars(QDomElement element, QString searchElementName) {
    QList<qint8> values;
    QDomNodeList elements = element.elementsByTagName(searchElementName);
    for (qint32 i = 0; i < elements.size(); i++ ) {
        QDomNode em = elements.at(i);
        values.append(em.toElement().text().at(0).row());
    }
    return values;
}


QList<quint8> XmlUtils::readUChars(QDomElement element, QString searchElementName) {
    QList<quint8> values;
    QDomNodeList elements = element.elementsByTagName(searchElementName);
    for (qint32 i = 0; i < elements.size(); i++ ) {
        QDomNode em = elements.at(i);
        values.append(em.toElement().text().at(0).row());
    }
    return values;
}


QList<qint16> XmlUtils::readShorts(QDomElement element, QString searchElementName) {
    QList<qint16> values;
    QDomNodeList elements = element.elementsByTagName(searchElementName);
    for (qint32 i = 0; i < elements.size(); i++ ) {
        QDomNode em = elements.at(i);
        values.append(em.toElement().text().toShort());
    }
    return values;
}


QList<quint16> XmlUtils::readUShorts(QDomElement element, QString searchElementName) {
    QList<quint16> values;
    QDomNodeList elements = element.elementsByTagName(searchElementName);
    for (qint32 i = 0; i < elements.size(); i++ ) {
        QDomNode em = elements.at(i);
        values.append(em.toElement().text().toUShort());
    }
    return values;
}


QList<qint32> XmlUtils::readints(QDomElement element, QString searchElementName) {
    QList<qint32> values;
    QDomNodeList elements = element.elementsByTagName(searchElementName);
    for (qint32 i = 0; i < elements.size(); i++ ) {
        QDomNode em = elements.at(i);
        values.append(em.toElement().text().toInt());
    }
    return values;
}


QList<quint32> XmlUtils::readUints(QDomElement element, QString searchElementName) {
    QList<quint32> values;
    QDomNodeList elements = element.elementsByTagName(searchElementName);
    for (qint32 i = 0; i < elements.size(); i++ ) {
        QDomNode em = elements.at(i);
        values.append(em.toElement().text().toUInt());
    }
    return values;
}


QList<quint64> XmlUtils::readLongs(QDomElement element, QString searchElementName) { //Кажется quint64 на многих платформах 32
    QList<quint64> values;
    QDomNodeList elements = element.elementsByTagName(searchElementName);
    for (qint32 i = 0; i < elements.size(); i++ ) {
        QDomNode em = elements.at(i);
        values.append(em.toElement().text().toLong());
    }
    return values;
}

QList<quint64> XmlUtils::readULongs(QDomElement element, QString searchElementName) {
    QList<quint64> values;
    QDomNodeList elements = element.elementsByTagName(searchElementName);
    for (qint32 i = 0; i < elements.size(); i++ ) {
        QDomNode em = elements.at(i);
        values.append(em.toElement().text().toULong());
    }
    return values;
}


QList<QString> XmlUtils::readTexts(QDomElement element, QString searchElementName) {
    QList<QString> values;
    QDomNodeList elements = element.elementsByTagName(searchElementName);
    for (qint32 i = 0; i < elements.size(); i++ ) {
        QDomNode em = elements.at(i);
        values.append(em.toElement().text());
    }
    return values;
}


void XmlUtils::writeChar(QDomDocument domDocument, QDomElement element, QString newElementName, qint8 value) {
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(QString(value));
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}


void XmlUtils::writeUChar(QDomDocument domDocument, QDomElement element, QString newElementName, quint8 value) {
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(QString(value));
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}


void XmlUtils::writeShort(QDomDocument domDocument, QDomElement element, QString newElementName, qint16 value) {
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(QString::number(value));
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}


void XmlUtils::writeUShort(QDomDocument domDocument, QDomElement element, QString newElementName, quint16 value) {
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(QString::number(value));
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}


void XmlUtils::writeint(QDomDocument domDocument, QDomElement element, QString newElementName, qint32 value) {
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(QString::number(value));
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}


void XmlUtils::writeUint(QDomDocument domDocument, QDomElement element, QString newElementName, quint32 value) {
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(QString::number(value));
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}


void XmlUtils::writeLong(QDomDocument domDocument, QDomElement element, QString newElementName, quint64 value) { //Кажется quint64 на многих платформах 32
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(QString::number(value));
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}

void XmlUtils::writeULong(QDomDocument domDocument, QDomElement element, QString newElementName, quint64 value) {
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(QString::number(value));
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}


void XmlUtils::writeText(QDomDocument domDocument, QDomElement element, QString newElementName, QString value) {
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(value);
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}


void XmlUtils::writeChars(QDomDocument domDocument, QDomElement element, QString newElementName, QList<qint8> value) {
    for (qint32 i=0; i<value.size(); i++) {
        QDomElement xmlRecord = domDocument.createElement(newElementName);
        QDomText recordValue = domDocument.createTextNode(QString(value[i]));
        xmlRecord.appendChild(recordValue);
        element.appendChild(xmlRecord);
    }
}


void XmlUtils::writeUChars(QDomDocument domDocument, QDomElement element, QString newElementName, QList<quint8> value) {
    for (qint32 i=0; i<value.size(); i++) {
        QDomElement xmlRecord = domDocument.createElement(newElementName);
        QDomText recordValue = domDocument.createTextNode(QString(value[i]));
        xmlRecord.appendChild(recordValue);
        element.appendChild(xmlRecord);
    }
}


void XmlUtils::writeShorts(QDomDocument domDocument, QDomElement element, QString newElementName, QList<qint16> value) {
    for (qint32 i=0; i<value.size(); i++) {
        QDomElement xmlRecord = domDocument.createElement(newElementName);
        QDomText recordValue = domDocument.createTextNode(QString::number(value[i]));
        xmlRecord.appendChild(recordValue);
        element.appendChild(xmlRecord);
    }
}


void XmlUtils::writeUShorts(QDomDocument domDocument, QDomElement element, QString newElementName, QList<quint16> value) {
    for (qint32 i=0; i<value.size(); i++) {
        QDomElement xmlRecord = domDocument.createElement(newElementName);
        QDomText recordValue = domDocument.createTextNode(QString::number(value[i]));
        xmlRecord.appendChild(recordValue);
        element.appendChild(xmlRecord);
    }
}


void XmlUtils::writeInts(QDomDocument domDocument, QDomElement element, QString newElementName, QList<qint32> value) {
    for (qint32 i=0; i<value.size(); i++) {
        QDomElement xmlRecord = domDocument.createElement(newElementName);
        QDomText recordValue = domDocument.createTextNode(QString::number(value[i]));
        xmlRecord.appendChild(recordValue);
        element.appendChild(xmlRecord);
    }
}

void XmlUtils::writeUints(QDomDocument domDocument, QDomElement element, QString newElementName, QList<quint32> value)  {
    for (qint32 i=0; i<value.size(); i++) {
        QDomElement xmlRecord = domDocument.createElement(newElementName);
        QDomText recordValue = domDocument.createTextNode(QString::number(value[i]));
        xmlRecord.appendChild(recordValue);
        element.appendChild(xmlRecord);
    }
}


void XmlUtils::writeLongs(QDomDocument domDocument, QDomElement element, QString newElementName, QList<quint64> value) { //Кажется quint64 на многих платформах 32
    for (qint32 i=0; i<value.size(); i++) {
        QDomElement xmlRecord = domDocument.createElement(newElementName);
        QDomText recordValue = domDocument.createTextNode(QString::number(value[i]));
        xmlRecord.appendChild(recordValue);
        element.appendChild(xmlRecord);
    }
}

void XmlUtils::writeULongs(QDomDocument domDocument, QDomElement element, QString searchElementName, QList<quint64> value) {
    for (qint32 i=0; i<value.size(); i++) {
        QDomElement xmlRecord = domDocument.createElement(searchElementName);
        QDomText recordValue = domDocument.createTextNode(QString::number(value[i]));
        xmlRecord.appendChild(recordValue);
        element.appendChild(xmlRecord);
    }
}


void XmlUtils::writeTexts(QDomDocument domDocument, QDomElement element, QString newElementName, QList<QString> value) {
    for (qint32 i=0; i<value.size(); i++) {
        QDomElement xmlRecord = domDocument.createElement(newElementName);
        QDomText recordValue = domDocument.createTextNode(value[i]);
        xmlRecord.appendChild(recordValue);
        element.appendChild(xmlRecord);
    }
}

void XmlUtils::writeXMLHeader(QDomDocument *domDocument) {
    QDomNode node(domDocument->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\""));
    domDocument->insertBefore(node,domDocument->firstChild());
}

bool XmlUtils::checkSingleNode(QDomElement element, QString searchElementName) {
    //Взять список всех дочерних, входящих в неё нод
    QDomNodeList childs = element.childNodes();

    for (qint32 i = 0; i < childs.size() ; i++) {
        //Перебираем по 1 входящий в 'Database элемент ноде
        QDomNode domNode = childs.at(i);

        //Если нода это элемент вообще (может быть комментарий или кракозябра
        if (!domNode.isElement()) {
            return 0;
        }
        //Так 3как это элемент, можно ноду для поиска скастовать в элемент для работы
        QDomElement domElement = domNode.toElement();

        //на всякий случай, проверяем, что он нормально скастовался
        if (domElement.isNull()) {
            return 0;
        }

        //Если элемент входяший в element это searchElementName, то читаем его как корневую группу
        QString nodeName = domElement.nodeName();
        if (domElement.nodeName() == searchElementName) {
            return 1;
        }

    }
    return 0;
}


QDomElement XmlUtils::readSingleNode(QDomElement element, QString searchElementName) {
    //Взять список всех дочерних, входящих в неё нод
    QDomNodeList childs= element.childNodes();
    for (qint32 i = 0; i < childs.size() ; i++) {
        //Перебираем по 1 входящий в 'Database элемент ноде
        QDomNode domNode = childs.at(i);

        //Если нода это элемент вообще (может быть комментарий или кракозябра
        if (!domNode.isElement()) {
            throw FileOperationException("[XmlUtils] Error reading QDomElement from file!");
        }

        //Так 3как это элемент, можно ноду для поиска скастовать в элемент для работы
        QDomElement domElement = domNode.toElement();

        //на всякий случай, проверяем, что он нормально скастовался
        if (domElement.isNull()) {
            throw FileOperationException("[XmlUtils] Error converting QDomNode to QDomElement!");
        }

        //Если элемент входяший в element это searchElementName, то читаем его как корневую группу
        QString nodeName = domElement.nodeName();
        if (domElement.nodeName() == searchElementName) {
            return domElement;
        }

    }
    throw FileOperationException("[XmlUtils] Error Cannot find QDomElement!");
}

QList<QDomElement> XmlUtils::readMultiNode(QDomElement element, QString searchElementName) {
    QList<QDomElement> elements;
    //Взять список всех дочерних, входящих в неё нод
    QDomNodeList childs = element.childNodes();
    for (qint32 i = 0; i < childs.size() ; i++) {
        //Перебираем по 1 входящий в 'Database элемент ноде
        QDomNode domNode = childs.at(i);
        //Если нода это элемент вообще (может быть комментарий или кракозябра
        if (!domNode.isElement()) {
            throw FileOperationException("[XmlUtils] Error reading QDomElement from file!");
        }

        //Так как это элемент, можно ноду для поиска скастовать в элемент для работы
        QDomElement domElement = domNode.toElement();

        //на всякий случай, проверяем, что он нормально скастовался
        if (domElement.isNull()) {
            throw FileOperationException("[XmlUtils] Error converting QDomNode to QDomElement!");
        }
        //Если элемент входяший в element это searchElementName, то читаем его как корневую группу
        if (domElement.nodeName() == searchElementName) {
            elements.append(domElement);
        }

    }

    return elements;
}


