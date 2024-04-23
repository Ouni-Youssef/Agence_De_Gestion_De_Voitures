#include "paiement.h"
#include "ui_paiement.h"
#include <QMessageBox>
#include <QWidget>
#include "connexion.h"
#include "finance.h"
#include <QDebug>
#include <algorithm>
#include "piechartwidget.h"
#include <QFileDialog>
#include "welcome.h"
#include "location.h"
#include "gestion_des_voitures.h"
#include "mainclient.h"
#include "employe.h"
#include <QTimer>

Paiement::Paiement(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Paiement),
      Ftmp(),
      proxyModel(new QSortFilterProxyModel(this)),
      pieChartWidget(nullptr),
      files()
{
    proxyModel->setSourceModel(Ftmp.afficher());
    ui->setupUi(this);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->update();

    connect(ui->sendBtn, SIGNAL(clicked()), this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    QSqlQuery query("SELECT ID_CLIENT FROM CLIENT");
    while (query.next()) {
        QString value = query.value(0).toString();
        ui->comboBox_4->addItem(value);
        ui->comboBox_5->addItem(value);
    }
}

Paiement::~Paiement()
{
    delete ui;
}

int Paiement::getNextIdFactureFromDatabase()
{
    QSqlQuery query;
    query.exec("SELECT MAX(idFacture) FROM FACTURE");
    query.next();

    QVariant value = query.value(0);

    if (value.isNull())
        return 1;
    else
        return value.toInt() + 1;
}

void Paiement::on_BtnAjouter_clicked()
{
    int id = ui->comboBox_4->currentText().toInt();
    int montant = ui->lineEdit_2->text().toInt();
    QString status = ui->comboBox->currentText();
    QDate date = ui->dateEdit->date();
    int nextId = Paiement::getNextIdFactureFromDatabase();
    Facture F(nextId, id, montant, status, date);

    bool test = F.ajouter();

    if (test)
    {
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(Ftmp.afficher());
        ui->tableView->setModel(proxyModel);
        ui->tableView->setSortingEnabled(true);
        ui->tableView->update();
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Ajout effectué");
        labelStatus->show();
        QTimer *timer = new QTimer(this);

        // Connect the timeout signal to a slot that hides the label
        connect(timer, &QTimer::timeout, [=]() {
            labelStatus->hide();
            timer->deleteLater();  // Delete the timer to clean up resources
        });

        // Set the timer to single-shot mode and start it with a 5-second interval
        timer->setSingleShot(true);
        timer->start(5000);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Id Exist"), QMessageBox::Cancel);
    }
}

void Paiement::on_BtnRecherche_clicked()
{
    QString combo = ui->comboBox_2->currentText();
    QString text = ui->lineEdit_Recherche->text();
    int columnIndex = -1;
    if (combo == "idFacture")
    {
        columnIndex = 0;
    }
    else if (combo == "idClient")
    {
        columnIndex = 2;
    }
    else if (combo == "Status")
    {
        columnIndex = 3;
    }
    if (columnIndex != -1)
    {
        proxyModel->setFilterKeyColumn(columnIndex);
        proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxyModel->setFilterFixedString(text);
    }
}

void Paiement::on_pushButton_clicked()
{
    int id = ui->lineEdit_Supprimer->text().toInt();
    bool test = Ftmp.supprimer(id);

    if (test)
    {
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(Ftmp.afficher());
        ui->tableView->setModel(proxyModel);
        ui->tableView->setSortingEnabled(true);
        ui->tableView->update();
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("Suppression effectué");
        labelStatus->show();
        QTimer *timer = new QTimer(this);

        // Connect the timeout signal to a slot that hides the label
        connect(timer, &QTimer::timeout, [=]() {
            labelStatus->hide();
            timer->deleteLater();  // Delete the timer to clean up resources
        });

        // Set the timer to single-shot mode and start it with a 5-second interval
        timer->setSingleShot(true);
        timer->start(5000);
    }
    else
    {
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("ID non existant");
        labelStatus->show();
        QTimer *timer = new QTimer(this);

        // Connect the timeout signal to a slot that hides the label
        connect(timer, &QTimer::timeout, [=]() {
            labelStatus->hide();
            timer->deleteLater();  // Delete the timer to clean up resources
        });

        // Set the timer to single-shot mode and start it with a 5-second interval
        timer->setSingleShot(true);
        timer->start(5000);
    }
}

void Paiement::on_BtnAjouter_2_clicked()
{
    int id_facture = ui->lineEdit_facture->text().toInt();

    bool exists = Ftmp.exist_supprimer(id_facture);

    if (exists)
    {
        int idC = ui->comboBox_5->currentText().toInt();
        int Montant = ui->lineEdit_4->text().toInt();
        QString statut = ui->comboBox_3->currentText();
        QDate Date = ui->dateEdit_2->date();

        bool updateSuccess = Ftmp.Modifier(id_facture, idC, Montant, statut, Date);

        if (updateSuccess)
        {
            ui->tableView->setModel(Ftmp.afficher());
            QLabel *labelStatus = new QLabel(this);
            labelStatus->setText("Modification effectué");
            labelStatus->show();
            QTimer *timer = new QTimer(this);

            // Connect the timeout signal to a slot that hides the label
            connect(timer, &QTimer::timeout, [=]() {
                labelStatus->hide();
                timer->deleteLater();  // Delete the timer to clean up resources
            });

            // Set the timer to single-shot mode and start it with a 5-second interval
            timer->setSingleShot(true);
            timer->start(5000);
        }
        else
        {
            QLabel *labelStatus = new QLabel(this);
            labelStatus->setText("Modification non effectué");
            labelStatus->show();
            QTimer *timer = new QTimer(this);

            // Connect the timeout signal to a slot that hides the label
            connect(timer, &QTimer::timeout, [=]() {
                labelStatus->hide();
                timer->deleteLater();  // Delete the timer to clean up resources
            });

            // Set the timer to single-shot mode and start it with a 5-second interval
            timer->setSingleShot(true);
            timer->start(5000);
        }
    }
    else
    {
        QLabel *labelStatus = new QLabel(this);
        labelStatus->setText("ID n'existe pas");
        labelStatus->show();
        QTimer *timer = new QTimer(this);

        // Connect the timeout signal to a slot that hides the label
        connect(timer, &QTimer::timeout, [=]() {
            labelStatus->hide();
            timer->deleteLater();  // Delete the timer to clean up resources
        });

        // Set the timer to single-shot mode and start it with a 5-second interval
        timer->setSingleShot(true);
        timer->start(5000);
    }
}

void Paiement::on_pushButton_2_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();

    if (!selectedIndexes.isEmpty())
    {
        int selectedRow = selectedIndexes.first().row();

        int idfacture = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 0)).toInt();
        int Montant = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 1)).toInt();
        int idclient = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 2)).toInt();
        QString Status = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 4)).toString();

        QPrintDialog printDialog(this);
        if (printDialog.exec() == QDialog::Accepted)
        {
            QPrinter *printer = printDialog.printer();
            QPainter painter;
            painter.begin(printer);
            painter.drawText(100, 100, QString(" ID Facture: %1\nMontant: %2\nID Client: %3\nStatus %4").arg(idfacture).arg(Montant).arg(idclient).arg(Status));
            painter.end();
        }
    }
    else
    {
        QMessageBox::warning(this, "Print", "Please select a row to print.");
    }
}

void Paiement::on_ShowStats_clicked()
{
    QMap<int, QPair<int, double>> statistics = Facture::calculateClientStatistics();

    QGraphicsScene *scene = new QGraphicsScene();
    QPieSeries *pieSeries = new QPieSeries();
    QList<QColor> sliceColors = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta};
    double totalMontantAllClients = 0.0;
    for (auto it = statistics.begin(); it != statistics.end(); ++it)
    {
        totalMontantAllClients += it.value().second;
    }

    QVector<QPieSlice *> slices;
    int colorIndex = 0;
    for (auto it = statistics.begin(); it != statistics.end(); ++it)
    {
        int idclient = it.key();
        double totalMontant = it.value().second;
        double percentage = (totalMontant / totalMontantAllClients) * 100;
        QString label = QString("IDClient: %1\nPercentage: %2%")
                            .arg(idclient)
                            .arg(QString::number(percentage, 'f', 2));
        QPieSlice *slice = pieSeries->append(label, totalMontant);
        slice->setExploded();
        slice->setColor(sliceColors.at(colorIndex % sliceColors.size()));
        slice->setLabel(QString("Client %2 %1%").arg(QString::number(percentage, 'f', 2)).arg(idclient));
        slices.append(slice);
        colorIndex++;
    }

    for (const auto &slice : slices)
    {
        pieSeries->append(slice);
    }

    QtCharts::QChartView *chartView = new QtCharts::QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->addSeries(pieSeries);
    chartView->chart()->setTitle("Client Statistics By Total Montant");

    chartView->setFixedSize(600, 400);

    scene->addWidget(chartView);

    ui->graphicsView_5->setScene(scene);
}

void Paiement::on_pushButton_3_clicked()
{
    int clientId = ui->lineEdit_5->text().toInt();
    QString fileName = QString("ClientInvoice_%1.pdf").arg(clientId);
    Ftmp.generatePDF(fileName, clientId);
}

void Paiement::browse()
{
    files.clear();
    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec())
        files = dialog.selectedFiles();
    QString fileListString;
    foreach (QString file, files)
        fileListString.append("\"" + QFileInfo(file).fileName() + "\" ");
    ui->file->setText(fileListString);
}

void Paiement::sendMail()
{
    Smtp *smtp = new Smtp("khalyylgam@gmail.com", "uexw goyy vasj awxz", "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if (!files.isEmpty())
        smtp->sendMail("khalyylgam@gmail.com", ui->rcpt->text(), ui->subject->text(), ui->msg->toPlainText(), files);
    else
        smtp->sendMail("khalyylgam@gmail.com", ui->rcpt->text(), ui->subject->text(), ui->msg->toPlainText());
}

void Paiement::mailSent(QString status)
{
    if (status == "Message sent")
        QMessageBox::warning(nullptr, tr("Qt Simple SMTP client"), tr("Message sent!\n\n"));
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
}

void Paiement::on_pushButton_7_clicked()
{
    close();
    Welcome *wel = new Welcome(this);
    wel->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    wel->show();
}

void Paiement::on_pushButton_10_clicked()
{
    close();
    Employe *emp = new Employe(this);
    emp->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    emp->show();
}

void Paiement::on_pushButton_8_clicked()
{
    close();
    Location *location = new Location(this);
    location->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    location->show();
}

void Paiement::on_pushButton_11_clicked()
{
    close();
    gestion_des_voitures *voiture = new gestion_des_voitures(this);
    voiture->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    voiture->show();
}

void Paiement::on_pushButton_9_clicked()
{
    close();
    MainClient *client = new MainClient(this);
    client->setStyleSheet("QMainWindow {\n    background-image: url(C:/Users/ouniy/Desktop/projet c++/bg.jpg);\n    background-repeat: no-repeat;\n    background-position: center;\n	\n}\n");

    client->show();
}
