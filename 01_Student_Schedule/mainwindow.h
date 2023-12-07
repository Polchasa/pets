#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QButtonGroup>
#include "databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DatabaseManager* mdb, QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_logIn_clicked();

    void on_signIn_clicked();

private:
    Ui::MainWindow* ui;
    DatabaseManager* db;
    QButtonGroup* headButtons;

    void setUIStyles();
    void configureUI();
};
#endif // MAINWINDOW_H
