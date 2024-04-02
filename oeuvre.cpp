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
<<<<<<< HEAD
    LOCATION="";
}
Oeuvre::Oeuvre(QString REFERENCE,QString NOM,int PRICE,QString DESCRIPTION,QDate DATEC,QString TYPE,QString POSITION,QString ETAT,QString LOCATION)
=======


}
Oeuvre::Oeuvre(QString REFERENCE,QString NOM,int PRICE,QString DESCRIPTION,QDate DATEC,QString TYPE,QString POSITION,QString ETAT)
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
{
    this->REFERENCE=REFERENCE;
    this->NOM=NOM;
    this->PRICE=PRICE;
    this->DESCRIPTION=DESCRIPTION;
    this->DATEC=DATEC;
     this->TYPE=TYPE;
     this->POSITION=POSITION;
     this->ETAT=ETAT;
<<<<<<< HEAD
    this->LOCATION=LOCATION;
=======
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1

}
void Oeuvre::setREFERENCE(QString n){REFERENCE=n;}
void Oeuvre::setNOM(QString n){NOM=n;}
void Oeuvre::setPRICE(int n){PRICE=n;}
void Oeuvre::setDESCRIPTION(QString n){DESCRIPTION=n;}
void Oeuvre::setDATEC(QDate date){DATEC=date;}
void Oeuvre::setTYPE(QString n){TYPE=n;}
void Oeuvre::setPOSITION(QString n){POSITION=n;}
void Oeuvre::setETAT(QString n){ETAT=n;}
<<<<<<< HEAD
void Oeuvre::setLOCATION(QString n){LOCATION=n;}

=======
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1

QString Oeuvre::get_REFERENCE(){return REFERENCE;}
QString Oeuvre::get_NOM(){return NOM;}
int Oeuvre::get_PRICE(){return PRICE;}
QString Oeuvre::get_DESCRIPTION(){return DESCRIPTION;}
QDate Oeuvre::get_DATEC(){return DATEC;}
QString Oeuvre::get_TYPE(){return TYPE;}
QString Oeuvre::get_POSITION(){return POSITION;}
QString Oeuvre::get_ETAT(){return ETAT;}
<<<<<<< HEAD
QString Oeuvre::get_LOCATION(){return LOCATION;}
=======
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1


bool Oeuvre::ajouter()
  {
      QSqlQuery query;
      QString res=QString::number(PRICE);
<<<<<<< HEAD
      query.prepare("insert into OEUVRES (REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT,LOCATION )""values(:ref,:name,:price,:description,:datec,:TYPE,:POSITION,:ETAT,:LOCATION)");
=======
      query.prepare("insert into OEUVRES (REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT )""values(:ref,:name,:price,:description,:datec,:TYPE,:POSITION,:ETAT)");
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
      query.bindValue(":ref", REFERENCE);
      query.bindValue(":name", NOM);
      query.bindValue(":price", res);
      query.bindValue(":description", DESCRIPTION);
      query.bindValue(":datec", DATEC);
      query.bindValue(":TYPE", TYPE);
      query.bindValue(":POSITION", POSITION);
      query.bindValue(":ETAT", ETAT);
<<<<<<< HEAD
      query.bindValue(":LOCATION", LOCATION);

=======
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1

  return query.exec();
  }
  QSqlQueryModel *Oeuvre::afficher()
  {
  QSqlQueryModel *model=new QSqlQueryModel();
<<<<<<< HEAD
  model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT,LOCATION from OEUVRES");
=======
  model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT from OEUVRES");
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("REFERENCE"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESCRIPTION"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRICE"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATEC"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
  model->setHeaderData(6,Qt::Horizontal,QObject::tr("POSITION"));
  model->setHeaderData(7,Qt::Horizontal,QObject::tr("ETAT"));
<<<<<<< HEAD
  model->setHeaderData(8,Qt::Horizontal,QObject::tr("LOCATION"));
=======

>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1

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
<<<<<<< HEAD
            query.prepare("UPDATE OEUVRES SET REFERENCE=:ref, NOM=:nom, PRICE=:price , DESCRIPTION=:description ,DATEC=:datec,TYPE=:TYPE,POSITION=:POSITION,ETAT=:ETAT,LOCATION=:LOCATION where reference='"+REFERENCE+"' ");
=======
            query.prepare("UPDATE OEUVRES SET REFERENCE=:ref, NOM=:nom, PRICE=:price , DESCRIPTION=:description ,DATEC=:datec,TYPE=:TYPE,POSITION=:POSITION,ETAT=:ETAT where reference='"+REFERENCE+"' ");
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
            query.bindValue(":ref", REFERENCE);
            query.bindValue(":nom", NOM);
            query.bindValue(":price", res);
            query.bindValue(":description",DESCRIPTION);
            query.bindValue(":datec",DATEC);
            query.bindValue(":TYPE", TYPE);
            query.bindValue(":POSITION", POSITION);
            query.bindValue(":ETAT", ETAT);
<<<<<<< HEAD
            query.bindValue(":LOCATION", LOCATION);

=======
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1

              return query.exec();

  }
  QSqlQueryModel *Oeuvre::rechercherOEUVRES(QString recherche)
  {
      QSqlQueryModel * model = new QSqlQueryModel();
<<<<<<< HEAD
      model->setQuery("SELECT * from OEUVRES WHERE (UPPER(REFERENCE) LIKE UPPER('%"+recherche+"%') OR UPPER(NOM) LIKE UPPER('%"+recherche+"%') OR UPPER(PRICE) LIKE UPPER('%"+recherche+"%') OR UPPER(DESCRIPTION) LIKE UPPER('%"+recherche+"%') OR UPPER(DATEC) LIKE UPPER('%"+recherche+"%') OR UPPER(TYPE) LIKE UPPER('%"+recherche+"%') OR UPPER(POSITION) LIKE UPPER('%"+recherche+"%') OR UPPER(ETAT) LIKE UPPER('%"+recherche+"%')OR UPPER(LOCATION) LIKE UPPER('%"+recherche+"%'))");
=======
      model->setQuery("SELECT * from OEUVRES WHERE (UPPER(REFERENCE) LIKE UPPER('%"+recherche+"%') OR UPPER(NOM) LIKE UPPER('%"+recherche+"%') OR PRICE LIKE UPPER('%"+recherche+"%') OR DESCRIPTION LIKE UPPER('%"+recherche+"%') OR DATEC LIKE UPPER('%"+recherche+"%') OR TYPE LIKE UPPER('%"+recherche+"%') OR POSITION LIKE UPPER('%"+recherche+"%') OR ETAT LIKE UPPER('%"+recherche+"%'))");
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
      model->setHeaderData(0,Qt::Horizontal,QObject::tr("REFERENCE"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESCRIPTION"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRICE"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATEC"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("POSITION"));
      model->setHeaderData(7,Qt::Horizontal,QObject::tr("ETAT"));
<<<<<<< HEAD
      model->setHeaderData(8,Qt::Horizontal,QObject::tr("LOCATION"));

=======
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
      return model;

  }
QSqlQueryModel * Oeuvre::triOEUVRES(QString tri)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    if(tri == "Tri par defaut"){
<<<<<<< HEAD
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT,LOCATION from OEUVRES");}
    else if(tri == "Tri Par Price"){
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT,LOCATION from OEUVRES ORDER BY PRICE asc");
        }else if (tri == "Tri Par Reference") {
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT,LOCATION from OEUVRES ORDER BY REFERENCE asc ");
    } else if (tri == "Tri Par Nom") {
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT,LOCATION from OEUVRES ORDER BY NOM asc");
=======
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT from OEUVRES");}
    else if(tri == "Tri Par Price"){
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT from OEUVRES ORDER BY PRICE asc");
        }else if (tri == "Tri Par Reference") {
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT from OEUVRES ORDER BY REFERENCE asc ");
    } else if (tri == "Tri Par Nom") {
        model->setQuery("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT from OEUVRES ORDER BY NOM asc");
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
    }
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRICE"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("REFERENCE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    return model;

}
<<<<<<< HEAD

=======
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
