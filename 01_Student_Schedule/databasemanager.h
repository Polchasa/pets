#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QDebug>
#include <QVector>
#include <QPair>

class DatabaseManager
{
public:
    DatabaseManager();
    DatabaseManager(const QString& configPath);
    QPair<bool, QString> loginUser(const QString& email, const QString& password);
    QPair<bool, QString> registerUser(const QString& email, const QString& password, const QString& nameSurname);
    void logOut();
    QPair<bool, QString> addLesson();
    QString getUserName();
private:
    QSqlDatabase db;
    QString userEmail;
    QString userName;

    QString hashPassword(const QString& password);
};

#endif // DATABASEMANAGER_H
