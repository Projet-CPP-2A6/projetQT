#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statsdialog.h"

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
ArtNexus::ArtNexus(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

        ui->stackedWidget->setCurrentIndex(0);
   class event e;

   QRegExpValidator *dateValidator = new QRegExpValidator(QRegExp("[0-9]{1,2}/[0-9]{1,2}/[0-9]{4}"), this);
       ui->ledate->setValidator(dateValidator);
        ui->ledate_3->setValidator(dateValidator);
         QMetaObject::invokeMethod(this, "on_pbrefresh_clicked", Qt::QueuedConnection);
ui->pbrefresh->setVisible(false);

}

ArtNexus::~ArtNexus()
{
    delete ui;
}

void ArtNexus::on_pbconfirm_clicked()
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







void ArtNexus::on_tableView_clicked(const QModelIndex &index)
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


void ArtNexus::on_pbdeleteall_clicked()
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

void ArtNexus::on_pbdelete_clicked()
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

void ArtNexus::on_pbaddevent_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pbconfirm->setVisible(true);
}

void ArtNexus::on_pbliste_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ArtNexus::on_pbupdate_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                             QObject::tr("Please select an item to update."),
                             QMessageBox::Ok);
        return;
    }
    ui->pbconfirm->setVisible(false);
  //  ui->pbconfirm_3->setVisible(true);
    int selectedRow = selectedIndexes.first().row();
    QString nom_event = ui->tableView->model()->index(selectedRow, 1).data().toString();
    QString descript_event = ui->tableView->model()->index(selectedRow, 2).data().toString();
    QString location = ui->tableView->model()->index(selectedRow, 3).data().toString();
    QString date_event = ui->tableView->model()->index(selectedRow, 4).data().toString();
    QString id_event = ui->tableView->model()->index(selectedRow, 0).data().toString();

    ui->lename_3->setText(nom_event);
    ui->ledesc_3->setText(descript_event);
    ui->lelocation_3->setText(location);
    ui->ledate_3->setText(date_event);
    ui->leid->setText(id_event);
    ui->stackedWidget->setCurrentIndex(2);
     ui->label_id2->setVisible(false);
      ui->leid->setVisible(false);
}
void ArtNexus::on_pbexportpdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");

      if (!filePath.isEmpty()) {
          QPrinter printer(QPrinter::PrinterResolution);
          printer.setOutputFormat(QPrinter::PdfFormat);
          printer.setOutputFileName(filePath);

          // Set the resolution for the printer, not the QPainter
          printer.setResolution(100);

          QPainter painter(&printer);

          // Remove the following line as setResolution is now applied to QPrinter
          // painter.setResolution(1200);

          ui->tableView->render(&painter);

          QMessageBox::information(this, "Export PDF", "PDF file exported successfully.");
      }
}


void ArtNexus::on_pbsearch_clicked()
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

void ArtNexus::on_pbtri_clicked()
{
 ui->tableView->setModel(e.triNom());
}

void ArtNexus::on_pbrefresh_clicked()
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
       ui->pbrefresh->setVisible(false);
}

void ArtNexus::on_pbconfirm_5_clicked()
{
    int id_event = ui->leid->text().toInt();
       QString nom_event = ui->lename_3->text();
       QString descript_event = ui->ledesc_3->toPlainText();
       QString location = ui->lelocation_3->text();
       QString date_event = ui->ledate_3->text();
     class  event e (id_event,nom_event, descript_event, location,date_event);
       bool test = e.modifier();
       if(test) {
           ui->tableView->setModel(etmp.afficher());
           ui->stackedWidget->setCurrentIndex(0);
           QMessageBox::information(nullptr,QObject::tr("OK"),
                                  QObject::tr("UPDATE SUCCES\n"),QMessageBox::Cancel);

       }
       else {
           QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                  QObject::tr(" UPDATE FAILED.\n"),QMessageBox::Cancel);
       }
}

void ArtNexus::on_pbstat_clicked()
{
    QSqlQuery query;
        query.prepare("SELECT location, COUNT(*) FROM event GROUP BY location");
        if (query.exec())
        {
            QMap<QString, QList<int>> data;

            while (query.next())
            {
                QString location = query.value(0).toString();
                int count = query.value(1).toInt();
                data[location].append(count);
            }

            Dialog *Dialog = new class Dialog(this);
            Dialog->setChartData(data);
            Dialog->exec();
        }
}
