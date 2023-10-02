#ifndef ADMINEDITMENUCONTROLLER_H
#define ADMINEDITMENUCONTROLLER_H

#include <QObject>

#include "src/ui/admin/AdminEditMenuWidget.h"

/**
 * @brief AdminEditMenuController - контроллер меню редактирования
 * администратора, инициализирует меню и управляет им приказами от ядра программы.
 */
class AdminEditMenuController : public QObject {

    Q_OBJECT

    private:
        /// Объект меню редактирования
        AdminEditMenuWidget *editMenuWidget;

    private slots:

    public:
        /**
        *  @brief AdminEditMenuController - не изменяемый конструктор по умолчанию
        *  @param parent - родительский объект в иерархии Qt.
        */
        explicit AdminEditMenuController(QObject *parent = nullptr);

    /**
    *  @brief init - метод инициализации меню редактирования
    *  @param editMenu - объект AdminEditMenuWidget, находящийся в MainWindow.
    */
        void init(AdminEditMenuWidget *editMenu);

    public slots:
       void slotSetDeleteSelectedCategoriesButtonEnabled();
       void slotSetDeleteSelectedCategoriesButtonDisabled();

       void slotSetDeleteSelectedEventsButtonEnabled();
       void slotSetDeleteSelectedEventsButtonDisabled();

    signals:
        void signalAddCategoryButtonPressed();
        void signalDeleteSelectedCategoriesButtonPressed();

        void signalAddEventButtonPressed();
        void signalDeleteSelectedEventsButtonPressed();
};

#endif // ADMINEDITMENUCONTROLLER_H
