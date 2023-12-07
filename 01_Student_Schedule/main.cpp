#include "mainwindow.h"
#include "databasemanager.h"

#include <QApplication>
#include <QCoreApplication>
#include <QSettings>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QString test = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QString configPath = QApplication::applicationDirPath() + "/config.ini";

    DatabaseManager db(configPath);

    MainWindow w(&db);
    w.show();
    return a.exec();
}
