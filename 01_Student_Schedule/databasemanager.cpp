#include "databasemanager.h"
#include <QMessageBox>
#include <QCryptographicHash>

DatabaseManager::DatabaseManager() {}

DatabaseManager::DatabaseManager(const QString& configPath) {
    //загружаем файл конфигурации с данными о подключении к БД
    //файл конфигурации должен находиться рядом с исполняемым файлом
    QSettings settings(configPath, QSettings::IniFormat);

    //QSettings settings("X:\\Cyrill\\Programming\\pets\\build-01_Student_Schedule-Desktop_Qt_6_6_0_MinGW_64_bit-Debug\\debug\\config.ini", QSettings::IniFormat);
    //берем данные из файла конфигурации для подключения к бд
    QString host = settings.value("database/host").toString();
    QString databaseName = settings.value("database/name").toString();
    QString username = settings.value("database/username").toString();
    QString password = settings.value("database/password").toString();
    unsigned int port = settings.value("database/port").toUInt();

    //настраиваем подключение к бд
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(databaseName);
    db.setUserName(username);
    db.setPassword(password);
    db.setPort(port);

    if(db.open()) {
        qDebug() << "Database connected! " << db.hostName();
    }
    else {
        qDebug() << "Can't connect to database :(" << db.lastError().text();
    }
    db.close();
}

QString DatabaseManager::hashPassword(const QString& password) {
    QByteArray passwordData = password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256);
    return QString(hashedPassword.toHex());
}

bool DatabaseManager::loginUser(const QString& email, const QString& password) {
    if(!db.open()) {
        qDebug() << "DB CONNECTION ON LOGIN FAILD: " << db.lastError().text();
        return false;
    }
    QSqlQuery query;
    query.prepare("SELECT password_hash FROM user WHERE email = :email");
    query.bindValue(":email", email);

    if(!query.exec()) {
        qDebug() << "Error! On user taken:" << query.lastError().text();
        db.close();
        return false;
    }

    if(query.next()) {
        QString hashPasswordEntered = hashPassword(password);
        QString hashPasswordStored  = query.value(0).toString();
        if(hashPasswordEntered == hashPasswordStored) {
            this->userEmail = email;
            db.close();
            return true;
        } else {
            qDebug() << "Bad password!";
            db.close();
            return false;
        }
    } else {
        qDebug() << "No user by this email!";
        db.close();
        return false;
    }
}

QPair<bool, QString> DatabaseManager::registerUser(const QString& email, const QString& password, const QString& nameSurname) {
    QPair<bool, QString> res;
    if(!db.open()) {
        qDebug() << "DB CONNECTION FOR REGISTER FAILD: " << db.lastError().text();
        res = {false, "Ошибка подключения к БД"};
    } else {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM user WHERE email = :email;");
        query.bindValue(":email", email);
        if(!query.exec()) {
            qDebug() << "FAILD TO CHECK USER WITH EMAIL: " << query.lastError().text();
            res = {false, "Ошибка запроса"};
        } else {
            if(query.next() && query.value(0).toInt() != 0) {
                qDebug() << "EMAIL ALREADY USED";
                res = {false, "E-mail уже зарегистрирован"};
            } else {
                QString hashPasswordEntered = hashPassword(password);
                query.prepare("INSERT INTO user (name_surname, email, password_hash) VALUES (:n, :e, :p);");
                query.bindValue(":n", nameSurname);
                query.bindValue(":e", email);
                query.bindValue(":p", hashPasswordEntered);
                if(!query.exec()) {
                    qDebug() << "CREATE USER ERROR: " << query.lastError().text();
                    res = {false, "Ошибка создания пользователя"};
                } else {
                    qDebug() << "USER CREATED!";
                    res = {true, "Регистрация прошла успешно"};
                }
            }
        }
        db.close();
    }
    return res;
}

QVector<QString> DatabaseManager::getTableInfo(QString tableName) {
    if(!db.open()) return {};
    QSqlQuery query;
    query.exec("SELECT * FROM " + tableName + ";");
    //query.exec();
    QVector<QString> res;
    while(query.next()) {
        res.push_back(query.value(0).toString() + " " + query.value(1).toString() + " " + query.value(2).toString());
    }
    return res;
}
