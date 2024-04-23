#include "mainclient.h"
#include "ui_mainclient.h"
#include "client.h"
#include <QWidget>
#include <QMessageBox>
#include "welcome.h"
#include "employe.h"
#include "gestion_des_voitures.h"
#include "paiement.h"
#include "location.h"
#include <QTimer>

MainClient::MainClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainClient)
{
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(tmpclient.afficher());
    ui->setupUi(this);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->update();
}

MainClient::~MainClient()
{
    delete ui;
}

void MainClient::on_pb_supprimer_clicked()
{
    int id = ui->lineEdit_4->text().toInt();
    bool test = tmpclient.supprimer(id);

    if (test)
    {
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(tmpclient.afficher());
        ui->tableView->setModel(proxyModel);
        ui->tableView->setSortingEnabled(true);
        ui->tableView->update();
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Suppression  effectué");
        labelStatus->show();
        QTimer *timer = new QTimer(this);

        // Connect the timeout signal to a slot that hides the label
        connect(timer, &QTimer::timeout, [=]() {
            labelStatus->hide();
            timer->deleteLater();  // Delete the timer to clean up resources
        });

        // Set the timer to single-shot mode and start it with a 5-second interval
        timer->setSingleShot(true);
        timer->start(5000);
    }
    else
    {
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Suppression non effectué");
        labelStatus->show();
        QTimer *timer = new QTimer(this);

        // Connect the timeout signal to a slot that hides the label
        connect(timer, &QTimer::timeout, [=]() {
            labelStatus->hide();
            timer->deleteLater();  // Delete the timer to clean up resources
        });

        // Set the timer to single-shot mode and start it with a 5-second interval
        timer->setSingleShot(true);
        timer->start(5000);
    }
}

void MainClient::on_pushButton_clicked()
{
    int id = ui->lineEdit->text().toInt();
    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_3->text();
    int age = ui->lineEdit_5->text().toInt();

    Client c(id, age, nom, prenom);
    bool test = c.ajouter();

    if (test)
    {
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(tmpclient.afficher());
        ui->tableView->setModel(proxyModel);
        ui->tableView->setSortingEnabled(true);
        ui->tableView->update();
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Ajout effectué");
        labelStatus->show();
        QTimer *timer = new QTimer(this);

        // Connect the timeout signal to a slot that hides the label
        connect(timer, &QTimer::timeout, [=]() {
            labelStatus->hide();
            timer->deleteLater();  // Delete the timer to clean up resources
        });

        // Set the timer to single-shot mode and start it with a 5-second interval
        timer->setSingleShot(true);
        timer->start(5000);
    }
    else
    {
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Ajout non effectué");
        labelStatus->show();
        QTimer *timer = new QTimer(this);

        // Connect the timeout signal to a slot that hides the label
        connect(timer, &QTimer::timeout, [=]() {
            labelStatus->hide();
            timer->deleteLater();  // Delete the timer to clean up resources
        });

        // Set the timer to single-shot mode and start it with a 5-second interval
        timer->setSingleShot(true);
        timer->start(5000);
    }
}

void MainClient::on_pushButton_2_clicked()
{
    int id_client = ui->lineEdit_6->text().toInt();
    QString Nom = ui->lineEdit_7->text();
    QString Prenom = ui->lineEdit_8->text();
    int age = ui->lineEdit_9->text().toInt();

    bool updateSuccess = tmpclient.Modifier(id_client, age, Nom, Prenom);

    if (updateSuccess)
    {
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(tmpclient.afficher());
        ui->tableView->setModel(proxyModel);
        ui->tableView->setSortingEnabled(true);
        ui->tableView->update();
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Modification effectué");
        labelStatus->show();
        QTimer *timer = new QTimer(this);

        // Connect the timeout signal to a slot that hides the label
        connect(timer, &QTimer::timeout, [=]() {
            labelStatus->hide();
            timer->deleteLater();  // Delete the timer to clean up resources
        });

        // Set the timer to single-shot mode and start it with a 5-second interval
        timer->setSingleShot(true);
        timer->start(5000);
    }
    else
    {
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Modification non effectué");
        labelStatus->show();
        QTimer *timer = new QTimer(this);

        // Connect the timeout signal to a slot that hides the label
        connect(timer, &QTimer::timeout, [=]() {
            labelStatus->hide();
            timer->deleteLater();  // Delete the timer to clean up resources
        });

        // Set the timer to single-shot mode and start it with a 5-second interval
        timer->setSingleShot(true);
        timer->start(5000);
    }
}

void MainClient::on_pushButton_3_clicked()
{
    QString combo = ui->comboBox->currentText();
    QString text = ui->lineEdit_10->text();
    int columnIndex = -1;

    if (combo == "ID")
    {
        columnIndex = 0;
    }
    else if (combo == "Nom")
    {
        columnIndex = 1;
    }
    else if (combo == "Prenom")
    {
        columnIndex = 2;
    }
    else if (combo == "Age")
    {
        columnIndex = 3;
    }

    if (columnIndex != -1)
    {
        proxyModel->setFilterKeyColumn(columnIndex);
        proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxyModel->setFilterFixedString(text);
    }
}

void MainClient::on_pushButton_4_clicked()
{
    int clientId = ui->lineEdit_11->text().toInt();
    QString fileName = QString("ClientInvoice_%1.pdf").arg(clientId);
    tmpclient.generatePDF(fileName, clientId);
}

void MainClient::on_pushButton_5_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();

    if (!selectedIndexes.isEmpty())
    {
        int selectedRow = selectedIndexes.first().row();

        int idclient = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 0)).toInt();
        QString Nom = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 1)).toString();
        QString Prenom = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 2)).toString();
        int Age = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 4)).toInt();

        QPrintDialog printDialog(this);
        if (printDialog.exec() == QDialog::Accepted)
        {
            QPrinter *printer = printDialog.printer();
            QPainter painter;
            painter.begin(printer);
            painter.drawText(100, 100, QString(" ID Client: %1\nNom: %2\nPrenom: %3\nAge %4").arg(idclient).arg(Nom).arg(Prenom).arg(Age));
            painter.end();
        }
    }
    else
    {
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Veuillez selectionner une ligne");
        labelStatus->show();
        QTimer *timer = new QTimer(this);

        // Connect the timeout signal to a slot that hides the label
        connect(timer, &QTimer::timeout, [=]() {
            labelStatus->hide();
            timer->deleteLater();  // Delete the timer to clean up resources
        });

        // Set the timer to single-shot mode and start it with a 5-second interval
        timer->setSingleShot(true);
        timer->start(5000);
    }
}

void MainClient::on_pushButton_6_clicked()
{
    c = new camera();
    c->show();
}

void MainClient::on_pushButton_7_clicked()
{
    close();
    Welcome *wel = new Welcome(this);
    wel->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    wel->show();
}

void MainClient::on_pushButton_10_clicked()
{
    close();
    Employe *emp = new Employe(this);
    emp->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    emp->show();
}

void MainClient::on_pushButton_8_clicked()
{
    close();
    Paiement *pay = new Paiement(this);
    pay->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    pay->show();
}

void MainClient::on_pushButton_11_clicked()
{
    close();
    gestion_des_voitures *voit = new gestion_des_voitures(this);
    voit->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    voit->show();
}

void MainClient::on_pushButton_9_clicked()
{
    close();
    Location *loc = new Location(this);
    loc->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    loc->show();
}
