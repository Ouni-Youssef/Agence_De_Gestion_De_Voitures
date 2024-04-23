#include "welcome.h"
#include "ui_welcome.h"
#include "employe.h"
#include "mainclient.h"
#include "gestion_des_voitures.h"
#include "paiement.h"
#include "location.h"
#include "login.h"

Welcome::Welcome(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Welcome)
{
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;
}


void Welcome::on_pushButton_6_clicked()
{
    close();
}

void Welcome::on_pushButton_4_clicked()
{
    close();
    Employe *emp = new Employe(this);
    emp->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    emp->show();
}

void Welcome::on_pushButton_clicked()
{
    close();
    MainClient *client = new MainClient(this);
    client->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    client->show();
}

void Welcome::on_pushButton_2_clicked()
{
    close();
    gestion_des_voitures *voiture = new gestion_des_voitures(this);
    voiture->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    voiture->show();
}

void Welcome::on_pushButton_3_clicked()
{
    close();
    Paiement *pay = new Paiement(this);
    pay->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    pay->show();

}

void Welcome::on_pushButton_5_clicked()
{
    close();
    Location *res = new Location(this);
    res->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");
    res->show();

}

void Welcome::on_pushButton_7_clicked()
{
    close();
    Login *log = new Login(this);
    log->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");
    log->show();
}
