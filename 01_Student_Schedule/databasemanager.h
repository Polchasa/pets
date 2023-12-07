#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QDebug>
#include <QVector>
#include <QPair>

#define TUSER "user"


class DatabaseManager
{
public:
    DatabaseManager();
    DatabaseManager(const QString& configPath);
    bool loginUser(const QString& email, const QString& password);
    QPair<bool, QString> registerUser(const QString& email, const QString& password, const QString& nameSurname);
    QVector<QString> getTableInfo(QString tableName);    
private:
    QSqlDatabase db;
    QString userEmail;

    QString hashPassword(const QString& password);
};

#endif // DATABASEMANAGER_H
