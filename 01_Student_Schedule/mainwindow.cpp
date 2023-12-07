#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QButtonGroup>
#include <QFontDatabase>
#include <QRegularExpression>

#include "styles.cpp"

MainWindow::MainWindow(DatabaseManager* mdb, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db(mdb)
{
    ui->setupUi(this);
    setUIStyles();
    configureUI();
}

void MainWindow::setUIStyles() {
    ui->horizontalLayoutWidget->setStyleSheet(setTopButtonsStyles());
    ui->tabWidget->setStyleSheet(setTabWidgetStyle());

    ui->logInfoLabel->setStyleSheet(setLabelStyle());
    ui->logEmail->setStyleSheet(setEditStyleClassic());
    ui->logPass->setStyleSheet(setEditStyleClassic());
    ui->logEmail->setAlignment(Qt::AlignCenter);
    ui->logPass->setAlignment(Qt::AlignCenter);
    ui->logIn->setStyleSheet(setLogInButtonStyle());

    ui->signInfoLabel->setStyleSheet(setLabelStyle());
    ui->signName->setStyleSheet(setEditStyleClassic());
    ui->signEmail->setStyleSheet(setEditStyleClassic());
    ui->signPass->setStyleSheet(setEditStyleClassic());
    ui->signName->setAlignment(Qt::AlignCenter);
    ui->signEmail->setAlignment(Qt::AlignCenter);
    ui->signPass->setAlignment(Qt::AlignCenter);
    ui->signIn->setStyleSheet(setLogInButtonStyle());

    ui->logStatusLabel->setStyleSheet(setLabelBadStyle());
    ui->signStatusLabel->setStyleSheet(setLabelGoodStyle());
}

void MainWindow::configureUI() {
    //подключение шрифта из файла ресурсов
    //но для использования в проекте он будет называтья не по имени файла
    //для того чтобы точно знать его название, можно в винде открыть файл шрифта
    //и посмотреть там его название
    QFontDatabase::addApplicationFont(":/Roboto-Light.ttf");

    ui->tabWidget->setCurrentIndex(0); //задаем номер текущего таба

    ui->headButton_1->setChecked(true); //делаем кнопку "Вход" нажатой

    headButtons = new QButtonGroup(this); //создаем группу для головных кнопок
    headButtons->addButton(ui->headButton_1, 0); //добавлям кнопки в группу
    headButtons->addButton(ui->headButton_2, 1);
    connect(headButtons, SIGNAL(idClicked(int)), ui->tabWidget, SLOT(setCurrentIndex(int))); //связываем группу кнопок с табами
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_logIn_clicked()
{
    static const QRegularExpression rEmail(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    static const QRegularExpression rPass(R"(^\S+$)");

    QRegularExpressionMatch matchEmail = rEmail.match(ui->logEmail->text());
    QRegularExpressionMatch matchPas   = rPass.match(ui->logPass->text());
    if(!(matchEmail.hasMatch() && matchPas.hasMatch())) {
        ui->logStatusLabel->setText("Введены некорректные данные");
        ui->logStatusLabel->setStyleSheet(setLabelBadStyle());
        return;
    }
    QString email = ui->logEmail->text();
    QString password = ui->logPass->text();
    if(db->loginUser(email, password)) {
        ui->logStatusLabel->setText("Вход выполнен успешно!");
        ui->logStatusLabel->setStyleSheet(setLabelGoodStyle());
        ui->logEmail->clear();
        ui->logPass->clear();
    } else {
        ui->logStatusLabel->setText("Неверный E-mail или пароль!");
        ui->logStatusLabel->setStyleSheet(setLabelBadStyle());
    }
}

/*
 * static const QRegularExpression rEmail(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
 * static const QRegularExpression rLogPass(R"(^\S+$)");
 * static const QRegularExpression rSignPass(R"(^.{6,}$)");
 * static const QRegularExpression rNameSurnamePass(R"(^[A-Za-zА-Яа-я]+ [A-Za-zА-Яа-я]+$)");
*/

void MainWindow::on_signIn_clicked()
{
    QString email = ui->signEmail->text();
    QString pass = ui->signPass->text();
    QString nameSurname = ui->signName->text();
    static const QRegularExpression rEmail(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    static const QRegularExpression rPass(R"(^.{6,}$)");
    static const QRegularExpression rNameSurname(R"(^[A-Za-zА-Яа-я]+ [A-Za-zА-Яа-я]+$)");

    QRegularExpressionMatch matchEmail = rEmail.match(email);
    QRegularExpressionMatch matchPas = rPass.match(pass);
    QRegularExpressionMatch matchNameSurname = rNameSurname.match(nameSurname);

    if(!(matchEmail.hasMatch() && matchPas.hasMatch() && matchNameSurname.hasMatch())) {
        ui->signStatusLabel->setText("Введенные данные некорректны.");
        ui->signStatusLabel->setStyleSheet(setLabelBadStyle());
        return;
    }

    auto res = db->registerUser(email, pass, nameSurname);
    ui->signStatusLabel->setText(res.second);
    if(res.first) {
        ui->signStatusLabel->setStyleSheet(setLabelGoodStyle());
        ui->signEmail->clear();
        ui->signPass->clear();
        ui->signName->clear();
    }
    else ui->signStatusLabel->setStyleSheet(setLabelBadStyle());
}

