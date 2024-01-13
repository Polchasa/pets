#ifndef LESSONADDER_H
#define LESSONADDER_H

#include <QWidget>
#include "databasemanager.h"

namespace Ui {
class lessonAdder;
}

class lessonAdder : public QWidget
{
    Q_OBJECT

public:
    explicit lessonAdder(DatabaseManager* mdb, QWidget *parent = nullptr);
    ~lessonAdder();

private:
    Ui::lessonAdder *ui;
    DatabaseManager* db;
    QStringList dayOfWeeks;
};

#endif // LESSONADDER_H
