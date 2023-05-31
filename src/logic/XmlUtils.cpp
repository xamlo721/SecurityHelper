#include "src/logic/XmlUtils.h"
#include <QFile>
#include <QDebug>

#include <stdexcept>
#include <exception>

XmlUtils::XmlUtils(QObject *parent) : QObject(parent) {

}

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

char XmlUtils::readChar(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().at(0).row();
}

unsigned char XmlUtils::readUChar(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().at(0).row();
}

short XmlUtils::readShort(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toShort();
}

unsigned short XmlUtils::readUShort(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toUShort();
}

int XmlUtils::readint(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toInt();
}

unsigned int XmlUtils::readUint(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toUInt();
}

long XmlUtils::readLong(QDomElement element, QString searchElementName) {    //Кажется long на многих платформах 32
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toLong();
}

unsigned long XmlUtils::readULong(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toULong();
}

QString XmlUtils::readText(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text();
}

QDomElement XmlUtils::readSingleNode(QDomElement element, QString searchElementName) {
    //Взять список всех дочерних, входящих в неё нод
    QDomNodeList childs= element.childNodes();
    for (int i = 0; i < childs.size() ; i++) {
        //Перебираем по 1 входящий в 'Database элемент ноде
        QDomNode domNode = childs.at(i);

        //Если нода это элемент вообще (может быть комментарий или кракозябра
        if (!domNode.isElement()) {
            throw std::runtime_error(QString("[XmlUtils] Error reading QDomElement from file!").toLocal8Bit().constData());
        }

        //Так как это элемент, можно ноду для поиска скастовать в элемент для работы
        QDomElement domElement = domNode.toElement();

        //на всякий случай, проверяем, что он нормально скастовался
        if (domElement.isNull()) {
            throw std::runtime_error(QString("[XmlUtils] Error converting QDomNode to QDomElement!").toLocal8Bit().constData());
        }

        //Если элемент входяший в element это searchElementName, то читаем его как корневую группу
        if (domElement.nodeName() == searchElementName) {
            return domElement;
        }

    }

    throw std::runtime_error(QString("[XmlUtils] Error Cannot find QDomElement!").toLocal8Bit().constData());
}

QList<QDomElement> XmlUtils::readMultiNode(QDomElement element, QString searchElementName) {
    QList<QDomElement> elements;
    //Взять список всех дочерних, входящих в неё нод
    QDomNodeList childs= element.childNodes();
    for (int i = 0; i < childs.size() ; i++) {
        //Перебираем по 1 входящий в 'Database элемент ноде
        QDomNode domNode = childs.at(i);

        //Если нода это элемент вообще (может быть комментарий или кракозябра
        if (!domNode.isElement()) {
            throw std::runtime_error(QString("[XmlUtils] Error reading QDomElement from file!").toLocal8Bit().constData());
        }

        //Так как это элемент, можно ноду для поиска скастовать в элемент для работы
        QDomElement domElement = domNode.toElement();

        //на всякий случай, проверяем, что он нормально скастовался
        if (domElement.isNull()) {
            throw std::runtime_error(QString("[XmlUtils] Error converting QDomNode to QDomElement!").toLocal8Bit().constData());
        }

        //Если элемент входяший в element это searchElementName, то читаем его как корневую группу
        if (domElement.nodeName() == searchElementName) {
            elements.append(domElement);
        }

    }

    return elements;
}
