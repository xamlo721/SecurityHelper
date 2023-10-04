#ifndef ITEMDELETIONMESSAGEBOX_H
#define ITEMDELETIONMESSAGEBOX_H

#include <QMessageBox>

#include "EnumMessageBoxVariants.h"
#include "EnumMessageBoxItemVariants.h"

class ItemDeletionMessageBox : public QMessageBox {

    private:
        QString getTitle(EnumMessageBoxVariants variant, EnumMessageBoxItemVariants item);
        QString getMessage(EnumMessageBoxVariants variant, EnumMessageBoxItemVariants item);

    public:
        ItemDeletionMessageBox();

        QMessageBox::StandardButton openWarning(EnumMessageBoxVariants variant, EnumMessageBoxItemVariants item);

};

#endif // ITEMDELETIONMESSAGEBOX_H
