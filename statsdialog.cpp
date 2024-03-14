#include "statsdialog.h"
#include "ui_dialog.h"

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
{
    QBarSeries *series = new QBarSeries();

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        QBarSet *set = new QBarSet(it.key());
        *set << it.value().first();
        series->append(set);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("STATS DES EVENTS PAR LOCATION");

    QStringList categories;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        categories << it.key();
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->label->setLayout(layout);
}
