#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
class Employe
{
    QDate debut_conge, fin_conge, heure_ent;
    QString nom_e, prenom_e, role_e, email, mdp, idcard;
    int id_e, tel_e, salaire_e;

public:
    //constructeurs
    Employe(){}
    Employe(int id_e, QString nom_e, QString prenom_e, int tel_e, int salaire_e, QString role_e, QDate debut_conge, QDate fin_conge, QString email, QString mdp, QString idcard);
    //getters
    int getID(){ return id_e; }
    QString getNom(){ return nom_e; }
    QString getPrenom(){ return prenom_e; }
    int getTel(){ return tel_e; }
    int getSalaire(){ return salaire_e; }
    QString getRole(){ return role_e; }
    QDate getdebut_conge(){ return debut_conge; }
    QDate getfin_conge(){ return fin_conge; }
    QString getEmail(){ return email; }
    QString getMdp(){ return mdp; }
    QDate getheure_ent(){ return heure_ent; }
    QString getidcard(){return idcard; }

    //setters
    void setID(int id){ this->id_e = id; }
    void setNom(QString n){ nom_e=n; }
    void setPrenom(QString p){ prenom_e=p; }
    void setTel(int tel){ this->tel_e=tel; }
    void setSalaire(int sal){ this->salaire_e=sal; }
    void setRole(QString role){ role_e=role; }
    void setdebut_conge(QDate dc){ debut_conge = dc; }
    void setfin_conge(QDate fc){ fin_conge = fc; }
    void setEmail(QString mail){ email=mail; }
    void setMdp(QString pass){ mdp=pass; }
    void setheure_ent(QDate he){ heure_ent = he; }
    void setidcard(QString card){ idcard=card; }


    //functions
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier( int );
    QSqlQueryModel * tri();
    bool seConnecter();
    QSqlQueryModel * afficher_calendar(QDate x);


};


#endif // EMPLOYE_H
