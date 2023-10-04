#ifndef ADMINEDITMENUWIDGET_H
#define ADMINEDITMENUWIDGET_H

#include <QWidget>
#include "qboxlayout.h"
#include "qscrollarea.h"

namespace Ui {
class AdminEditMenuWidget;
}

/**
 * @brief AdminEditMenuWidget - класс-виджет меню редактирования
 * администратора, предоставляет возможность переключаться по вкладкам с items,
 * а так же редактировать их, удалять и добавлять.
 */
class AdminEditMenuWidget : public QWidget {

    Q_OBJECT

    private:
        /// Переменные боксов, в которых хранятся виджеты items
        QVBoxLayout *boxLayoutCategories;
        QVBoxLayout *boxLayoutEvents;
        QVBoxLayout *boxLayoutIncidents;
        QVBoxLayout *boxLayoutScenaries;
        /// Переменная, хранящая в себе данные интерфейса
        Ui::AdminEditMenuWidget *ui;

        void setAllDeleteButtonsDisabled();

    private slots:

    public:
        /**
         *  @brief AdminEditMenuWidget - конструктор по умолчанию
         *  @param parent - родительский объект в иерархии Qt.
         *  В данном конструкторе производится установка UI.
         */
        explicit AdminEditMenuWidget(QWidget *parent = nullptr);
        /**
         *  @brief ~AdminEditMenuWidget - деструктор по умолчанию, используется для
         * высвобождения памяти.
         */
        ~AdminEditMenuWidget();

        /**
         *  @brief setupScrollAreas - метод, выделяющий память под
         *  указатели на QVBoxLayout для каждого item'а и добавляющий их в
         *  соответствующие scrollArea.
         */
        void setupScrollAreas();

        /**
         *  @brief getBoxLayoutCategories - метод, позволяющий получить бокс категорий.
         */
        QVBoxLayout *getBoxLayoutCategories();
        /**
         *  @brief getBoxLayoutEvents - метод, позволяющий получить бокс событий.
         */
        QVBoxLayout *getBoxLayoutEvents();
        /**
         *  @brief getBoxLayoutIncidents - метод, позволяющий получить бокс инцидентов.
         */
        QVBoxLayout *getBoxLayoutIncidents();
        /**
         *  @brief getBoxLayoutScenaries - метод, позволяющий получить бокс сценариев.
         */
        QVBoxLayout *getBoxLayoutScenaries();

        void setAllTabsEnable();

        void setCategoriesActive();
        void setEventsActive();
        void setIncidentsActive();
        void setScenariesActive();
        void setRecommendtaionsActive();


        void setAddCategoryButtonEnabled();
        void setAddCategoryButtonDisabled();

        void setDeleteSelectedCategoriesButtonEnabled();
        void setDeleteSelectedCategoriesButtonDisabled();


        void setAddEventButtonEnabled();
        void setAddEventButtonDisabled();

        void setDeleteSelectedEventsButtonEnabled();
        void setDeleteSelectedEventsButtonDisabled();                        

    public slots:

    signals:
        void signalAddCategoryButtonPressed();
        void signalDeleteSelectedCategoriesButtonPressed();

        void signalAddEventButtonPressed();
        void signalDeleteSelectedEventsButtonPressed();
};

#endif // ADMINEDITMENUWIDGET_H
