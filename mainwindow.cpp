#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "oeuvre.h"
#include <QDebug>
#include<QMainWindow>
#include<QMessageBox>
#include<QIntValidator>
#include <QDir>
#include<QPainter>
#include<QPrinter>
#include<QPdfWriter>
#include <QStandardPaths>
#include<QChart>
#include<QChartView>
#include<QPieSlice>
#include<QPieSeries>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QHBoxLayout>
#include <QtCharts/QLegend>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
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

void MainWindow::on_comboBox_4_currentIndexChanged(const QString &arg1)
{
    if(arg1 != "")
    {
       ui->tableView->setModel(etmp.triOEUVRES(arg1));
    }
    else
    {
        ui->tableView->setModel(etmp.rechercherOEUVRES(arg1));
    }

}

void MainWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
    if(arg1!="")
    {
    ui->tableView->setModel(etmp.rechercherOEUVRES(arg1));}
    else if(arg1 == "REFERENCE")
    { ui->tableView->setModel(etmp.rechercherOEUVRES(arg1));}
    else if (arg1 == "NOM"){
    ui->tableView->setModel(etmp.rechercherOEUVRES(arg1));}
    else if (arg1 == "PRICE")
    {ui->tableView->setModel(etmp.rechercherOEUVRES(arg1));}
    else if (arg1 == "DESCRIPTION")
    {ui->tableView->setModel(etmp.rechercherOEUVRES(arg1));}
    else
    {ui->tableView->setModel(etmp.rechercherOEUVRES(arg1));}


}

void MainWindow::on_pushButton_9_clicked()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    filePath = QDir(filePath).filePath("C:/Users/medal/OneDrive/Bureau/projet qt/add_oeuvre/listeOeuvres.pdf"); // Chemin du fichier
    QPdfWriter pdf(filePath); // Création du fichier PDF

    QPainter painter(&pdf); // Création d'un peintre pour le PDF
    int i = 4100;

    QColor dateColor(0x4a5bcf); // Couleur pour la date
    painter.setPen(dateColor);
    painter.setFont(QFont("Montserrat SemiBold", 11));
    QDate cd = QDate::currentDate();
    painter.drawText(8400, 250, cd.toString("Tunis")); // Entête de la date
    painter.drawText(8100, 500, cd.toString("dd/MM/yyyy"));

    QColor titleColor(0x341763); // Couleur pour le titre
    painter.setPen(titleColor);
    painter.setFont(QFont("Montserrat SemiBold", 25));
    painter.drawText(3000, 2700, "Liste des OEUVRES"); // Titre

    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 12));

    // Dessiner le cadre du tableau
    painter.drawRect(100, 3300, 9400, 500);

    // Dessiner les en-têtes des colonnes
    painter.drawText(100, 3550, "REFERENCE");
    painter.drawText(1300, 3550, "NOM");
    painter.drawText(2000, 3550,"PRICE" );
    painter.drawText(3000, 3550,"DESCRIPTION" );
    painter.drawText(4400, 3550, "DATEC");
    painter.drawText(6000, 3550, "TYPE");
    painter.drawText(7200, 3550, "POSITION");
    painter.drawText(8500, 3550, "ETAT");

    painter.setFont(QFont("Time New Roman", 10));

    // Exécuter la requête SQL pour sélectionner tous les enregistrements de la table "OEUVRES"
    QSqlQuery query;
    query.prepare("SELECT * FROM OEUVRES");
    query.exec();

    // Afficher les données dans le PDF
    int y = 3800; // Position verticale initiale
    while (query.next())
    {
        painter.drawLine(100, y, 9490, y); // Dessiner une ligne horizontale
        y += 300; // Augmenter la position verticale pour la prochaine ligne

        painter.drawText(500, i, query.value(0).toString()); // REFERENCE
        painter.drawText(1000, i, query.value(1).toString()); // NOM
        painter.drawText(2000, i, query.value(2).toString()); // DESCRIPTION
        painter.drawText(3000, i, query.value(3).toString()); // PRICE
        painter.drawText(4000, i, query.value(4).toString()); // DATEC
        painter.drawText(6000, i, query.value(5).toString()); // TYPE
        painter.drawText(7500, i, query.value(6).toString()); // POSITION
        painter.drawText(8500, i, query.value(7).toString()); // ETAT

        i = i + 300; // Augmenter la position verticale pour la prochaine ligne
    }

    // Afficher un message de confirmation
    QMessageBox::information(nullptr, QObject::tr("PDF créé"),
                             QObject::tr("Fichier créé avec succès.\n"), QMessageBox::Ok);

}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    QSqlQueryModel * model= new QSqlQueryModel();
                     model->setQuery("select * from OEUVRES where PRICE < 500 ");
                     float PRICE=model->rowCount();
                     model->setQuery("select * from OEUVRES where PRICE  between 500 and 5000 ");
                     float PRICE1=model->rowCount();
                     model->setQuery("select * from OEUVRES where PRICE >5000 ");
                     float PRICE2=model->rowCount();
                     float total=PRICE+PRICE1+PRICE2;
                     QString a=QString("moins de 500 \t"+QString::number((PRICE*100)/total,'f',2)+"%" );
                     QString b=QString("entre 500 et 5000 \t"+QString::number((PRICE1*100)/total,'f',2)+"%" );
                     QString c=QString("+5000 \t"+QString::number((PRICE2*100)/total,'f',2)+"%" );
                     QPieSeries *series = new QPieSeries();
                     series->append(a,PRICE);
                     series->append(b,PRICE1);
                     series->append(c,PRICE2);
             if (PRICE!=0)
             {

                 QPieSlice *slice = series->slices().at(0);
                   slice->setBrush(QColor(164, 133, 105));
                   slice->setLabelVisible();
                   slice->setPen(QPen());;

             }
             if ( PRICE1!=0)
             {
                 QPieSlice *slice1 = series->slices().at(1);
                 slice1->setBrush(QColor(232, 215, 198));
                 slice1->setLabelVisible();
             }
             if(PRICE2!=0)
             {
                 QPieSlice *slice2 = series->slices().at(2);
                  slice2->setBrush(QColor("#C29E7E")); // Utilisation de la valeur hexadécimale
                  slice2->setLabelVisible();
             }
                     QChart *chart = new QChart();
                         chart->addSeries(series);
                         chart->setTitle("");
                        chart->setBackgroundVisible(false);
                     chart->setVisible(true);
                     chart->legend()->setAlignment(Qt::AlignBottom);
                     QChartView *chartView = new QChartView(chart);
                     chartView->setRenderHint(QPainter::Antialiasing);
                     QPalette pal = qApp->palette();
                     chartView->setMaximumWidth(741);
                     chartView->setMaximumHeight(451);
                     chartView->setMinimumWidth(741);
                     chartView->setMinimumHeight(451);
                     chartView->setParent(ui->label_stat_oeuvre);
                     chartView->show();

}

void MainWindow::on_returnOvrBtn_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}
