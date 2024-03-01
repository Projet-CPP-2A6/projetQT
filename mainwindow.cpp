#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include "event.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
   class event e;


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
}

void MainWindow::on_pbliste_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pbupdate_clicked()
{

}
