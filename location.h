#ifndef LOCATION_H
#define LOCATION_H

#include <QMainWindow>
#include "reservation.h"
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Location; }
QT_END_NAMESPACE

class Location : public QMainWindow
{
    Q_OBJECT

public:
    Location(QWidget *parent = nullptr);
    ~Location();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::Location *ui;
    Reservation resv;
    QSortFilterProxyModel *proxyModel;
};

#endif // LOCATION_H

