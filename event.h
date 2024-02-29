#ifndef EVENT_H
#define EVENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>
class event
{
private :
    QString nom_event, descript_event, location,date_event;
    int id_event;


public:


    event();
    event(int id_event,QString nom_event,QString descript_event,QString location,QString date_event)
    {
        this->id_event = id_event;
        this->nom_event = nom_event;
        this->descript_event = descript_event;
        this->location = location;
        this->date_event = date_event;

    }
    event(QString nom_event,QString descript_event,QString location,QString date_event)
    {
        this->nom_event = nom_event;
        this->descript_event = descript_event;
        this->location = location;
        this->date_event = date_event;

    }
    event (int id_event)
    {
        this->id_event=id_event;
    }
    void setNom_event(QString nom_event){
        this->nom_event = nom_event;
    }
    void setDescript_event(QString descript_event){
        this->descript_event = descript_event;
    }
    void setLocation(QString location){
        this->location = location;
    }
    void setDate(QString date_event){
        this->date_event = date_event;
    }

    void setId_event(int id_event){
        this->id_event = id_event;
    }
    int getId_event(){
        return this->id_event;
    }
    QString getNom_event(){
        return this->nom_event;
    }
    QString getDescript_event(){
        return this->descript_event;
    }
    QString getLocation(){
        return this->location;
    }
    QString getDate_event(){
        return this->date_event;
    }

    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier ();
    bool supprimer(int);


};
#endif // EVENT_H

