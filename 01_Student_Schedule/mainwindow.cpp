#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"

#include <QButtonGroup>
#include <QFontDatabase>
#include <QRegularExpression>

#include "styles.h"

MainWindow::MainWindow(DatabaseManager* mdb, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db(mdb)
{
    ui->setupUi(this);
    configureUI();
    setUIStyles();
    this->clearFocus();
    secondWindow = new SecondWindow(db, this);

    #ifdef DEBUG
    ui->logEmail->setText("polchasa@live.ru");
    ui->logPass->setText("PolchasaPolchasa1");
    #endif
}

//Обработка нажатия клавиши энтер
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        if(ui->tabWidget->currentIndex() == 0) on_logIn_clicked();
        else on_signIn_clicked();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Пременение стилей для окна
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

//Конфигурирование окна, задача базовых значений для элементов
void MainWindow::configureUI() {


    ui->tabWidget->setCurrentIndex(0); //задаем номер текущего таба

    ui->headButton_1->setChecked(true); //делаем кнопку "Вход" нажатой

    headButtons = new QButtonGroup(this); //создаем группу для головных кнопок
    headButtons->addButton(ui->headButton_1, 0); //добавлям кнопки в группу
    headButtons->addButton(ui->headButton_2, 1);
    connect(headButtons, SIGNAL(idClicked(int)), ui->tabWidget, SLOT(setCurrentIndex(int))); //связываем группу кнопок с табами
}

void MainWindow::on_logIn_clicked()
{
    QString email = ui->logEmail->text();
    QString pass = ui->logPass->text();
    static const QRegularExpression rEmail(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    static const QRegularExpression rPass(R"(^\S+$)");

    QRegularExpressionMatch matchEmail = rEmail.match(email);
    QRegularExpressionMatch matchPas   = rPass.match(pass);
    if(!(matchEmail.hasMatch() && matchPas.hasMatch())) {
        ui->logStatusLabel->setText("Введенные данные некорректны.");
        ui->logStatusLabel->setStyleSheet(setLabelBadStyle());
        return;
    }

    auto res = db->loginUser(email, pass);
    ui->logStatusLabel->setText(res.second);
    if(res.first) {
        ui->logStatusLabel->setStyleSheet(setLabelGoodStyle());
        ui->logEmail->clear();
        ui->logPass->clear();

        secondWindow->extendetShow();
        ui->logPass->clearFocus();
        this->clearFocus();
        this->hide(); // скрываем окно логина
    } else ui->signStatusLabel->setStyleSheet(setLabelBadStyle());
}

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
    } else ui->signStatusLabel->setStyleSheet(setLabelBadStyle());
}

void MainWindow::clearShow() {
    ui->tabWidget->setCurrentIndex(0);
    ui->headButton_1->setChecked(true);
    ui->logStatusLabel->clear();
    ui->signStatusLabel->clear();
    this->show();
}

