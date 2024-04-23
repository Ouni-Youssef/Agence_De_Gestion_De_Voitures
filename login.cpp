#include "login.h"
#include "ui_login.h"
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QByteArray>
#include <QMessageBox>
#include "welcome.h"
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

bool Login::checkLogin(const QString &cin, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Employe WHERE cin = :cin AND password = :password");
    query.bindValue(":cin", cin);

    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    query.bindValue(":password", hashedPassword.toHex());

    if (query.exec() && query.next()) {
        return true;
    } else {
        return false;
    }
}

void Login::on_pushButton_2_clicked()
{
    close();
}

void Login::on_pushButton_clicked()
{
    {
        QString cin = ui->lineEdit->text();
        QString password = ui->lineEdit_2->text();

        if (this->checkLogin(cin, password)) {
            close();
            Welcome *wel = new Welcome(this);
            wel->show();
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Not Connected"), QObject::tr("Connection failed."));
        }
}
}
