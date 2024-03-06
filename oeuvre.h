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
public:
    void setREFERENCE(QString n);
    void setNOM(QString n);
    void setPRICE(int n);
    void setDESCRIPTION(QString n);
    void setDATEC(QDate n);
    void setTYPE(QString n);
    void setPOSITION(QString n);
    void setETAT(QString n);

    QString get_REFERENCE();
    QString get_NOM();
    int get_PRICE();
    QString get_DESCRIPTION();
    QDate get_DATEC();
    QString get_TYPE();
    QString get_POSITION();
    QString get_ETAT();

    Oeuvre();
    Oeuvre(QString ,QString ,int,QString,QDate,QString,QString,QString);
public slots:
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(QString );
    bool modifier( QString );
private:
    QString REFERENCE,NOM,DESCRIPTION,TYPE,POSITION,ETAT;
    QDate DATEC;
    int PRICE;
};



#endif // OEUVRE_H
