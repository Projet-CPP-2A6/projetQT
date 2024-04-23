#include "statdialog.h"
#include "ui_dialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QMessageBox>
#include <QPainter>
#include <QtCharts>
#include <Eigen/Dense> // Include Eigen library headers

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

void Dialog::setChartData(const QMap<QString, double> &data)
{
    QPieSeries *series = new QPieSeries();

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        QString label = it.key() + " (" + QString::number(it.value(), 'f', 2) + "%)";
        series->append(label, it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Percentage of montant_association per domaine_association");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->label->setLayout(layout);
}

void Dialog::setPredictiveChartData()
{
    QSqlQuery query;
    query.prepare("SELECT montant_association, domaine_association FROM associations");
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to retrieve data from the database.");
        return;
    }

    QVector<double> montantData;
    QVector<double> domaineData;

    while (query.next()) {
        double montant = query.value(0).toDouble();
        QString domaine = query.value(1).toString();

        double domainValue = 0.0;
        if (domaine == "sante") {
            domainValue = 1.0;
        } else if (domaine == "environnement") {
            domainValue = 2.0;
        } else if (domaine == "social") {
            domainValue = 3.0;
        }

        montantData.append(montant);
        domaineData.append(domainValue);
    }

    Eigen::MatrixXd X(montantData.size(), 2); // Matrix to store input data
    Eigen::VectorXd y(montantData.size());    // Vector to store output data

    for (int i = 0; i < montantData.size(); ++i) {
        X(i, 0) = 1.0;          // Intercept term
        X(i, 1) = domaineData[i]; // Domain value
        y(i) = montantData[i]; // Montant value
    }

    Eigen::VectorXd coeffs;
    if (montantData.size() > 0) {
        coeffs = X.colPivHouseholderQr().solve(y);
    } else {
        qDebug() << "No data available for linear regression.";
        QMessageBox::critical(this, "Error", "No data available for linear regression.");
        return;
    }

    QMap<QString, double> predictiveData;

    for (int i = 0; i < domaineData.size(); ++i) {
        QString domain;
        double montant = coeffs[0] + coeffs[1] * domaineData[i];

        if (domaineData[i] == 1.0) {
            domain = "sante";
        } else if (domaineData[i] == 2.0) {
            domain = "environnement";
        } else if (domaineData[i] == 3.0) {
            domain = "social";
        }
        predictiveData[domain] += montant;
    }

    double totalMontant = std::accumulate(predictiveData.begin(), predictiveData.end(), 0.0,
                                          [](double sum, const QMap<QString, double>::mapped_type& p) {
                                              return sum + p;
                                          });

    if (totalMontant > 0) {
        for (auto& p : predictiveData) {
            p = (p / totalMontant) * 100.0;
        }
    } else {
        qDebug() << "Total montant is zero. Cannot normalize data.";
        QMessageBox::critical(this, "Error", "Total montant is zero. Cannot normalize data.");
        return;
    }

    setChartData(predictiveData);
}


