#include "client.h"
#include <QDebug>
#include "connexion.h"
#include <QMessageBox>
#include <QDesktopServices>
Client::Client()
{
id=0;
nom="";
prenom="";
age=0;
}
Client::Client(int id,int age,QString nom,QString prenom)
{
  this->id=id;
  this->nom=nom;
  this->prenom=prenom;
  this->age=age;
}
QString Client::get_nom(){return  nom;}
QString Client::get_prenom(){return prenom;}
int Client::get_id(){return  id;}
int Client::get_age(){return age;}

bool Client::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
QString res1= QString::number(age);
query.prepare("INSERT INTO CLIENT (id_client, NOM, PRENOM,AGE) VALUES (:id, :nom, :prenom,:age)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":age",res1);

return    query.exec();
}

QSqlQueryModel * Client::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select ID_client,nom,prenom,age from client");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
    return model;
}

bool Client::supprimer(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("DELETE from CLIENT where id_client = :id ");
query.bindValue(":id", res);
    return    query.exec();
}

bool Client::Modifier(int idC,int ageC ,QString Nom,QString Prenom)
{
    QSqlQuery query;
    QString res = QString::number(idC);
    QString res2 = QString::number(ageC);

    QString updateQuery = "UPDATE client SET ";
    bool fieldsModified = false;

    if (!Nom.isEmpty())
    {
        updateQuery += "Nom = :Nom, ";
        fieldsModified = true;
    }
    if (!Prenom.isEmpty())
    {
        updateQuery += "Prenom = :Prenom, ";
        fieldsModified = true;
    }
    if (res != get_id())
    {
        updateQuery += "id_client = :idC, ";
        fieldsModified = true;
    }

    if (res2 != get_age())
    {
        updateQuery += "age = :age, ";
        fieldsModified = true;
    }

    if (fieldsModified)
    {
        updateQuery = updateQuery.left(updateQuery.length() - 2);
    }

    updateQuery += " WHERE id_client = :idC";

    query.prepare(updateQuery);
    query.bindValue(":idC", res);
    if (!res2.isEmpty())
        query.bindValue(":age", res2);
    if (!Nom.isEmpty())
        query.bindValue(":Nom", Nom);
    if (!Prenom.isEmpty())
        query.bindValue(":Prenom", Prenom);


    return query.exec();
}

void Client::generatePDF(const QString &fileName,int id)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier PDF:" << file.errorString();
        return;
    }

    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("SELECT id_client,AGE,NOM,PRENOM FROM CLIENT WHERE id_client = :id_client");
    query.bindValue(":id_client", res);
    query.exec();
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QPainter painter;
    painter.begin(&printer);

    painter.drawText(100, 100, "Les donnees du client avec ID: "+res);

    int row = 0;
     int yPos = 150;

     for (int col = 0; col < query.record().count(); ++col) {
         painter.drawText(100 + (col + 1) * 200, yPos - 20, query.record().fieldName(col));
     }

     while (query.next()) {
         for (int col = 0; col < query.record().count(); ++col) {
             painter.drawText(100 + (col + 1) * 200, yPos + row * 20, query.value(col).toString());
         }
         ++row;
     }

     painter.end();

     QMessageBox::information(nullptr, "PDF Generated", "PDF file has been generated successfully!");
     QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}
