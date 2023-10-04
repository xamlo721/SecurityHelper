#include "ItemDeletionMessageBox.h"

ItemDeletionMessageBox::ItemDeletionMessageBox() {
}

QMessageBox::StandardButton ItemDeletionMessageBox::openWarning(EnumMessageBoxVariants variant, EnumMessageBoxItemVariants item) {
    ItemDeletionMessageBox messageBox;

    messageBox.setIcon(QMessageBox::Warning);
    messageBox.setWindowTitle(this->getTitle(variant, item));
    messageBox.setText(this->getMessage(variant, item));
    messageBox.setStandardButtons(QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No));
    messageBox.setDefaultButton(QMessageBox::NoButton);

    messageBox.setButtonText(QMessageBox::Yes, "Да");
    messageBox.setButtonText(QMessageBox::No, "Нет");

    return (QMessageBox::StandardButton)messageBox.exec();
}

QString ItemDeletionMessageBox::getTitle(EnumMessageBoxVariants variant, EnumMessageBoxItemVariants item) {
    QString title = "Удаление ";

    if(variant == EnumMessageBoxVariants::DeletionOneItem) {

        switch (item) {
        case EnumMessageBoxItemVariants::EventCategory:
            title += "выбранной категории событий";
            break;

        case EnumMessageBoxItemVariants::Event:
            title += "выбранного события";
            break;

        case EnumMessageBoxItemVariants::Incident:
            title += "выбранного инцидента";
            break;

        case EnumMessageBoxItemVariants::Scenario:
            title += "выбранного сценария";
            break;
        }

    }
    else {
        switch (item) {
        case EnumMessageBoxItemVariants::EventCategory:
            title += "выбранных категорий событий";
            break;

        case EnumMessageBoxItemVariants::Event:
            title += "выбранных событий";
            break;

        case EnumMessageBoxItemVariants::Incident:
            title += "выбранных инцидентов";
            break;

        case EnumMessageBoxItemVariants::Scenario:
            title += "выбранных сценариев";
            break;
        }

    }
    return title;
}

QString ItemDeletionMessageBox::getMessage(EnumMessageBoxVariants variant, EnumMessageBoxItemVariants item) {
    QString message = "Вы уверены, что хотите удалить ";

    if(variant == EnumMessageBoxVariants::DeletionOneItem) {

        switch (item) {
        case EnumMessageBoxItemVariants::EventCategory:
            message += "выбранную категорию событий";
            break;

        case EnumMessageBoxItemVariants::Event:
            message += "выбранное событие";
            break;

        case EnumMessageBoxItemVariants::Incident:
            message += "выбранный инцидент";
            break;

        case EnumMessageBoxItemVariants::Scenario:
            message += "выбранный сценарий";
            break;
        }

    }
    else {

        switch (item) {
        case EnumMessageBoxItemVariants::EventCategory:
            message += "выбранные категории событий";
            break;

        case EnumMessageBoxItemVariants::Event:
            message += "выбранные события";
            break;

        case EnumMessageBoxItemVariants::Incident:
            message += "выбранные инциденты";
            break;

        case EnumMessageBoxItemVariants::Scenario:
            message += "выбранные сценарии";
            break;
        }

    }

    message += "?";
    return message;
}
