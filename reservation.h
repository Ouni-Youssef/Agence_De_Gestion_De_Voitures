#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateEdit>

class Reservation
{
    int id_reservation;
    QString nom, prenom, id_client, statut;
    QDate datedebut, datefin;
    float frais;

public:
    QSqlQueryModel *rechercherAvancee(QString criteria, QString value);
    // Constructors
    Reservation() {}
    Reservation(int, QString, QString, QString, QDate, QDate, QString, float);

    // Getters
    QString getNom() { return nom; }
    QString getPrenom() { return prenom; }
    int getID() { return id_reservation; }
    QString getid_client() { return id_client; }
    QDate getdatedebut() { return datedebut; }
    QDate getdatefin() { return datefin; }
    QString getstatut() { return statut; }
    float getfrais() { return frais; }


    // Setters
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setID(int id) { id_reservation = id; }
    void setid_client(QString id_client) { this->id_client = id_client; }
    void setdatedebut(QDate db) { datedebut = db; }
    void setdatefin(QDate df) { datefin = df; }
    void setstatut(QString s) { statut = s; }
    void setfrais(float f) { frais = f; }

    // Basic functionalities related to the Reservation entity
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool Modifier(int, QString, QString, QString, QDate, QDate, QString, float);
    bool verifierExistence(int id_reservation);

};

#endif // RESERVATION_H
