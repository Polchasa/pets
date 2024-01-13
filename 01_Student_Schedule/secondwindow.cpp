#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "mainwindow.h"
#include "globals.h"

#include "lessonadder.h"

#include "styles.h"

#include <QDateTime>

SecondWindow::SecondWindow(DatabaseManager* mdb, MainWindow* mainWindow, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow),
    db(mdb),
    mainWindow(mainWindow)
{
    ui->setupUi(this);
    ui->userNameSurname->setText(db->getUserName());
    ui->userNameSurname->setStyleSheet(setUserNameSurnameStyle());
    ui->userNameSurname->setAlignment(Qt::AlignCenter);

    ui->centralwidget->setStyleSheet("background-color: #181818");

    ui->dayAndDate->setStyleSheet(setDayDateStyle());

    ui->logOut->setStyleSheet(setLogOutButtonStyle());

    ui->addLesson->setStyleSheet(setAddLessonStyle());

    lessonAdderWindow = new lessonAdder(db);
}

void SecondWindow::extendetShow() {
    QString temp = db->getUserName();
    temp.replace(' ', '\n');
    ui->userNameSurname->setText(temp);

    QDateTime currDateTime = QDateTime::currentDateTime();
    QDate currDate = currDateTime.date();
    QString currDateString = QLocale("ru_RU").toString(currDate, "dd MMMM");
    int currentDayOfWeek = currDate.dayOfWeek();
    QString dayOfWeekString = QLocale("ru_RU").dayName(currentDayOfWeek);
    dayOfWeekString[0] = dayOfWeekString[0].toUpper();
    temp = dayOfWeekString + "\n" + currDateString;
    ui->dayAndDate->setText(temp);

    this->setWindowTitle("Расписание занятий студента");
    this->show();
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_logOut_clicked()
{
    db->logOut();
    this->hide();
    if(mainWindow){
        mainWindow->clearShow();
    }
}


void SecondWindow::on_addLesson_clicked()
{
    lessonAdderWindow->clearFocus();
    lessonAdderWindow->setWindowTitle("Добавление занятия");
    lessonAdderWindow->show();
}

