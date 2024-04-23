#ifndef EMPLOYE_H
#define EMPLOYE_H

#include "emp_crud.h"
#include <QMainWindow>
#include <QWidget>
#include "connexion.h"
#include "exportexcelobject.h"
#include <QSortFilterProxyModel>
#include <QDateEdit>
#include <QPainter>
#include <QTableWidget>
#include <QGraphicsScene>
#include "stat_combo.h"
#include "cameraemp.h"
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>

namespace Ui {
class Employe;
}

class Employe : public QMainWindow
{
    Q_OBJECT

public:
    explicit Employe(QWidget *parent = nullptr);
    ~Employe();

public slots:
    void on_pb_supprimer_clicked();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_stat_clicked();
    void on_camera_clicked();
    void on_export_excel_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    QMediaPlayer *player;
    QVideoWidget *vw;
    Ui::Employe *ui;
    emp_crud tmpclient;
    QSortFilterProxyModel *proxyModel;
    stat_combo *s;
    cameraemp *c;
};

#endif // EMPLOYE_H
