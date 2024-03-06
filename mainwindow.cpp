#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "oeuvre.h"
#include <QDebug>
#include<QMainWindow>
#include<QMessageBox>
#include<QIntValidator>
#include <QDir>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    ui->lineEdit_price->setValidator(new QIntValidator(0,9999,this));//cs
         QRegularExpressionValidator *stringValidator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z0-9]+"), this);
         ui->lineEdit_name->setValidator(stringValidator);
         ui->tableView->setModel(etmp.afficher());
         ui->stackedWidget->setCurrentIndex(0);
    }
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}
void MainWindow::on_btn_confirmer_clicked()

{


    QString ref=ui->lineEdit_reference->text();
   QString nom=ui->lineEdit_name->text();
   int price=ui->lineEdit_price->text().toInt();
   QString desc=ui->lineEdit_desc->text();
   QDate DATEC=ui->dateEdit->date();
   QString TYPE=ui->comboBox->currentText();
   QString POSITION=ui->comboBox_2->currentText();
   QString ETAT=ui->comboBox_3->currentText();
   QSqlQuery qry ;
   qry.prepare("select * from oeuvres where REFERENCE='"+ref+"' " );
   qry.exec();
   if(qry.next()){ QMessageBox::critical(nullptr, QObject::tr("add"),
                                            QObject::tr(" reference already exist .\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);}
   else{
       if(ref==0 || nom=="" || price ==0 ||desc =="" || POSITION == "" || ETAT=="" || TYPE == ""){QMessageBox::warning(nullptr, QObject::tr("add"),
                                                                            QObject::tr(" tous les champs sont obligatoires .\n"
                                                                                      "Click Cancel to exit."), QMessageBox::Cancel);}
                                   else{
   Oeuvre o(ref,nom,price,desc,DATEC,TYPE,POSITION,ETAT);
   bool test=o.ajouter();
   if (test)
   {

       ui->tableView->setModel(etmp.afficher());

        ui->stackedWidget->setCurrentIndex(0);
       QMessageBox::information(nullptr, QObject::tr("add"),
                  QObject::tr(" successful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

       ui->lineEdit_reference->clear();
       ui->lineEdit_name->clear();
       ui->lineEdit_price->clear();
       ui->lineEdit_desc->clear();
       ui->dateEdit->clear();
       ui->comboBox->currentText();
       ui->comboBox_2->currentText();
       ui->comboBox_3->currentText();

   }
   else{

       QMessageBox::critical(nullptr, QObject::tr("add"),
                   QObject::tr(" failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
   }
}}
}
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView->model()->data(in).toString();
        QSqlQuery qry;
        qry.prepare("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT from OEUVRES where REFERENCE='"+val+"' " );
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_reference_update->setText(qry.value(0).toString());
                ui->lineEdit_name_update->setText(qry.value(1).toString());
                ui->lineEdit_price_update->setText(qry.value(2).toString());
                ui->lineEdit_desc_update->setText(qry.value(3).toString());
                ui->dateEdit_update->setDate(qry.value(4).toDate());
                ui->comboBox_update->setCurrentText(qry.value(6).toString());
                ui->comboBox_update_2->setCurrentText(qry.value(5).toString());
                ui->comboBox_update_3->setCurrentText(qry.value(7).toString());

            }
}
}
void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget_integ->setCurrentIndex(1);

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget_integ->setCurrentIndex(2);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget_integ->setCurrentIndex(3);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget_integ->setCurrentIndex(4);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget_integ->setCurrentIndex(0);
}

void MainWindow::on_btn_modifier_clicked()

{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                             QObject::tr("Please select an item to update."),
                             QMessageBox::Ok);
        return;
    }
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_btn_supprimer_clicked()
{
    {
        int i;
            QModelIndex index=ui->tableView->currentIndex();
        i=index.row();
        QModelIndex in=index.sibling(i,0);

        QString val=ui->tableView->model()->data(in).toString();

            bool test=etmp.supprimer(val);
            if (test)
            {

                ui->tableView->setModel(etmp.afficher());
                ui->lineEdit_reference->clear();
                ui->lineEdit_name->clear();
                ui->lineEdit_price->clear();
                ui->lineEdit_desc->clear();
                ui->dateEdit->clear();
                ui->comboBox->currentText();
                ui->comboBox_2->currentText();
                ui->comboBox_3->currentText();


        }
    }
}

void MainWindow::on_btn_confirmer_2_clicked()
    {
        ui->stackedWidget->setCurrentIndex(0);
    }





void MainWindow::on_returnOvrBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_updateOvrBtn_clicked()
{

    QString ref = ui->lineEdit_reference_update->text();
    QString nom = ui->lineEdit_name_update->text();
    int price = ui->lineEdit_price_update->text().toInt();
    QString desc = ui->lineEdit_desc_update->text();
    QDate DATEC=ui->dateEdit_update->date();
    QString TYPE=ui->comboBox_update->currentText();
    QString POSITION=ui->comboBox_update_2->currentText();
    QString ETAT=ui->comboBox_update_3->currentText();

    if( nom=="" || price ==0 ||desc =="" || POSITION == "" || ETAT=="" || TYPE == ""){QMessageBox::warning(nullptr, QObject::tr("add"),
                                                                         QObject::tr(" tous les champs sont obligatoires .\n"
                                                                                   "Click Cancel to exit."), QMessageBox::Cancel);}
                                else{
    Oeuvre o(ref, nom, price, desc,DATEC,TYPE,POSITION,ETAT);
    bool test = o.modifier(ref);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Update"),
                                 QObject::tr("Update successful.\nClick OK to return."),
                                 QMessageBox::Ok);

        ui->lineEdit_reference_update->clear();
        ui->lineEdit_name_update->clear();
        ui->lineEdit_price_update->clear();
        ui->lineEdit_desc_update->clear();
        ui->dateEdit_update->clear();
        ui->comboBox_update->currentText();
        ui->comboBox_update_2->currentText();
        ui->comboBox_update_3->currentText();
        ui->stackedWidget->setCurrentIndex(0);
        ui->tableView->setModel(etmp.afficher());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Update"),
                              QObject::tr("Update failed.\nClick OK to return."),
                              QMessageBox::Ok);
    }}
}
