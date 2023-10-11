#ifndef SELECTEDWIDGETSTORAGE_H
#define SELECTEDWIDGETSTORAGE_H

#include <QObject>

class SelectedWidgetStorage : public QObject
{
    Q_OBJECT
public:
    explicit SelectedWidgetStorage(QObject *parent = nullptr);

signals:

};

#endif // SELECTEDWIDGETSTORAGE_H
