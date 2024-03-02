#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QInputDialog>
#include <QSortFilterProxyModel>
#include <QSqlRecord>
#include "event.h"
#include "eventmodel.h"
#include <QRegExpValidator>
#include <qsqldatabase.h>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);


        ui->stackedWidget->setCurrentIndex(0);
   class event e;

   QRegExpValidator *dateValidator = new QRegExpValidator(QRegExp("[0-9]{1,2}/[0-9]{1,2}/[0-9]{4}"), this);
       ui->ledate->setValidator(dateValidator);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbconfirm_clicked()
{
    QString nom_event=ui->lename->text();
    QString descript_event=ui->ledesc->toPlainText();
    QString location=ui->lelocation->text();
    QString date_event=ui->ledate->text();
    QSqlQuery query;
      class event e (nom_event,descript_event,location,date_event);
    bool test=e.ajouter();
    if (test)
    {
        ui->tableView->setModel(etmp.afficher());
      ui->stackedWidget->setCurrentIndex(0);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        ui->lename->clear();
        ui->ledesc->clear();
        ui->lelocation->clear();
        ui->ledate->clear();
    }else QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                QObject::tr("Ajout non effectué.\n"
                                            "Click Cancel to exit."),QMessageBox::Cancel);

}







void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView->model()->data(in).toString();

        QSqlQuery qry;
        qry.prepare("select id_event,nom_event, descript_event, location, date_event from event where event='"+val+"' " );
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lename->setText(qry.value(1).toString());
                ui->ledesc->setText(qry.value(2).toString());
                ui->lelocation->setText(qry.value(3).toString());
                ui->ledate->setText(qry.value(4).toString());
            }
}
}


void MainWindow::on_pbdeleteall_clicked()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment supprimer tous les éléments ?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            class event e;
            bool test = e.supprimerTous();

            if (test)
            {
                ui->tableView->setModel(e.afficher());
                QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("Suppression de tous les éléments effectuée.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                        QObject::tr("Suppression de tous les éléments non effectuée.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
}

void MainWindow::on_pbdelete_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

        if (!selectedIndexes.isEmpty()) {
            // Récupérer l'ID de la première colonne (id_event)
            int id_event = selectedIndexes.at(0).sibling(selectedIndexes.at(0).row(), 0).data().toInt();

            class event e;
            bool test = e.supprimer(id_event);

            if (test)
            {
                ui->tableView->setModel(e.afficher());
                QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("Suppression de l'élément effectuée.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                        QObject::tr("Suppression de l'élément non effectuée.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
        else {
            QMessageBox::warning(nullptr, QObject::tr("Avertissement"),
                                 QObject::tr("Veuillez sélectionner un élément à supprimer."),
                                 QMessageBox::Cancel);
        }
}

void MainWindow::on_pbaddevent_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pbconfirm_3->setVisible(false);
}

void MainWindow::on_pbliste_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pbupdate_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                             QObject::tr("Please select an item to update."),
                             QMessageBox::Ok);
        return;
    }
    ui->pbconfirm->setVisible(false);
    ui->pbconfirm_3->setVisible(true);
    int selectedRow = selectedIndexes.first().row();
    QString nom_event = ui->tableView->model()->index(selectedRow, 1).data().toString();
    QString descript_event = ui->tableView->model()->index(selectedRow, 2).data().toString();
    QString location = ui->tableView->model()->index(selectedRow, 3).data().toString();
    QString date_event = ui->tableView->model()->index(selectedRow, 4).data().toString();

    ui->lename->setText(nom_event);
    ui->ledesc->setText(descript_event);
    ui->lelocation->setText(location);
    ui->ledate->setText(date_event);
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_pbexportpdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");

      if (!filePath.isEmpty()) {
          QPrinter printer(QPrinter::PrinterResolution);
          printer.setOutputFormat(QPrinter::PdfFormat);
          printer.setOutputFileName(filePath);

          // Set the resolution for the printer, not the QPainter
          printer.setResolution(1200);

          QPainter painter(&printer);

          // Remove the following line as setResolution is now applied to QPrinter
          // painter.setResolution(1200);

          ui->tableView->render(&painter);

          QMessageBox::information(this, "Export PDF", "PDF file exported successfully.");
      }
}


void MainWindow::on_pbsearch_clicked()
{
    // Get the search string from the line edit
       QString searchStr = ui->lesearch->text().trimmed();

       // Check if the search string is not empty
       if (!searchStr.isEmpty()) {
           // Create a filter for the SQL query
           QString filter = QString("nom_event LIKE '%%1%' OR descript_event LIKE '%%1%' OR location LIKE '%%1%' OR date_event LIKE '%%1%'")
                                .arg(searchStr);

           // Apply the filter to the SQL query
           QSqlQueryModel *filteredModel = new QSqlQueryModel();
           filteredModel->setQuery("SELECT id_event, nom_event, descript_event, location, date_event FROM event WHERE " + filter);

           // Set the filtered model to the table view
           ui->tableView->setModel(filteredModel);

           // Update the view
           ui->tableView->update();
       } else {
           // If the search string is empty, display all data
           ui->tableView->setModel(etmp.afficher());
       }
}

void MainWindow::on_pbtri_clicked()
{
 ui->tableView->setModel(e.triID());
}

void MainWindow::on_pbstat_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);  // Afficher la page 2

 class   event e;
        QBarSet *set0 = new QBarSet("");

        *set0  << e.stat("Admin")<< e.stat("Responsable RH");


        QColor color(0x6568F3);
        set0->setColor(color);

        QBarSeries *series = new QBarSeries();
        series->append(set0);




        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setBackgroundVisible(false);

        QColor bgColor(0xF4DCD3);
                       chart->setBackgroundBrush(QBrush(QColor(bgColor)));

                       chart->setBackgroundVisible(true);

        QStringList categories;
        categories  << "Admin"<< "RH";
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        QChartView *chartView = new QChartView(chart);

        chartView->setMinimumWidth(500);
        chartView->setMinimumHeight(300);
        chartView->setParent(ui->statContainer);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chartView->show();
}

void MainWindow::on_pbconfirm_3_clicked()
{

}

void MainWindow::on_pbrefresh_clicked()
{
    // Get the search string from the line edit
       QString searchStr = ui->lesearch->text().trimmed();

       // Check if the search string is not empty
       if (!searchStr.isEmpty()) {
           // Create a filter for the SQL query
           QString filter = QString("nom_event LIKE '%%1%' OR descript_event LIKE '%%1%' OR location LIKE '%%1%' OR date_event LIKE '%%1%'")
                                .arg(searchStr);

           // Apply the filter to the SQL query
           QSqlQueryModel *filteredModel = new QSqlQueryModel();
           filteredModel->setQuery("SELECT id_event, nom_event, descript_event, location, date_event FROM event WHERE " + filter);

           // Set the filtered model to the table view
           ui->tableView->setModel(filteredModel);

           // Update the view
           ui->tableView->update();
       } else {
           // If the search string is empty, display all data
           ui->tableView->setModel(etmp.afficher());
       }
}
