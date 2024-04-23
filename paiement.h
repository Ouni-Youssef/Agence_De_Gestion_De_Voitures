#ifndef PAIEMENT_H
#define PAIEMENT_H

#include <QMainWindow>
#include "finance.h"
#include "connexion.h"
#include "smtp.h"
#include <QSortFilterProxyModel>
#include <QDateEdit>
#include <QPrintDialog>
#include <QPainter>
#include <QPrinter>
#include <QTableWidget>
#include "piechartwidget.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class Paiement; }  // Update the namespace and class name here
QT_END_NAMESPACE

class Paiement : public QMainWindow  // Update the class name here
{
    Q_OBJECT

public slots:
    void on_BtnAjouter_clicked();
    void on_BtnRecherche_clicked();
    void on_pushButton_clicked();

public:
   int getNextIdFactureFromDatabase();
   Paiement(QWidget *parent = nullptr);
    ~Paiement();

private slots:
   void on_BtnAjouter_2_clicked();

   void on_pushButton_2_clicked();

   void on_ShowStats_clicked();

   void on_pushButton_3_clicked();
   void sendMail();
   void mailSent(QString);
   void browse();

   void on_pushButton_7_clicked();

   void on_pushButton_10_clicked();

   void on_pushButton_8_clicked();

   void on_pushButton_11_clicked();

   void on_pushButton_9_clicked();

private:
    Ui::Paiement *ui;  // Update the class name here
    Facture Ftmp;
    QSortFilterProxyModel *proxyModel;
    PieChartWidget *pieChartWidget;
    QStringList files;

};
#endif // PAIEMENT_H
