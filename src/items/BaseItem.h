#ifndef BASEITEM_H
#define BASEITEM_H

#include "qglobal.h"
#include "QString"

class BaseItem {
    public:
       virtual void setID(quint32 id) { this->id = id; }
       virtual void setText(QString text) { this->text = text; }

        quint32 getID() { return this->id; }
        QString getText() { return this->text; }

    protected:
        quint32 id;
        QString text;
};


#endif // BASEITEM_H
