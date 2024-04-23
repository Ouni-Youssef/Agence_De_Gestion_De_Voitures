#include "employe.h"
#include "ui_employe.h"
#include "stat_combo.h"
#include "emp_crud.h"
#include <QMessageBox>
#include "welcome.h"
#include "mainclient.h"
#include "paiement.h"
#include "gestion_des_voitures.h"
#include "location.h"
#include <QTimer>

Employe::Employe(QWidget *parent) : QMainWindow(parent), ui(new Ui::Employe) {
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(tmpclient.afficher());
    ui->setupUi(this);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->update();
}

Employe::~Employe() {
    delete ui;
}

void Employe::on_pb_supprimer_clicked() {
    int id = ui->lineEdit_4->text().toInt();
    bool test = tmpclient.supprimer(id);

    if (test) {
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(tmpclient.afficher());
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
    } else {
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

void Employe::on_pushButton_clicked() {
    int id = ui->lineEdit->text().toInt();
    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_3->text();
    QString password = ui->lineEdit_11->text();
    int age = ui->lineEdit_5->text().toInt();
    emp_crud c(id,age,nom, prenom,password);
    bool test = c.ajouter();

    if (test) {
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

void Employe::on_pushButton_3_clicked()

    {
            QString combo =ui->comboBox->currentText();
            QString text = ui->lineEdit_10->text();
            int columnIndex = -1;
            if (combo == "CIN") {
                columnIndex = 0;
            } else if (combo == "Nom") {
                columnIndex = 1;
            } else if (combo == "Prenom") {
                columnIndex = 2;
            } else if (combo == "Age") {
                columnIndex = 3;
            }
            if (columnIndex != -1) {
                proxyModel->setFilterKeyColumn(columnIndex);
                proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
                proxyModel->setFilterFixedString(text);
            }
    }

void Employe::on_stat_clicked()
{
   s = new stat_combo();

  s->setWindowTitle("statistique ComboBox");
  s->choix_bar();
  s->show();

}

void Employe::on_camera_clicked()
{
    c= new cameraemp();
    c->show();
}



void Employe::on_export_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("hamza"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tableView);

    obj.addField(0, "entier", "char(20)");
    obj.addField(1, "reel", "char(20)");
    obj.addField(2, "combobox", "char(20)");
    obj.addField(3, "lineedit", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

void Employe::on_pushButton_2_clicked()
{
    {
        int cin = ui->lineEdit_7->text().toInt();
        QString nom = ui->lineEdit_8->text();
        QString prenom = ui->lineEdit_6->text();
        QString password = ui->lineEdit_12->text();
        int age = ui->lineEdit_9->text().toInt();


            bool updateSuccess = tmpclient.Modifier(cin, age, nom, prenom, password);

            if (updateSuccess)
            {
                ui->tableView->setModel(tmpclient.afficher());
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
    }

void Employe::on_pushButton_4_clicked()
{
    close();
    Welcome *wel = new Welcome(this);
    wel->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    wel->show();
}


void Employe::on_pushButton_5_clicked()
{
    close();
    MainClient *client = new MainClient(this);
    client->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    client->show();
}

void Employe::on_pushButton_6_clicked()
{
    close();
    Paiement *pay = new Paiement(this);
    pay->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    pay->show();
}

void Employe::on_pushButton_7_clicked()
{
    close();
    gestion_des_voitures *voit = new gestion_des_voitures(this);
    voit->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    voit->show();
}

void Employe::on_pushButton_8_clicked()
{
    close();
    Location *loc = new Location(this);
    loc->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    loc->show();
}
