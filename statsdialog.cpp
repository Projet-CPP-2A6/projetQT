#include "statsdialog.h"
#include "ui_dialog.h"
#include <QPieSeries>
#include <QPieSlice>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setChartData(const QMap<QString, QList<int>> &data)
{   QPieSeries *series = new QPieSeries();

    int totalEvents = 0;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        totalEvents += it.value().first();
    }

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        double percentage = (static_cast<double>(it.value().first()) / totalEvents) * 100.0;
        QString label = QString("%1 (%2%)").arg(it.key()).arg(QString::number(percentage, 'f', 1));
        series->append(label, it.value().first());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("STATS DES EVENTS PAR LOCATION");

    series->setLabelsVisible();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->label->setLayout(layout);
}
void Dialog::setChartDataemp(const QMap<QString, QList<int>> &data)
{   QPieSeries *series = new QPieSeries();

    int totalEvents = 0;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        totalEvents += it.value().first();
    }

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        double percentage = (static_cast<double>(it.value().first()) / totalEvents) * 100.0;
        QString label = QString("%1 (%2%)").arg(it.key()).arg(QString::number(percentage, 'f', 1));
        series->append(label, it.value().first());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("STATS DES EMPOLYES PAR ROLE");

    series->setLabelsVisible();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->label->setLayout(layout);
}

