#include "connexion.h"
#include "finance.h"
#include <QDesktopServices>
#include <QUrl>

Facture::Facture(){
}
Facture::Facture(int idF,int idC,int Montant,QString Status,QDate Date){
        this->idFacture = idF;
        this->idClient = idC;
    this->Montant = Montant;
    this->Status = Status;
    this->Date = Date;
    }

bool Facture::ajouter(){
   QSqlQuery query;
   QString res = QString::number(idClient);
   QString res3 = QString::number(Montant);
   query.prepare("INSERT INTO FACTURE(IDFACTURE,IDCLIENT,MONTANT,STATUS,DateF) VALUES (:idF,:idC,:Montant,:Status,:date)");
   query.bindValue(":idC",res);
   query.bindValue(":idF",idFacture);
   query.bindValue(":Montant",res3);
   query.bindValue(":date",Date.toString("yyyy-MM-dd"));
   query.bindValue(":Status",Status);

return query.exec();
}
bool Facture::exist_supprimer(int id) {
    QSqlQuery query;
    query.prepare("SELECT idFacture FROM FACTURE WHERE idFacture = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return true;
    }

    return false;
}

bool Facture::exist_client(int id) {
    QSqlQuery query;
    query.prepare("SELECT idClient FROM FACTURE WHERE idClient = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return true;
    }

    return false;
}


bool Facture::exist_ajouter(int id) {
    QSqlQuery query;
    query.prepare("SELECT idFacture FROM FACTURE WHERE idFacture = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {

        return false;
    }

    return true;
}



bool Facture::supprimer(int id){
    QSqlQuery query;
    QString res = QString::number(id);
    if (exist_supprimer(id)){
    query.prepare("DELETE from FACTURE where IDFACTURE= :id");
    query.bindValue(":id",res);

    return query.exec();
}
    return false;

}

QSqlQueryModel * Facture::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from FACTURE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDFacture"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("IDClient"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Montant"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));


    return model;
}

bool Facture::Modifier(int idF,int idC,int Montant,QString Status,QDate Date)
{
    QSqlQuery query;
    QString res = QString::number(idF);
    QString res2 = QString::number(idC);
    QString ref = QString::number(Montant);



    QString updateQuery = "UPDATE facture SET ";
    bool fieldsModified = false;

    if (!Status.isEmpty())
    {
        updateQuery += "Status = :Status, ";
        fieldsModified = true;
    }
    if (res2 != getIDC())
    {
        updateQuery += "IDClient = :idC, ";
        fieldsModified = true;
    }
    if (!Date.isNull())
    {
        updateQuery += "DateF = :Date, ";
        fieldsModified = true;
    }
    if (ref != getMontant())
    {
        updateQuery += "Montant = :Montant, ";
        fieldsModified = true;
    }

    if (fieldsModified)
    {
        updateQuery = updateQuery.left(updateQuery.length() - 2);
    }

    updateQuery += " WHERE IDFACTURE = :facture";

    query.prepare(updateQuery);
    query.bindValue(":facture", res);
    if (!res2.isEmpty())
        query.bindValue(":idC", res2);
    if (!ref.isEmpty())
        query.bindValue(":Montant", ref);
    if (!Status.isEmpty())
        query.bindValue(":Status", Status);
    if (!Date.isNull())
        query.bindValue(":Date", Date.toString("yyyy-MM-dd"));


    return query.exec();
}

QMap<int, QPair<int, double>> Facture::calculateClientStatistics() {
    QMap<int, QPair<int, double>> clientStatistics;

    QSqlQuery query("SELECT IDCLIENT, COUNT(IDFACTURE) AS NumberOfInvoices, SUM(MONTANT) AS TotalMontant FROM FACTURE GROUP BY IDCLIENT");

    while (query.next()) {
        int idclient = query.value("IDCLIENT").toInt();
        int numberOfInvoices = query.value("NumberOfInvoices").toInt();
        double totalMontant = query.value("TotalMontant").toInt();

        clientStatistics[idclient] = qMakePair(numberOfInvoices, totalMontant);
    }

    return clientStatistics;
}

void Facture::generatePDF(const QString &fileName,int id)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier PDF:" << file.errorString();
        return;
    }

    QSqlQuery query;
    QString res = QString::number(id);
    if (exist_client(id)){
    query.prepare("SELECT idFacture,Montant,Status FROM FACTURE WHERE idClient = :id");
    query.bindValue(":id", res);
    query.exec();
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QPainter painter;
    painter.begin(&printer);

    painter.drawText(100, 100, "La Facture du client avec ID: "+res);

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
    else
        QMessageBox::critical(nullptr, "PDF Not Generated", "Client ID Doesn't exist!");


}


