#include "arduinotemp.h"
#include "ui_arduinotemp.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer> // Include QTimer for delays
#include <QThread>
#include "notification.h"
#include "mainwindow.h"
arduinotemp::arduinotemp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::arduinotemp)
{
    QSqlQuery q3 ;

    ui->setupUi(this);
    int ret = A.connect_arduino(); // Connect to Arduino
   if (ret) {
        qDebug() << "arduino mrgl" ;
   }

   timer = new QTimer(this);
   connect(timer, &QTimer::timeout, this, &arduinotemp::update_label2);

   update_label();
}

void arduinotemp::update_label()
{

    QSqlQuery query;
    QByteArray msg = "";
    QByteArray reference ;
    int risk = 0;

    query.prepare("SELECT REFERENCE FROM OEUVRES WHERE ETAT LIKE 'Risque' ");

    if (query.exec()) {
        while (query.next()) {
            reference = query.value(0).toByteArray();
            risk++;
            msg += reference + " ";
        }
        ui->label_4->setText("oeuvre(s): "+msg+"en risque") ;
    }

    if (risk ) {
        A.write_to_arduino(msg);
    }
}


void arduinotemp::update_label2()
{
    QByteArray data = A.read_from_arduino();
    QString reply(data)  ;
    QSqlQuery q1,q2,q3;
    QString etat,msg ;

    if(reply != ""){
        ui->label_2->setText(reply);

    if ( reply.toInt() >= 30 ) {
        etat = "Risque";

        q1.prepare("UPDATE OEUVRES SET ETAT = :etat WHERE REFERENCE = 1");
        q2.prepare("SELECT ETAT FROM OEUVRES WHERE REFERENCE = 1 ") ;



        q1.bindValue(":etat", etat);
        if(q2.exec() && q2.next()) {
               if (q2.value(0) == "Risque" ){
                        A.write_to_arduino("0") ;
                        notif.notifAlert();
               }
               else {
                        q1.exec() ;
                        A.write_to_arduino("1") ;
                    }
                }
            }
        else {
            etat = "Non risque";
            q1.prepare("UPDATE OEUVRES SET ETAT = :etat WHERE REFERENCE = 1");
            q2.prepare("SELECT ETAT FROM OEUVRES WHERE REFERENCE = 1 ") ;

            q1.bindValue(":etat", etat);
            if(q2.exec() && q2.next()) {
                   if (q2.value(0) == "Non risque" ){
                         A.write_to_arduino("2") ;
                   }
                   else {
                         q1.exec() ;
                         A.write_to_arduino("3") ;
                        }
                }
        }

    }
}


arduinotemp::~arduinotemp()
{
    delete ui;
}



void arduinotemp::on_pushButton_2_clicked()
{
    timer->start(1000);
}

void arduinotemp::on_pushButton_clicked()
{
    timer->stop() ;
    ui->label_2->clear() ;
}

void arduinotemp::on_pushButton_3_clicked()
{
    QSqlQuery q3 ;
    QString msg ;

    q3.prepare("SELECT REFERENCE FROM OEUVRES WHERE ETAT LIKE 'Risque' ") ;
    if(q3.exec()) {
        while (q3.next()) {
            msg += q3.value(0).toString() + " "  ;
        }
    }
    ui->label_4->setText("oeuvre(s): "+msg+"en risque") ;
}



