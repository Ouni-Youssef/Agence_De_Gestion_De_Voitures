#ifndef VOITURE_H
#define VOITURE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QCoreApplication>
#include <QFile>



class Voiture
{
private:
    QString matricule,modele,marque,couleur,disponibilite,etat_generale,type_carburant,dernier_date_entretien,date_fin_assurance,photo_path;
    QString capacite;
    QString kilometrage;
    QByteArray photodata;

public:
    Voiture();
    Voiture(QString mat, QString mod, QString mar, QString col, int cap, float km,
            QString dispo, QString etat, QString carbu, QString date_entretien,
            QString date_assurance, QString path);

    //setters
    void Setphotopath(const QString &newString){photo_path = newString;};

    void Setphotodat(const QByteArray& p_d ){photodata =p_d;};
void readImageFile(const QString& imagePath);


    void setMatricule(const QString& mat) {
            matricule = mat;
        }

        void setModele(const QString& mod) {
            modele = mod;
        }

        void setMarque(const QString& mar) {
            marque = mar;
        }

        void setCouleur(const QString& col) {
            couleur = col;
        }

        void setDisponibilite(const QString& disp) {
            disponibilite = disp;
        }

        void setEtatGenerale(const QString& etat) {
            etat_generale = etat;
        }

        void setTypeCarburant(const QString& carbu) {
            type_carburant = carbu;
        }

        void setDernierDateEntretien(const QString& date) {
            dernier_date_entretien = date;
        }

        void setDateFinAssurance(const QString& date) {
            date_fin_assurance = date;
        }



        void setPhotoPath(const QString& path) {
            photo_path = path;
        }

        void setCapacite(const QString& cap) {
            capacite = cap;
        }

        void setKilometrage(const QString& km) {
            kilometrage = km;
        }

    QString retrievepath();

    QSqlQueryModel * afficher();


//    QByteArray readImageFromFile(const QString& filePath);

    bool ajouter();
    bool rechercher();
    void supprimer();
    bool mis_a_jour();
    QPixmap getimage();
    QSqlQueryModel * sorttable(const QString &);
    QSqlQueryModel * filter(QString value,QString crit,QString date,QString cdate);
    QString qrcodestring();




};

#endif // VOITURE_H
