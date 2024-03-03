#include "event.h"
#include <QtDebug>
event::event()
{

}

bool event::ajouter()
{
    QSqlQuery query;
QString res = QString::number(id_event);
       query.prepare("insert into event (nom_event, descript_event, location, date_event) "
                     "values (:nom_event, :descript_event, :location, :date_event)");
       // Bind the event details to the query parameters
       query.bindValue(":nom_event", nom_event);
       query.bindValue(":descript_event", descript_event);
       query.bindValue(":location", location);
       query.bindValue(":date_event", date_event);
          return query.exec() ;
}


QSqlQueryModel *event::afficher()
{
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select id_event,nom_event, descript_event, location, date_event from event");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_event"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom_event"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("descript_event"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("location"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_event"));
return model;

}


bool event::supprimerTous()
{
    QSqlQuery query;
    query.prepare("DELETE FROM event");
    return query.exec();
}
bool event::supprimer(int id_event)
{
    QSqlQuery query;
    query.prepare("DELETE FROM event WHERE id_event = :id_event");
    query.bindValue(":id_event", id_event);
    return query.exec();
}

bool event::modifier(){
     QSqlQuery query;
     QString res = QString::number(id_event);
     query.prepare ("UPDATE event SET nom_event=:nom_event,descript_event=:descript_event,location=:location,date_event=:date_event WHERE id_event=:id_event");
     query.bindValue(":id_event",res);
     query.bindValue(":nom_event",nom_event);
     query.bindValue(":descript_event",descript_event);
     query.bindValue(":location",location);
     query.bindValue(":date_event",date_event);
     return query.exec();


};

QSqlQueryModel * event::triNom()
{
    QSqlQueryModel * model = new QSqlQueryModel();
       model->setQuery("SELECT * FROM event ORDER BY nom_event");
       return model;

}
int event::stat(QString location)
{
    QSqlQuery query;
    query.prepare("select count(*) from event where location=:location ");
    query.bindValue(":location",location);
    query.exec();
    query.next();

    return query.value(0).toInt();

}
