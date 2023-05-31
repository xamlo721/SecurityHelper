#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class Database : public QObject {

    Q_OBJECT

    public:
        explicit Database(QObject *parent = nullptr);

    private:
        //QMap<int, >

    signals:

};

#endif // DATABASE_H
