#include "lessonadder.h"
#include "ui_lessonadder.h"
#include "globals.h"

lessonAdder::lessonAdder(DatabaseManager* mdb, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::lessonAdder)
    , db(mdb)
{
    dayOfWeeks = {"Понедельник","Вторник","Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};

    ui->setupUi(this);
    ui->lessonDayOfWeekBox->addItems(dayOfWeeks);
    ui->info->clear();
}

lessonAdder::~lessonAdder()
{
    delete ui;
}
