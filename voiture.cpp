#include "voiture.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QByteArray>




#include <QSqlQueryModel>
#include <QPixmap>

class CustomQueryModel : public QSqlQueryModel {
public:
    QVariant data(const QModelIndex &index, int role) const override {
        if (role == Qt::DecorationRole && index.column() == 11) {
            // Assuming column 11 contains the BLOB data
            QByteArray imageData = QSqlQueryModel::data(index, Qt::DisplayRole).toByteArray();
            QPixmap image;
            image.loadFromData(imageData);

            return image;
        }

        return QSqlQueryModel::data(index, role);
    }
};




Voiture::Voiture()
{
    QString matricule = "";
    QString modele = "";
    QString marque = "";
    QString couleur = "";
    QString capacite = "";
    QString kilometrage = "";
    QString disponibilite = "";
    QString etat_generale = "";
    QString type_carburant = "";
    QString dernier_date_entretien = "";
    QString date_fin_assurance = "";
    QString alertes_mecaniques = "";
    QString photo_path = "";

}


Voiture::Voiture(QString mat, QString mod, QString mar, QString col, int cap, float km,
                 QString dispo, QString etat, QString carbu, QString date_entretien,
                 QString date_assurance, QString path )
{
    matricule = mat;
    modele = mod;
    marque = mar;
    couleur = col;
    capacite = cap;
    kilometrage = km;
    disponibilite = dispo;
    etat_generale = etat;
    type_carburant = carbu;
    dernier_date_entretien = date_entretien;
    date_fin_assurance = date_assurance;

    photo_path = path;

    if (photo_path!="")
    {

    QFile photoFile(photo_path);

        if (!photoFile.open(QIODevice::ReadOnly)) {

            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n""Click Cancel to exit."), QMessageBox::Cancel);
        }
   photodata = photoFile.readAll();
   photoFile.close();
    }


}

QSqlQueryModel *Voiture::afficher() {
    CustomQueryModel *model = new CustomQueryModel();
    model->setQuery("SELECT * FROM GESTION_DES_VOITURES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Disponibilité"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Modèle"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat générale"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Couleur"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de carburant"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date du fin de l’assurance"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Dernier date d’entretien"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Capacité"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Marque"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Kilometrage"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Photo"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Emplacement du photo"));

    return model;
}



QSqlQueryModel *Voiture::sorttable(const QString &index){
    CustomQueryModel *model = new CustomQueryModel();
    model->setQuery("SELECT * FROM GESTION_DES_VOITURES ORDER BY " +index);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Disponibilité"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Modèle"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat générale"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Couleur"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de carburant"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date du fin de l’assurance"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Dernier date d’entretien"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Capacité"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Marque"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Kilometrage"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Photo"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Emplacement du photo"));
    return model;

}








void Voiture::readImageFile(const QString& imagePath) {
    QFile imageFile(imagePath);

    if (!imageFile.open(QIODevice::ReadOnly)) {
        // Handle error opening the file
        qWarning() << "Error: Unable to open image file" << imagePath;

    }

    QByteArray imageData = imageFile.readAll();
    imageFile.close();

   photodata =imageData;

}





bool Voiture::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO GESTION_DES_VOITURES (MATRICULE, DISPONIBILITE, MODELE, ETAT_GENERALE, COULEUR, TYPE_CARBURANT, "
                  "DATE_FIN_ASSURANCE, DERNIER_DATE_ENTRETIEN, CAPACITE, MARQUE, KILOMETRAGE, PHOTO, PHOTO_PATH) "
                  "VALUES (:mat, :disp, :modl, :etat, :couleur, :carb, :assur, :ent, :cap, :mar, :kil, :pho, :pho_p)");
    query.bindValue(":mat", matricule);
    query.bindValue(":disp", disponibilite);
    query.bindValue(":modl", modele);
    query.bindValue(":etat", etat_generale);
    query.bindValue(":couleur", couleur);
    query.bindValue(":carb", type_carburant);
    query.bindValue(":assur", date_fin_assurance);
    query.bindValue(":ent", dernier_date_entretien);
    query.bindValue(":cap", capacite);
    query.bindValue(":mar", marque);
    query.bindValue(":kil", kilometrage);
    query.bindValue(":pho", photodata);  // Assuming 'photodata' is a QByteArray
    query.bindValue(":pho_p", photo_path);

    return query.exec();
}

bool Voiture::mis_a_jour(){
    QSqlQuery query;
    query.prepare("UPDATE GESTION_DES_VOITURES"
                  " SET DISPONIBILITE = :disp, MODELE = :modl, ETAT_GENERALE = :etat, COULEUR = :couleur, TYPE_CARBURANT = :carb, "
                  "DATE_FIN_ASSURANCE = :assur, DERNIER_DATE_ENTRETIEN = :ent, CAPACITE = :cap, MARQUE = :mar, KILOMETRAGE = :kil, PHOTO = :pho, PHOTO_PATH = :pho_p"
                  " WHERE MATRICULE = :mat");
    query.bindValue(":mat", matricule);
    query.bindValue(":disp", disponibilite);
    query.bindValue(":modl", modele);
    query.bindValue(":etat", etat_generale);
    query.bindValue(":couleur", couleur);
    query.bindValue(":carb", type_carburant);
    query.bindValue(":assur", date_fin_assurance);
    query.bindValue(":ent", dernier_date_entretien);
    query.bindValue(":cap", capacite);
    query.bindValue(":mar", marque);
    query.bindValue(":kil", kilometrage);
    query.bindValue(":pho", photodata);  // Assuming 'photodata' is a QByteArray
    query.bindValue(":pho_p", photo_path);

    return query.exec();


}






bool Voiture::rechercher(){
    QSqlQuery query;
    query.prepare("SELECT MATRICULE FROM GESTION_DES_VOITURES WHERE MATRICULE = :mat");
    query.bindValue(":mat",matricule);
    if (!query.exec()) {

            return false;  // Consider handling the error appropriately in your application
        }
    bool test=query.next();

    if (test){
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                    QObject::tr("Cette matricule existe.\n""dans la base de donnee."), QMessageBox::Cancel);



    }



    return test;


}

void Voiture::supprimer(){
    QSqlQuery query;
    query.prepare("DELETE FROM GESTION_DES_VOITURES WHERE MATRICULE = :mat");
    query.bindValue(":mat",matricule);

    if (query.exec()) {


        }




}

QPixmap Voiture::getimage(){
    QSqlQuery query;
    query.prepare("SELECT photo FROM GESTION_DES_VOITURES WHERE MATRICULE = :mat");
    query.bindValue(":mat", matricule); // Replace 1 with the actual ID you want to retrieve
    QPixmap pixmap;

    if (query.exec() && query.next()) {
        // Retrieve BLOB data
        QByteArray imageData = query.value("photo").toByteArray();

        // Convert BLOB data to QImage
        QImage image;
        image.loadFromData(imageData);


        if (!image.isNull()) {

            pixmap = QPixmap::fromImage(image);
        }
    }
return pixmap;
}






QString Voiture::retrievepath(){
    QSqlQuery query;
    query.prepare("SELECT PHOTO_PATH FROM GESTION_DES_VOITURES WHERE MATRICULE = :mat");
    query.bindValue(":mat", matricule);
    QString res = query.value("PHOTO_PATH").toString();
    return res;
}

QSqlQueryModel * Voiture::filter(QString value, QString crit, QString date, QString cdate) {
    CustomQueryModel *model = new CustomQueryModel();

    QString requette_1;
    QString requette_2;

    if (value.isEmpty() && date == "01/01/2000") {
        // Both value and date are empty, return an empty model
        return model;
    }

    if (!value.isEmpty() && date != "01/01/2000") {
        // Value is not empty and date is not "01/01/2000", query depends on crit and cdate
        if (crit.toLower().trimmed() == "matricule") {
            requette_1 = "upper(MATRICULE) LIKE '%" + value.toUpper() + "%'";
        } else if (crit.toLower().trimmed() == "capacité") {
            requette_1 = "upper(CAPACITE) = " + value;
        } else if (crit.toLower().trimmed() == "modèle") {
            requette_1 = "upper(MODELE) LIKE '%" + value.toUpper() + "%'";
        } else if (crit.toLower().trimmed() == "marque") {
            requette_1 = "upper(MARQUE) LIKE '%" + value.toUpper() + "%'";
        } else if (crit.toLower().trimmed() == "couleur") {
            requette_1 = "upper(COULEUR) LIKE '%" + value.toUpper() + "%'";
        }

        if (cdate.toLower().trimmed() == "dernier date d'entretien") {
            requette_2 = "AND DERNIER_DATE_ENTRETIEN LIKE '%" + date.toUpper() + "%'";
        } else if (cdate.toLower().trimmed() == "date du fin de l'assurance") {
            requette_2 = "AND DATE_FIN_ASSURANCE = '" + date.toUpper() + "'";
        }
    } else if (!value.isEmpty() && date == "01/01/2000") {
        // Value is not empty and date is "01/01/2000", query depends on crit only
        if (crit.toLower().trimmed() == "matricule") {
            requette_1 = "upper(MATRICULE) LIKE '%" + value.toUpper() + "%'";
        } else if (crit.toLower().trimmed() == "capacité") {
            requette_1 = "upper(CAPACITE) = " + value;
        } else if (crit.toLower().trimmed() == "modèle") {
            requette_1 = "upper(MODELE) LIKE '%" + value.toUpper() + "%'";
        } else if (crit.toLower().trimmed() == "marque") {
            requette_1 = "upper(MARQUE) LIKE '%" + value.toUpper() + "%'";
        } else if (crit.toLower().trimmed() == "couleur") {
            requette_1 = "upper(COULEUR) LIKE '%" + value.toUpper() + "%'";
        }
    } else if (value.isEmpty() && date != "01/01/2000") {
        // Value is empty, but date is not, query depends on cdate
        if (cdate.toLower().trimmed() == "dernier date d'entretien") {
            requette_2 = "DERNIER_DATE_ENTRETIEN LIKE '%" + date.toUpper() + "%'";
        } else if (cdate.toLower().trimmed() == "date du fin de l'assurance") {
            requette_2 = "DATE_FIN_ASSURANCE = '" + date.toUpper() + "'";
        }
    }

    QString fullQuery = "SELECT * FROM GESTION_DES_VOITURES WHERE " + requette_1 + requette_2;
    model->setQuery(fullQuery);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Disponibilité"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Modèle"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat générale"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Couleur"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de carburant"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date du fin de l’assurance"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Dernier date d’entretien"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Capacité"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Marque"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Kilometrage"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Photo"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Emplacement du photo"));

    return model;
}

QString Voiture::qrcodestring(){
    return "Matricule : "+matricule+"\nModèle : "+modele+"\nCouleur : "+couleur+"\nCapacité : "+capacite+"\nType de carburant : "+type_carburant+"\nMarque : "+marque+"\nKilometrage : "+kilometrage+"\nDate du fin de l’assurance : "+date_fin_assurance+"\nDernier date d’entretien : "+dernier_date_entretien+"\nEtat générale : "+etat_generale+"\nDisponibilité : "+disponibilite;
}


















