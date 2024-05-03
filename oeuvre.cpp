#include "oeuvre.h"
#include<QString>
#include<QDebug>
Oeuvre::Oeuvre()
{
    REFERENCE="";
    NOM="";
    PRICE=0;
    DESCRIPTION="";
    DATEC=QDate();
    TYPE="";
    POSITION="";
    ETAT="";


}
Oeuvre::Oeuvre(QString REFERENCE,QString NOM,int PRICE,QString DESCRIPTION,QDate DATEC,QString TYPE,QString POSITION,QString ETAT)
{
    this->REFERENCE=REFERENCE;
    this->NOM=NOM;
    this->PRICE=PRICE;
    this->DESCRIPTION=DESCRIPTION;
    this->DATEC=DATEC;
     this->TYPE=TYPE;
     this->POSITION=POSITION;
     this->ETAT=ETAT;


}
Oeuvre::Oeuvre(QString REFERENCE,QString NOM,int PRICE,QString DESCRIPTION,QDate DATEC,QString TYPE,QString POSITION,QString ETAT,QString FILEPATH,QString id_artiste,QString id_event)
{
    this->REFERENCE=REFERENCE;
    this->NOM=NOM;
    this->PRICE=PRICE;
    this->DESCRIPTION=DESCRIPTION;
    this->DATEC=DATEC;
     this->TYPE=TYPE;
     this->POSITION=POSITION;
     this->ETAT=ETAT;

    this->FILEPATH=FILEPATH;
    this->id_artiste=id_artiste;
    this->id_event=id_event;


}
void Oeuvre::setREFERENCE(QString n){REFERENCE=n;}
void Oeuvre::setNOM(QString n){NOM=n;}
void Oeuvre::setPRICE(int n){PRICE=n;}
void Oeuvre::setDESCRIPTION(QString n){DESCRIPTION=n;}
void Oeuvre::setDATEC(QDate date){DATEC=date;}
void Oeuvre::setTYPE(QString n){TYPE=n;}
void Oeuvre::setPOSITION(QString n){POSITION=n;}
void Oeuvre::setETAT(QString n){ETAT=n;}


QString Oeuvre::get_REFERENCE(){return REFERENCE;}
QString Oeuvre::get_NOM(){return NOM;}
int Oeuvre::get_PRICE(){return PRICE;}
QString Oeuvre::get_DESCRIPTION(){return DESCRIPTION;}
QDate Oeuvre::get_DATEC(){return DATEC;}
QString Oeuvre::get_TYPE(){return TYPE;}
QString Oeuvre::get_POSITION(){return POSITION;}
QString Oeuvre::get_ETAT(){return ETAT;}



bool Oeuvre::ajouter()
  {
      QSqlQuery query;
      QString res=QString::number(PRICE);
      query.prepare("insert into OEUVRES (REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT,FILEPATH,id_artiste,id_event )""values(:ref,:name,:price,:description,:datec,:TYPE,:POSITION,:ETAT,:FILEPATH,:id_artiste,:id_event)");
      query.bindValue(":ref", REFERENCE);
      query.bindValue(":name", NOM);
      query.bindValue(":price", res);
      query.bindValue(":description", DESCRIPTION);
      query.bindValue(":datec", DATEC);
      query.bindValue(":TYPE", TYPE);
      query.bindValue(":POSITION", POSITION);
      query.bindValue(":ETAT", ETAT);

      query.bindValue(":FILEPATH", FILEPATH);
      query.bindValue(":id_artiste", id_artiste);
      query.bindValue(":id_event", id_event);

  return query.exec();
  }
  QSqlQueryModel *Oeuvre::afficher()
  {
  QSqlQueryModel *model=new QSqlQueryModel();
  model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT,FILEPATH,id_artiste,id_event from OEUVRES");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("REFERENCE"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESCRIPTION"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRICE"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATEC"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
  model->setHeaderData(6,Qt::Horizontal,QObject::tr("POSITION"));
  model->setHeaderData(7,Qt::Horizontal,QObject::tr("ETAT"));

  model->setHeaderData(8,Qt::Horizontal,QObject::tr("FILEPATH"));
  model->setHeaderData(9,Qt::Horizontal,QObject::tr("id_artiste"));
  model->setHeaderData(10,Qt::Horizontal,QObject::tr("id_event"));



  return model;
  }

  bool Oeuvre::supprimer(QString REFERENCE)
  {
  QSqlQuery query;

  query.prepare("Delete from OEUVRES where REFERENCE=:ref");
  query.bindValue(":ref",REFERENCE);
  return query.exec();
  }
  bool Oeuvre::modifier(QString REFERENCE){

      QSqlQuery query;
          QString res=QString::number(PRICE);
            query.prepare("UPDATE OEUVRES SET REFERENCE=:ref, NOM=:nom, PRICE=:price , DESCRIPTION=:description ,DATEC=:datec,TYPE=:TYPE,POSITION=:POSITION,ETAT=:ETAT,id_artiste=:id_artiste,id_event=:id_event where reference='"+REFERENCE+"' ");
            query.bindValue(":ref", REFERENCE);
            query.bindValue(":nom", NOM);
            query.bindValue(":price", res);
            query.bindValue(":description",DESCRIPTION);
            query.bindValue(":datec",DATEC);
            query.bindValue(":TYPE", TYPE);
            query.bindValue(":POSITION", POSITION);
            query.bindValue(":ETAT", ETAT);
            query.bindValue(":id_artiste", id_artiste);
            query.bindValue(":id_event", id_event);

              return query.exec();

  }
  QSqlQueryModel *Oeuvre::rechercherOEUVRES(QString recherche)
  {
      QSqlQueryModel * model = new QSqlQueryModel();
      model->setQuery("SELECT * from OEUVRES WHERE (UPPER(REFERENCE) LIKE UPPER('%"+recherche+"%') OR UPPER(NOM) LIKE UPPER('%"+recherche+"%') OR UPPER(PRICE) LIKE UPPER('%"+recherche+"%') OR UPPER(DESCRIPTION) LIKE UPPER('%"+recherche+"%')  )");
      model->setHeaderData(0,Qt::Horizontal,QObject::tr("REFERENCE"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESCRIPTION"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRICE"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATEC"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("POSITION"));
      model->setHeaderData(7,Qt::Horizontal,QObject::tr("ETAT"));
      return model;

  }
QSqlQueryModel * Oeuvre::triOEUVRES(QString tri)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    if(tri == "Tri par defaut"){
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT from OEUVRES");}
    else if(tri == "Tri Par Price"){
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT from OEUVRES ORDER BY PRICE asc");
        }else if (tri == "Tri Par Reference") {
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT from OEUVRES ORDER BY REFERENCE asc ");
    } else if (tri == "Tri Par Nom") {
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT from OEUVRES ORDER BY NOM asc");
    }
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRICE"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("REFERENCE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    return model;

}
