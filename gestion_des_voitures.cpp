#include "gestion_des_voitures.h"
#include "ui_gestion_des_voitures.h"
#include <cctype>
#include <QDate>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QGraphicsScene>
#include <QSqlQueryModel>
#include <QZXing.h>
#include <QMessageBox>
#include <QPageSize>
#include "welcome.h"
#include "paiement.h"
#include "mainclient.h"
#include "employe.h"
#include "location.h"
#include <QTimer>










gestion_des_voitures::gestion_des_voitures(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_des_voitures)
{

    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->tableView->setSortingEnabled(true);
    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked(int)));
    ui->tableView->setModel(v.afficher());

}

gestion_des_voitures::~gestion_des_voitures()
{
    delete ui;
}

//bool gestion_des_voitures::is_valid_string(const QString& S){
//    // Check if the length is less than or equal to 20
//    if (S.length() > 20) {
//        return false;
//    }

//    // Check if each character is a letter, number, or space
//    for (QChar ch : S) {
//        if (!ch.isLetterOrNumber() && !ch.isSpace()) {
//            return false;
//        }
//    }
//        return true;
//}


//bool is_valid_date(const QString& dateString) {
//    // Attempt to parse the QString as a date with the format DD/MM/YYYY
//    QDate date = QDate::fromString(dateString, "dd/MM/yyyy");

//    // Check if the parsing was successful and the date is valid
//    return date.isValid();
//}

void gestion_des_voitures::on_pushButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Selection Image"),
                "Pictures",
                tr("Image Files (*.png *.jpg *.bmp *.jpeg)")
                );
    if (filename.isEmpty())  {
            return;
        }

    QPixmap pix(filename);
    ui->label_5->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    v.Setphotopath(filename);

    v.readImageFile(filename);


}





void gestion_des_voitures::connexion_etablie(){
    ui->label_13->setText("Connexion établiée");
    ui->tableView->setModel(v.afficher());
}

void gestion_des_voitures::connexion_echouee(){
    ui->label_13->setText("Connexion échouée");
}



void gestion_des_voitures::on_pushButton_2_clicked()
{
    v.setMatricule(ui->lineEdit->text());
    if (this->testfunction()&& !v.rechercher()){

    v.setModele(ui->lineEdit_3->text());
    v.setMarque(ui->lineEdit_4->text());
    v.setCouleur(ui->lineEdit_5->text());
    v.setCapacite(ui->spinBox->text());

    v.setKilometrage(ui->doubleSpinBox->text());

    if (ui->radioButton->isChecked()) {
            v.setDisponibilite("Disponible");
        }
        // else if statement
        else if (ui->radioButton_2->isChecked()) {
            v.setDisponibilite("Reservee");
        }
        // else if statement
        else if (ui->radioButton_3->isChecked()) {
            v.setDisponibilite("En utilisation");
        }


    if (ui->radioButton_4->isChecked()) {
            v.setEtatGenerale("Neuve");
        }
        // else if statement
        else if (ui->radioButton_5->isChecked()) {
            v.setEtatGenerale("Occasion");
        }
        // else if statement
        else if (ui->radioButton_6->isChecked()) {
            v.setEtatGenerale("En panne");
        }

    if (ui->radioButton_7->isChecked()) {
            v.setTypeCarburant("Essence");
        }
        // else if statement
        else if (ui->radioButton_8->isChecked()) {
            v.setTypeCarburant("Diesel");
        }
        // else if statement
        else if (ui->radioButton_9->isChecked()) {
            v.setTypeCarburant("Electrique");
        }
    v.setDernierDateEntretien(ui->dateEdit->text());
    v.setDateFinAssurance(ui->dateEdit_2->text());

    bool test=v.ajouter();
    if(test)
  {

        ui->tableView->setModel(v.afficher());//refresh
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
    else {
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

  }



bool gestion_des_voitures::containsOnlyLettersNumbersSpaces(const QString& str) {
    for (QChar ch : str) {
        if (!ch.isLetterOrNumber() && !ch.isSpace()) {
            return false;
        }
    }
    return true;
}


bool gestion_des_voitures::containsOnlyLetters(const QString& str) {
    for (QChar ch : str) {
        if (!ch.isLetter()) {
            return false;
        }
    }
    return true;
}

bool gestion_des_voitures::testfunction(){
    if (!this->containsOnlyLettersNumbersSpaces(ui->lineEdit->text())){
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Verifier la matricule");
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
        return false;
    }
    if (!this->containsOnlyLettersNumbersSpaces(ui->lineEdit_3->text())){
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Verifier le modele");
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
        return false;
    }
    if (!this->containsOnlyLetters(ui->lineEdit_4->text())){
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Verifier la marque");
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
        return false;
    }
    if (!this->containsOnlyLetters(ui->lineEdit_5->text())){
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Verifier la couleur");
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
        return false;
    }




    return true;
}


bool gestion_des_voitures::MatCheck(){
    QString valueToCheck = ui->lineEdit->text();
    QAbstractItemModel* model = ui->tableView->model();

    if (model) {
        int rowCount = model->rowCount();

        // Iterate through the rows in the first column
        for (int row = 0; row < rowCount; ++row) {
            QModelIndex index = model->index(row, 0); // Assuming the first column is at index 0

            QVariant data = model->data(index);

            if (data.toString() == valueToCheck) {

                // Perform your desired actions when the value is found
                return true; // If you only need to know if the value exists once, you can break out of the loop here
            }
        }




}
  return false;
}






void gestion_des_voitures::on_pushButton_3_clicked()
{
    if (this->MatCheck()){
        v.setMatricule(ui->lineEdit->text());
        v.supprimer();
        ui->tableView->setModel(v.afficher());


    }else{
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Matricule non existant");
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



void gestion_des_voitures::on_tableView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
            QAbstractItemModel* model = ui->tableView->model();

            // Assuming your model has 12 columns (adjust the column count accordingly)
            int columnCount = model->columnCount();
            int row = index.row();

            // Declare variables for each column's data
            QString matricule, disponibilite, modele, etatGenerale, couleur, typeCarburant,
                    dateFinAssurance, dernierDateEntretien, capacite, marque, kilometrage, photoPath;
            QByteArray photodata;

            for (int column = 0; column < columnCount; ++column) {
                QModelIndex cellIndex = model->index(row, column);
                QVariant data = model->data(cellIndex);

                // Assign data to variables based on column index
                switch (column) {
                    case 0: matricule = data.toString(); break;
                    case 1: disponibilite = data.toString(); break;
                    case 2: modele = data.toString(); break;
                    case 3: etatGenerale = data.toString(); break;
                    case 4: couleur = data.toString(); break;
                    case 5: typeCarburant = data.toString(); break;
                    case 6: dateFinAssurance = data.toString(); break;
                    case 7: dernierDateEntretien = data.toString(); break;
                    case 8: capacite = data.toString(); break;
                    case 9: marque = data.toString(); break;
                    case 10: kilometrage = data.toString(); break;
                    case 11: photodata = data.toByteArray(); break;
                    case 12: photoPath = data.toString(); break;

                }
            }
            ui->lineEdit->setText(matricule);
            v.setMatricule(matricule);
            ui->lineEdit_3->setText(modele);
            v.setModele(modele);
            ui->lineEdit_4->setText(marque);
            v.setMarque(marque);
            ui->lineEdit_5->setText(couleur);
            v.setCouleur(couleur);
            QDate entretien = QDate::fromString(dernierDateEntretien, "M/d/yyyy");
            QDate assurance = QDate::fromString(dateFinAssurance, "M/d/yyyy");
            ui->dateEdit->setDate(entretien);
            v.setDernierDateEntretien(dernierDateEntretien);

            ui->dateEdit_2->setDate(assurance);
            v.setDateFinAssurance(dateFinAssurance);
            ui->spinBox->setValue(capacite.toInt());
            v.setCapacite(capacite);
            ui->doubleSpinBox->setValue(kilometrage.toFloat());
            v.setKilometrage(kilometrage);

            if (disponibilite=="Reservee"){
                ui->radioButton_2->click();
                v.setDisponibilite("Reservee");
            }
            else if (disponibilite=="Disponible") {
                ui->radioButton->click();
                v.setDisponibilite("Disponible");

            }else if (disponibilite=="En utilisation"){
                ui->radioButton_3->click();
                v.setDisponibilite("En utilisation");

              }
            if (etatGenerale=="Neuve"){
                ui->radioButton_4->click();
                v.setEtatGenerale("Neuve");
            }
            else if (etatGenerale=="Occasion") {
                ui->radioButton_5->click();
                v.setEtatGenerale("Occasion");

            }else if (etatGenerale=="En panne"){
                ui->radioButton_6->click();
                v.setEtatGenerale("En panne");

              }

            if (typeCarburant=="Essence"){
                ui->radioButton_7->click();
                v.setEtatGenerale("Essence");
            }
            else if (typeCarburant=="Diesel") {
                ui->radioButton_8->click();
                v.setEtatGenerale("Diesel");

            }else if (typeCarburant=="Electrique"){
                ui->radioButton_9->click();
                v.setEtatGenerale("Electrique");

              }

            v.setMatricule(matricule);
            v.Setphotodat(photodata);


            ui->label_5->setPixmap(v.getimage().scaled(100,100,Qt::KeepAspectRatio));
}
}

void gestion_des_voitures::on_pushButton_4_clicked()
{
    ui->tableView->setModel(v.afficher());
    v.setMatricule(ui->lineEdit->text());
    if (this->MatCheck() && this->testfunction()){

        v.setModele(ui->lineEdit_3->text());
        v.setMarque(ui->lineEdit_4->text());
        v.setCouleur(ui->lineEdit_5->text());
        v.setCapacite(ui->spinBox->text());

        v.setKilometrage(ui->doubleSpinBox->text());

        if (ui->radioButton->isChecked()) {
                v.setDisponibilite("Disponible");
            }
            // else if statement
            else if (ui->radioButton_2->isChecked()) {
                v.setDisponibilite("Reservee");
            }
            // else if statement
            else if (ui->radioButton_3->isChecked()) {
                v.setDisponibilite("En utilisation");
            }


        if (ui->radioButton_4->isChecked()) {
                v.setEtatGenerale("Neuve");
            }
            // else if statement
            else if (ui->radioButton_5->isChecked()) {
                v.setEtatGenerale("Occasion");
            }
            // else if statement
            else if (ui->radioButton_6->isChecked()) {
                v.setEtatGenerale("En panne");
            }

        if (ui->radioButton_7->isChecked()) {
                v.setTypeCarburant("Essence");
            }
            // else if statement
            else if (ui->radioButton_8->isChecked()) {
                v.setTypeCarburant("Diesel");
            }
            // else if statement
            else if (ui->radioButton_9->isChecked()) {
                v.setTypeCarburant("Electrique");
            }
        v.setDernierDateEntretien(ui->dateEdit->text());
        v.setDateFinAssurance(ui->dateEdit_2->text());
        if (v.mis_a_jour()){

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
        else {
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

    ui->tableView->setModel(v.afficher());












    }
    else {
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Matricule n'existe pas");
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


void gestion_des_voitures::on_pushButton_6_clicked()
{

    ui->tableView->setModel(v.filter(ui->lineEdit_2->text(),ui->comboBox->currentText(),ui->dateEdit_3->text(),ui->comboBox_2->currentText()));


}

void gestion_des_voitures::on_pushButton_8_clicked()
{
    ui->tableView->setModel(v.afficher());
}

void gestion_des_voitures::onHeaderClicked(int logicalIndex){
    if (order=="DESC"){
        order ="ASC";
    }else {
        order = "DESC";
    }

    switch (logicalIndex) {
        case 0: ui->tableView->setModel(v.sorttable("MATRICULE " + order)); break;
        case 1: ui->tableView->setModel(v.sorttable("DISPONIBILITE " + order)); break;
        case 2: ui->tableView->setModel(v.sorttable("MODELE " + order)); break;
        case 3: ui->tableView->setModel(v.sorttable("ETAT_GENERALE " + order)); break;
        case 4: ui->tableView->setModel(v.sorttable("COULEUR " + order)); break;
        case 5: ui->tableView->setModel(v.sorttable("TYPE_CARBURANT " + order)); break;
        case 6: ui->tableView->setModel(v.sorttable("DATE_FIN_ASSURANCE " + order)); break;
        case 7: ui->tableView->setModel(v.sorttable("DERNIER_DATE_ENTRETIEN " + order)); break;
        case 8: ui->tableView->setModel(v.sorttable("CAPACITE " + order)); break;
        case 9: ui->tableView->setModel(v.sorttable("MARQUE " + order)); break;
        case 10: ui->tableView->setModel(v.sorttable("KILOMETRAGE " + order)); break;
        case 11: ui->tableView->setModel(v.sorttable("PHOTO " + order)); break;
        case 12: ui->tableView->setModel(v.sorttable("PHOTO_PATH " + order)); break;

}
}

void gestion_des_voitures::on_pushButton_5_clicked()
{
    QZXing *qzxing = new QZXing();
    QImage qrCodeImage = qzxing->encodeData(v.qrcodestring());

    QrCodeDialog qrCodeDialog;
    qrCodeDialog.setQrCodeImage(qrCodeImage);
    qrCodeDialog.exec();
}








void gestion_des_voitures::on_pushButton_7_clicked()
{

    QString filePath = QFileDialog::getSaveFileName(nullptr, "Export to CSV", QString(), "CSV Files (*.csv)");

        if (!filePath.isEmpty()) {
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&file);

                QAbstractItemModel *model = ui->tableView->model();
                const int rowCount = model->rowCount();
                const int columnCount = model->columnCount();

                // Write headers
                for (int col = 0; col < columnCount; ++col) {
                    if (col != 11) { // Exclude column with index 11
                        QString header = model->headerData(col, Qt::Horizontal).toString();
                        stream << '"' << header << '"';
                        if (col < columnCount - 2) {
                            stream << ',';
                        }
                    }
                }
                stream << '\n';

                // Write data
                for (int row = 0; row < rowCount; ++row) {
                    for (int col = 0; col < columnCount; ++col) {
                        if (col != 11) { // Exclude column with index 11
                            QString data = model->data(model->index(row, col), Qt::DisplayRole).toString();
                            stream << '"' << data << '"';

                            if (col < columnCount - 2) {
                                stream << ',';
                            }
                        }
                    }
                    stream << '\n';
                }

                file.close();
            }
        }
}



void gestion_des_voitures::on_pushButton_13_clicked()
{
    close();
    Welcome *wel = new Welcome(this);
    wel->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    wel->show();
}

void gestion_des_voitures::on_pushButton_12_clicked()
{
    close();
    Employe *emp = new Employe(this);
    emp->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    emp->show();
}

void gestion_des_voitures::on_pushButton_10_clicked()
{
    close();
    Location *loc = new Location(this);
    loc->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    loc->show();
}

void gestion_des_voitures::on_pushButton_11_clicked()
{
    close();
    Paiement *pay = new Paiement(this);
    pay->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    pay->show();
}

void gestion_des_voitures::on_pushButton_9_clicked()
{
    close();
    MainClient *client = new MainClient(this);
    client->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    client->show();
}
