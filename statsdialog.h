#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include <QDialog>
#include <QtCharts>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void setChartData(const QMap<QString, QList<int>> &data);
    void setChartDataassoc(const QMap<QString, double> &data);
    void setChartDataemp(const QMap<QString, QList<int>> &data);
     void setPredictiveChartData();

private:
    Ui::Dialog *ui;
};

#endif // STATSDIALOG_H
