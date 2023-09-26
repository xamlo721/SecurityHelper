#ifndef BASEITEM_H
#define BASEITEM_H

#include "qglobal.h"
#include "QString"

class BaseItem {
    public:
        quint32 getId() { return this->id; }
        QString getText() { return this->text; }

    protected:
        quint32 id;
        QString text;
};


#endif // BASEITEM_H
