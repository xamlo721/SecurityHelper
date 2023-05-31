#ifndef SCENARIOMENU_H
#define SCENARIOMENU_H

#include <QWidget>

namespace Ui {
class ScenarioMenu;
}

class ScenarioMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ScenarioMenu(QWidget *parent = nullptr);
    ~ScenarioMenu();

private:
    Ui::ScenarioMenu *ui;
};

#endif // SCENARIOMENU_H
