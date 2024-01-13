#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include "databasemanager.h"
#include "lessonadder.h"

namespace Ui {
class SecondWindow;
}

class MainWindow;

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(DatabaseManager* mdb, MainWindow* mainWindow, QWidget *parent = nullptr);
    void extendetShow();
    ~SecondWindow();

private slots:
    void on_logOut_clicked();

    void on_addLesson_clicked();

private:
    Ui::SecondWindow *ui;
    DatabaseManager* db;
    MainWindow* mainWindow;
    lessonAdder* lessonAdderWindow;
};

#endif // SECONDWINDOW_H
