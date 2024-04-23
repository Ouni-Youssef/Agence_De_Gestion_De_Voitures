#include "reservation.h"
#include <QMessageBox>
#include "connexion.h"

Reservation::Reservation(int id_reservation, QString nom, QString prenom, QString id_client, QDate datedebut, QDate datefin, QString statut, float frais)
{
    this->id_reservation = id_reservation;
    this->nom = nom;
    this->prenom = prenom;
    this->id_client = id_client;
    this->datedebut = datedebut;
    this->datefin = datefin;
    this->statut = statut;
    this->frais = frais;
}

bool Reservation::ajouter()
{
    QSqlQuery query;

    QString res = QString::number(id_reservation);
    QString ref = QString::number(frais, 'f', 2);

    query.prepare("insert into reservation(id_reservation, nom, prenom, id_client, datedebut, datefin, statut, frais) values(:id_reservation, :nom, :prenom, :id_client, :datedebut, :datefin, :statut, :frais)");
    query.bindValue(":id_reservation", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":id_client", id_client);
    query.bindValue(":datedebut", datedebut.toString("yyyy-MM-dd"));
    query.bindValue(":datefin", datefin.toString("yyyy-MM-dd"));
    query.bindValue(":statut", statut);
    query.bindValue(":frais", ref);

    return query.exec();
}

QSqlQueryModel *Reservation::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select *from reservation");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_client"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("datedebut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("datefin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("statut"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("frais"));
    return model;
}

bool Reservation::supprimer(int id_reservation)
{
    QSqlQuery query;
    QString res = QString::number(id_reservation);
    query.prepare("DELETE FROM reservation where id_reservation= :id_reservation");
    query.bindValue(":id_reservation", res);
    return query.exec();
}

bool Reservation::Modifier(int id_reservation1, QString nom1, QString prenom1, QString id_client1, QDate datedebut1, QDate datefin1, QString statut1, float frais1)
{
    QSqlQuery query;
    QString res = QString::number(id_reservation1);
    QString ref = QString::number(frais1, 'f', 2);

    QString updateQuery = "UPDATE reservation SET ";
    bool fieldsModified = false;

    if (!nom1.isEmpty())
    {
        updateQuery += "nom = :nom, ";
        fieldsModified = true;
    }
    if (!prenom1.isEmpty())
    {
        updateQuery += "prenom = :prenom, ";
        fieldsModified = true;
    }
    if (!id_client1.isEmpty())
    {
        updateQuery += "id_client = :id_client, ";
        fieldsModified = true;
    }
    if (!datedebut1.isNull())
    {
        updateQuery += "datedebut = :datedebut, ";
        fieldsModified = true;
    }
    if (!datefin1.isNull())
    {
        updateQuery += "datefin = :datefin, ";
        fieldsModified = true;
    }
    if (!statut1.isEmpty())
    {
        updateQuery += "statut = :statut, ";
        fieldsModified = true;
    }
    if (frais1 != getfrais())
    {
        updateQuery += "frais = :frais, ";
        fieldsModified = true;
    }

    if (fieldsModified)
    {
        updateQuery = updateQuery.left(updateQuery.length() - 2);
    }

    updateQuery += " WHERE id_reservation = :id_reservation";

    query.prepare(updateQuery);
    query.bindValue(":id_reservation", res);
    if (!nom1.isEmpty())
        query.bindValue(":nom", nom1);
    if (!prenom1.isEmpty())
        query.bindValue(":prenom", prenom1);
    if (!id_client1.isEmpty())
        query.bindValue(":id_client", id_client1);
    if (!datedebut1.isNull())
        query.bindValue(":datedebut", datedebut1.toString("yyyy-MM-dd"));
    if (!datefin1.isNull())
        query.bindValue(":datefin", datefin1.toString("yyyy-MM-dd"));
    if (!statut1.isEmpty())
        query.bindValue(":statut", statut1);
    if (frais1 != getfrais())
        query.bindValue(":frais", ref);

    return query.exec();
}

bool Reservation::verifierExistence(int id_reservation)
{
    QSqlQuery query;
    QString res = QString::number(id_reservation);

    query.prepare("SELECT id_reservation FROM reservation WHERE id_reservation = :id_reservation");
    query.bindValue(":id_reservation", res);

    if (query.exec() && query.next())
    {
        return true;
    }
    else
    {
        return false;
    }
}
QSqlQueryModel *Reservation::rechercherAvancee(QString criteria, QString value)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QString queryString = "SELECT * FROM reservation WHERE ";


    if (criteria == "ID Client")
        queryString += "id_reservation";
    else if (criteria == "Nom")
        queryString += "nom";
    else if (criteria == "Prenom")
        queryString += "prenom";
    else
        return model;

    queryString += " LIKE :value";

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":value", "%" + value + "%");

    if (query.exec())
        model->setQuery(query);

    return model;
}

