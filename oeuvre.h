#ifndef OEUVRE_H
#define OEUVRE_H
#include<QString>
#include <QIntValidator>
#include <QDate>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class Oeuvre
{
signals:
    void cityNameChanged(const QString &cityName);

public:
    QString FILEPATH;
    QString id_artiste,id_event;
    void setREFERENCE(QString n);
    void setNOM(QString n);
    void setPRICE(int n);
    void setDESCRIPTION(QString n);
    void setDATEC(QDate n);
    void setTYPE(QString n);
    void setPOSITION(QString n);
    void setETAT(QString n);
    void setLOCATION(QString n);



    QString get_REFERENCE();
    QString get_NOM();
    int get_PRICE();
    QString get_DESCRIPTION();
    QDate get_DATEC();
    QString get_TYPE();
    QString get_POSITION();
    QString get_ETAT();
    QString get_LOCATION();


    Oeuvre();
    Oeuvre(QString ,QString ,int,QString,QDate,QString,QString,QString,QString);
    Oeuvre(QString ,QString ,int,QString,QDate,QString,QString,QString,QString,QString,QString,QString);

    int nombreDeVentes();
public slots:
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(QString );
    bool modifier( QString );
    QSqlQueryModel * rechercherOEUVRES(QString recherche);
    QSqlQueryModel * triOEUVRES(QString tri);





private:
    QString REFERENCE,NOM,DESCRIPTION,TYPE,POSITION,ETAT,LOCATION;
    QDate DATEC;
    int PRICE;


};



#endif // OEUVRE_H
