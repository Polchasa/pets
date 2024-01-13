#include "mainwindow.h"
#include "databasemanager.h"
#include "globals.h"

#include <QApplication>
#include <QCoreApplication>
#include <QSettings>
#include <QFont>
#include <QFontDatabase>

QString fontName;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Путь к файлу конфигурации подключения к базе данных
    QString configPath =":/config.ini";

    //подключение шрифта из файла ресурсов
    //но для использования в проекте он будет называтья не по имени файла
    //для того чтобы точно знать его название, можно в винде открыть файл шрифта
    //и посмотреть там его название
    QFontDatabase::addApplicationFont(":/Roboto-Light.ttf");

    int fontId = QFontDatabase::addApplicationFont(":/Roboto-Light.ttf");
    if (fontId != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

        if (!fontFamilies.isEmpty()) {
            // Теперь шрифт доступен для использования в приложении.
            QFont customFont(fontFamilies.first(), 12);
            fontName = customFont.family();
            // Далее используйте customFont в ваших виджетах или элементах интерфейса.
        }
    }

    DatabaseManager db(configPath);

    MainWindow w(&db);
    w.clearFocus();
    w.setWindowTitle("Расписание занятий студента");
    w.show();
    return a.exec();
}
