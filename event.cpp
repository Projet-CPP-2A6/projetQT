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

