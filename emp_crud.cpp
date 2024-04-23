#include "emp_crud.h"
#include "connexion.h"
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QByteArray>

emp_crud::emp_crud()
{
    id=0;
    nom="";
    prenom="";
    age=0;
}


emp_crud::emp_crud(int id,int age,QString nom,QString prenom,QString password)
{
  this->id=id;
  this->age=age;
  this->nom=nom;
  this->prenom=prenom;
  this->password=password;
}
QString emp_crud::get_nom(){return  nom;}
QString emp_crud::get_prenom(){return prenom;}
QString emp_crud::get_password(){return password;}
int emp_crud::get_id(){return  id;}
int emp_crud::get_age(){return  age;}


bool emp_crud::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    QString res2 = QString::number(age);

    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    query.prepare("INSERT INTO EMPLOYE (CIN, NOM, PRENOM, AGE, PASSWORD) VALUES (:id, :nom, :prenom, :age, :password)");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":age", res2);
    query.bindValue(":password", hashedPassword.toHex());

    if (!query.exec())
    {
        qDebug() << "Error adding employee:" << query.lastError().text();
        return false;
    }

    return true;
}



QSqlQueryModel * emp_crud::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select cin,nom,prenom,age from employe");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));

    return model;
}

bool emp_crud::supprimer(int id)
{
   QSqlQuery query;
   QString res = QString::number(id);
   query.prepare("DELETE from EMPLOYE where CIN = :id ");
   query.bindValue(":id", res);

   if (!query.exec())
   {
      qDebug() << "Error deleting employee:" << query.lastError().text();
      return false;
   }

   return true;
}

bool emp_crud::Modifier(int CIN,int Age,QString Nom,QString Prenom,QString password)
{
    QSqlQuery query;
    QString res = QString::number(CIN);
    QString res2 = QString::number(Age);



    QString updateQuery = "UPDATE employe SET ";
    bool fieldsModified = false;

    if (!Nom.isEmpty())
    {
        updateQuery += "Nom = :Nom, ";
        fieldsModified = true;
    }
    if (!password.isEmpty())
    {
        updateQuery += "PASSWORD = :password, ";
        fieldsModified = true;
    }
    if (res2 != get_age())
    {
        updateQuery += "Age = :Age, ";
        fieldsModified = true;
    }
    if (!Prenom.isEmpty())
    {
        updateQuery += "Prenom = :Prenom, ";
        fieldsModified = true;
    }

    if (fieldsModified)
    {
        updateQuery = updateQuery.left(updateQuery.length() - 2);
    }

    updateQuery += " WHERE CIN = :cin";

    query.prepare(updateQuery);
    query.bindValue(":cin", res);
    if (!res2.isEmpty())
        query.bindValue(":Age", res2);
    if (!Nom.isEmpty())
        query.bindValue(":Nom", Nom);
    if (!Prenom.isEmpty())
        query.bindValue(":Prenom",Prenom);
    if (!password.isEmpty())
        query.bindValue(":password",password);


    return query.exec();
}
