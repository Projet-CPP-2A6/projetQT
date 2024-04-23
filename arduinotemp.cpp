#include "arduinotemp.h"
#include "ui_arduinotemp.h"

arduinotemp::arduinotemp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::arduinotemp)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

void arduinotemp::update_label()
{
    data=A.read_from_arduino();

    if(data=="0"){

        ui->label_etat->setText("Temperature normale");
    }else if (data=="1"){
  ui->label_etat->setText("Temperature elevee"); }  // si les données reçues de arduino via la liaison série sont égales à 0

else if (data=="2"){
  ui->label_etat->setText("Temperature basse");   // si les données reçues de arduino via la liaison série sont égales à 0
}}

arduinotemp::~arduinotemp()
{
    delete ui;
}

void arduinotemp::on_onlm35_clicked()
{
    A.write_to_arduino("1");
}

void arduinotemp::on_offlm35_clicked()
{
    A.write_to_arduino("0");
}
