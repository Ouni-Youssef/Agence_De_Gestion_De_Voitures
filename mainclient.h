#ifndef MAINCLIENT_H
#define MAINCLIENT_H

#include "client.h"
#include <QMainWindow>
#include <QWidget>
#include <QSortFilterProxyModel>
#include "camera.h"

namespace Ui {
class MainClient;
}

class MainClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainClient(QWidget *parent = nullptr);
    ~MainClient();

public slots:
    void on_pb_supprimer_clicked();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainClient *ui;
    QSortFilterProxyModel *proxyModel;
    Client tmpclient;
    camera *c;
};

#endif // MAINCLIENT_H
