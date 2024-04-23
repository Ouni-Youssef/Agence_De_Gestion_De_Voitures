#include "location.h"
#include "ui_reservation.h"
#include "reservation.h"
#include "connexion.h"
#include <QMessageBox>
#include <QPrintDialog>
#include <QPainter>
#include <QPrinter>
#include "welcome.h"
#include "gestion_des_voitures.h"
#include "paiement.h"
#include "mainclient.h"
#include "employe.h"
#include <QTimer>

Location::Location(QWidget *parent) : QMainWindow(parent), ui(new Ui::Location)
{
    Reservation resv;
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(resv.afficher());
    ui->setupUi(this);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->update();

    QSqlQuery query("SELECT ID_CLIENT FROM CLIENT");
    while (query.next())
    {
        QString value = query.value(0).toString(); // Assuming the column index is 0
        ui->comboBox_4->addItem(value);
        ui->comboBox_5->addItem(value);
    }
}

Location::~Location()
{
    delete ui;
}

void Location::on_pushButton_clicked()
{
    int id_reservation = ui->lineEdit_2->text().toInt();
    QString nom = ui->lineEdit_7->text();
    QString prenom = ui->lineEdit_3->text();
    QString id_client = ui->comboBox_5->currentText();
    QDate datedebut = ui->dateEdit->date();
    QDate datefin = ui->dateEdit_2->date();
    QString statut = ui->comboBox->currentText();
    float frais = ui->lineEdit_8->text().toFloat();

    Reservation R(id_reservation, nom, prenom, id_client, datedebut, datefin, statut, frais);
    bool test = R.ajouter();
    if (test)
    {
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(resv.afficher());
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

void Location::on_pushButton_2_clicked()
{
    int id_reservation = ui->lineEdit_9->text().toInt();

    Reservation resv;
    bool test = resv.supprimer(id_reservation);
    if (test)
    {
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(resv.afficher());
        ui->tableView->setModel(proxyModel);
        ui->tableView->setSortingEnabled(true);
        ui->tableView->update();
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Suppression effectué");
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

void Location::on_pushButton_3_clicked()
{
    int id_reservation = ui->lineEdit_11->text().toInt();

    bool exists = resv.verifierExistence(id_reservation);

    if (exists)
    {
        QString nom = ui->lineEdit_15->text();
        QString prenom = ui->lineEdit_14->text();
        QString id_client = ui->comboBox_4->currentText();
        QDate datedebut = ui->dateEdit_3->date();
        QDate datefin = ui->dateEdit_4->date();
        QString statut = ui->comboBox_2->currentText();
        float frais = ui->lineEdit_17->text().toFloat();

        bool updateSuccess = resv.Modifier(id_reservation, nom, prenom, id_client, datedebut, datefin, statut, frais);

        if (updateSuccess)
        {
            proxyModel = new QSortFilterProxyModel(this);
            proxyModel->setSourceModel(resv.afficher());
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
    else
    {
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("ID n'existe pas");
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

void Location::on_pushButton_4_clicked()
{
    QString criteria = ui->comboBox_3->currentText();
    QString value = ui->lineEdit_4->text();

    // Perform advanced search
    QSqlQueryModel *searchResults = resv.rechercherAvancee(criteria, value);

    // Display search results in the table view
    ui->tableView_2->setModel(searchResults);
}

void Location::on_pushButton_6_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();

    if (!selectedIndexes.isEmpty())
    {
        int selectedRow = selectedIndexes.first().row();

        int id_reservation = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 0)).toInt();
        QString nom = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 1)).toString();
        QString prenom = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 2)).toString();
        QString id_client = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 3)).toString();
        QDate datedebut = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 4)).toDate();
        QDate datefin = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 5)).toDate();
        QString statut = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 6)).toString();
        float frais = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 7)).toFloat();

        QPrintDialog printDialog(this);
        if (printDialog.exec() == QDialog::Accepted)
        {

            QPrinter *printer = printDialog.printer();

            QPainter painter;

            painter.begin(printer);

            painter.drawText(100, 100, QString("Printing ID: %1\nNom: %2\nPrenom: %3\nid_client: %4\n"
                                               "Datedebut: %5\nDatefin: %6\nStatut: %7\nFrais: %8\n\n")
                                     .arg(id_reservation)
                                     .arg(nom)
                                     .arg(prenom)
                                     .arg(id_client)
                                     .arg(datedebut.toString("yyyy-MM-dd"))
                                     .arg(datefin.toString("yyyy-MM-dd"))
                                     .arg(statut)
                                     .arg(QString::number(frais)));
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

void Location::on_pushButton_7_clicked()
{
    close();
    Welcome *wel = new Welcome(this);
    wel->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    wel->show();
}

void Location::on_pushButton_10_clicked()
{    close();
     Employe *emp = new Employe(this);
      emp->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

     emp->show();

}

void Location::on_pushButton_8_clicked()
{
    close();
    Paiement *pay = new Paiement(this);
    pay->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    pay->show();
}

void Location::on_pushButton_11_clicked()
{
    close();
    gestion_des_voitures *voit = new gestion_des_voitures(this);
    voit->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    voit->show();
}

void Location::on_pushButton_9_clicked()
{
    close();
    MainClient *client = new MainClient(this);
    client->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    client->show();
}
