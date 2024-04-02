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
<<<<<<< HEAD
signals:
    void cityNameChanged(const QString &cityName);



public:




=======
public:
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
    void setREFERENCE(QString n);
    void setNOM(QString n);
    void setPRICE(int n);
    void setDESCRIPTION(QString n);
    void setDATEC(QDate n);
    void setTYPE(QString n);
    void setPOSITION(QString n);
    void setETAT(QString n);
<<<<<<< HEAD
    void setLOCATION(QString n);

=======
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1

    QString get_REFERENCE();
    QString get_NOM();
    int get_PRICE();
    QString get_DESCRIPTION();
    QDate get_DATEC();
    QString get_TYPE();
    QString get_POSITION();
    QString get_ETAT();
<<<<<<< HEAD
    QString get_LOCATION();


    Oeuvre();
    Oeuvre(QString ,QString ,int,QString,QDate,QString,QString,QString,QString);
=======

    Oeuvre();
    Oeuvre(QString ,QString ,int,QString,QDate,QString,QString,QString);
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
    int nombreDeVentes();
public slots:
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(QString );
    bool modifier( QString );
    QSqlQueryModel * rechercherOEUVRES(QString recherche);
    QSqlQueryModel * triOEUVRES(QString tri);
<<<<<<< HEAD





private:
    QString REFERENCE,NOM,DESCRIPTION,TYPE,POSITION,ETAT,LOCATION;
    QDate DATEC;
    int PRICE;


=======
private:
    QString REFERENCE,NOM,DESCRIPTION,TYPE,POSITION,ETAT;
    QDate DATEC;
    int PRICE;
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
};



#endif // OEUVRE_H
