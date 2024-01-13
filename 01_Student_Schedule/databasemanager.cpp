#include "databasemanager.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include "globals.h"

//Базовый конструктор
DatabaseManager::DatabaseManager() {}

//Конструктор
DatabaseManager::DatabaseManager(const QString& configPath) {
    //загружаем файл конфигурации с данными о подключении к БД
    //файл конфигурации должен находиться рядом с исполняемым файлом
    QSettings settings(configPath, QSettings::IniFormat);

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

    //проверяем возможность подключения к базе данных
    if(db.open()) qDebug() << "Database connected!";
    else qDebug() << "Can't connect to database :( " << db.lastError().text();
    db.close();
}

//получение хэша из строки (sha-256)
QString DatabaseManager::hashPassword(const QString& password) {
    QByteArray passwordData = password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256);
    return QString(hashedPassword.toHex());
}

//Получить имя пользователя
QString DatabaseManager::getUserName() {
    return userName;
}

//Регистрация пользователя
QPair<bool, QString> DatabaseManager::registerUser(const QString& email, const QString& password, const QString& nameSurname) {
    QPair<bool, QString> res;
    if(!db.open()) { //если бд не открылась
        qDebug() << "DB CONNECTION FOR REGISTER FAILD: " << db.lastError().text();
        res = {false, "Ошибка подключения к БД"};
    } else { //иначе запросим кол-во юзеров с введеной почтой
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM user WHERE email = :email;");
        query.bindValue(":email", email);
        if(!query.exec()) { //если не удалось выполнить запрос
            qDebug() << "FAILD TO CHECK USER WITH EMAIL: " << query.lastError().text();
            res = {false, "Ошибка запроса"};
        } else {
            if(query.next() && query.value(0).toInt() != 0) { //если кол-во больше 0 - почта занята
                qDebug() << "EMAIL ALREADY USED";
                res = {false, "E-mail уже зарегистрирован"};
            } else { //иначе делаем хеш введеного пароля и добавляем запись о пользователе в БД
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

//Вход пользователя
QPair<bool, QString> DatabaseManager::loginUser(const QString& email, const QString& password) {
    QPair<bool, QString> res; //результат возвращаемый из функции
    if(!db.open()) { //если бд не открылась
        qDebug() << "DB CONNECTION ON LOGIN FAILD: " << db.lastError().text();
        res = {false, "Ошибка подключения к БД"};
    } else { //запрашиваем из бд хэш пароля для введенной почты
        QSqlQuery query;
        query.prepare("SELECT password_hash FROM user WHERE email = :email");
        query.bindValue(":email", email);
        if(!query.exec()) { //если запрос не удался
            qDebug() << "FAILD TO CHECK USER WITH EMAIL: " << query.lastError().text();
            res = {false, "Ошибка запроса"};
        } else { //если пользователя с такой почтой нет
            if(!query.next()) {
                qDebug() << "No user by this email!";
                res = {false, "Неверный E-mail или пароль!"};
            } else { //если пользователь есть, сверяем хеш введеного пароля и хеш из бд
                QString hashPasswordEntered = hashPassword(password);
                QString hashPasswordStored  = query.value(0).toString();
                if(hashPasswordEntered == hashPasswordStored) { //если все совпало
                    this->userEmail = email;
                    query.prepare("SELECT name_surname FROM user WHERE email = :email;");
                    query.bindValue(":email", email);
                    query.exec();
                    query.next();
                    this->userName = query.value(0).toString();
                    res = {true, "Успешный вход!"};
                } else {
                    qDebug() << "Bad password!";
                    res = {false, "Неверный E-mail или пароль!"};
                }
            }
        }
        db.close();
    }
    return res;
}

//Выход пользователя
void DatabaseManager::logOut() {
    userName.clear();
    userEmail.clear();
}
