#ifndef FINANCE_H
#define FINANCE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "connexion.h"
#include <QDateEdit>
#include <QPrintDialog>
#include <QPainter>
#include <QPrinter>
#include <QMap>
#include <QFile>
#include <QSqlRecord>
#include <QPair>
#include <QDebug>
class Facture
{
private:
    int idFacture,idClient,Montant;
    QString Status;
    QDate Date;

public:
    Facture();
    Facture(int,int,int,QString,QDate);
    static QMap<int, QPair<int, double>> calculateClientStatistics();


    //Getters
    QString getStatus(){
        return Status;
    }
    int getIDF(){
        return idFacture;
    }
    int getIDC(){
        return idClient;
    }
    int getMontant(){
        return Montant;
    }
    QDate getDate(){
        return Date;
    }

    //Setters
    void setStatus(QString Status){
        this->Status=Status;
    }
    void setIDF(int idFacture){
        this->idFacture=idFacture;
    }
    void setIDC(int idClient){
        this->idClient=idClient;
    }
    void setMontant(int Montant){
        this->Montant=Montant;
    }
    //Fonctionnalité
    QSqlQueryModel * afficher();
    bool ajouter();
    bool supprimer(int);
    bool exist_supprimer(int);
    bool exist_ajouter(int);
    bool Modifier(int,int,int,QString,QDate);
    void generatePDF(const QString &fileName, int);
    bool exist_client(int);

};

#endif // FINANCE_H
