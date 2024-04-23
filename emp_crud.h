#ifndef EMP_CRUD_H
#define EMP_CRUD_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "connexion.h"

class emp_crud
{
public:
    emp_crud();
    emp_crud(int,int,QString,QString,QString);
    QString get_nom();
    QString get_password();
    QString get_prenom();
    int get_id();
    int get_age();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool Modifier(int,int,QString,QString,QString);
private:
    QString nom,prenom,password;
    int id,age;
};
#endif // EMP_CRUD_H
