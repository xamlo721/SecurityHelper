#ifndef BASEITEM_H
#define BASEITEM_H

#include "qglobal.h"
#include "QString"

class BaseItem {
    public:
       virtual void setID(quint32 id) { this->id = id; }
       virtual void setTitle(QString title) { this->title = title; }

        quint32 getID() { return this->id; }
        QString getTitle() { return this->title; }

    protected:
        quint32 id;
        QString title;
};


#endif // BASEITEM_H
