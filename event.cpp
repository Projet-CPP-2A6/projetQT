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
model->setHeaderData(3,Qt::Horizontal,QObject::tr("descript_event"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("location"));
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
bool event::modifier(int id_event)
{
    QSqlQuery query;
        query.prepare("SELECT * FROM event WHERE id_event = :id_event");
        query.bindValue(":id_event", id_event);

        if (query.exec() && query.next()) {
            // Record found, update the fields
            query.prepare("UPDATE event SET nom_event=:nom, descript_event=:descript, "
                          "location=:location, date_event=:date WHERE id_event=:id");
            query.bindValue(":nom", nom_event);
            query.bindValue(":descript", descript_event);
            query.bindValue(":location", location);
            query.bindValue(":date", date_event);
            query.bindValue(":id", id_event);

            return query.exec();
        }

        return false;
}
