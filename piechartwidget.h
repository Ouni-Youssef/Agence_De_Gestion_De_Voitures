#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

class PieChartWidget : public QChartView {
    Q_OBJECT

public:
    PieChartWidget(QWidget *parent = nullptr);

public slots:
    void showPieChart(QMap<int, QPair<int, double>> statistics);

private:
    QPieSeries *pieSeries;
};

#endif // PIECHARTWIDGET_H
