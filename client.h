#ifndef CLIENT_H
#define CLIENT_H
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
#include <QUrl>
#include <QPair>
#include <QDebug>
class Client
{public:
    Client();
    Client(int,int,QString,QString);
    QString get_nom();
    QString get_prenom();
    int get_id();
    int get_age();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool Modifier(int,int,QString,QString);
    void generatePDF(const QString &fileName, int);
private:
    QString nom,prenom;
    int id,age;
};

#endif // CLIENT-H
