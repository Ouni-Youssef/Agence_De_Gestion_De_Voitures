#ifndef GESTION_DES_VOITURES_H
#define GESTION_DES_VOITURES_H

#include <QMainWindow>
#include <QDebug>
#include <QPixmap>
#include <QGraphicsScene>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "voiture.h"
#include "qrcodedialog.h"
#include <QPageSize>
#include <QPrinter>
#include <QPainter>



QT_BEGIN_NAMESPACE
namespace Ui { class gestion_des_voitures; }
QT_END_NAMESPACE

class gestion_des_voitures : public QMainWindow
{
    Q_OBJECT

public:

    QString order = "DESC";
    gestion_des_voitures(QWidget *parent = nullptr);
    ~gestion_des_voitures();
    bool is_valid_string(const QString&);
    bool is_valid_date(const QString&);
    void connexion_etablie();
    void connexion_echouee();
    bool containsOnlyLettersNumbersSpaces(const QString& str);
    bool containsOnlyLetters(const QString& str);
    bool MatCheck();
    bool testfunction();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();


    void onHeaderClicked(int logicalIndex);

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::gestion_des_voitures *ui;
    Voiture v;

};
#endif // GESTION_DES_VOITURES_H
