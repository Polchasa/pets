#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QButtonGroup>
#include <QKeyEvent>
#include "databasemanager.h"
#include "secondwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DatabaseManager* mdb, QWidget *parent = nullptr);
    ~MainWindow();
    void clearShow();

private slots:

    void on_logIn_clicked();

    void on_signIn_clicked();

private:
    Ui::MainWindow* ui;
    DatabaseManager* db;
    QButtonGroup* headButtons;
    SecondWindow *secondWindow;

    void setUIStyles();
    void configureUI();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
