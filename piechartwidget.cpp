#include "piechartwidget.h"

PieChartWidget::PieChartWidget(QWidget *parent) : QChartView(parent) {
    pieSeries = new QPieSeries();
    QChart *chart = new QChart();
    chart->addSeries(pieSeries);
    chart->setTitle("Client Statistics");
    chart->legend()->hide();

    setChart(chart);
    setRenderHint(QPainter::Antialiasing);
}

void PieChartWidget::showPieChart(QMap<int, QPair<int, double>> statistics) {
    pieSeries->clear();

    for (auto it = statistics.begin(); it != statistics.end(); ++it) {
        int idclient = it.key();
        int numberOfInvoices = it.value().first;
        double totalMontant = it.value().second;

        QString label = QString("IDClient: %1\nNumber of Invoices: %2\nTotal Montant: %3")
                            .arg(idclient)
                            .arg(numberOfInvoices)
                            .arg(totalMontant);

        QPieSlice *slice = pieSeries->append(label, numberOfInvoices);
        slice->setExploded();
    }
}
