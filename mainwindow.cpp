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






