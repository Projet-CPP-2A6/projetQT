#include "employe.h"

Employe::Employe(int id_e, QString nom_e, QString prenom_e, int tel_e, int salaire_e,QString role_e,QDate debut_conge,QDate fin_conge,QString email,QString mdp)
{
    this->id_e = id_e;
    this->nom_e = nom_e;
    this->prenom_e = prenom_e;
    this->tel_e = tel_e;
    this->salaire_e = salaire_e;
    this->role_e = role_e;
    this->debut_conge = debut_conge;
    this->fin_conge = fin_conge;
    this->email = email;
    this->mdp = mdp;


}

bool Employe::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO EMPLOYE (ID_E, NOM_E, PRENOM_E, TEL_E, SALAIRE_E, ROLE_E, DEBUT_CONGE, FIN_CONGE, EMAIL, MDP) "
                  "VALUES (:id_e, :nom_e, :prenom_e, :tel_e, :salaire_e, :role_e, TO_DATE(:debut_conge, 'DD/MM/YYYY'), TO_DATE(:fin_conge, 'DD/MM/YYYY'), :email, :mdp)");
    query.bindValue(":id_e", id_e);
    query.bindValue(":nom_e", nom_e);
    query.bindValue(":prenom_e", prenom_e);
    query.bindValue(":tel_e", tel_e);
    query.bindValue(":salaire_e", salaire_e);
    query.bindValue(":role_e", role_e);
    query.bindValue(":debut_conge", debut_conge.toString("dd/MM/yyyy"));
    query.bindValue(":fin_conge", fin_conge.toString("dd/MM/yyyy"));
    query.bindValue(":email", email);
    query.bindValue(":mdp", mdp);

    return query.exec();
}


QSqlQueryModel * Employe::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
       model->setQuery("select * from EMPLOYE");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("telephone"));
       model->setHeaderData(5,Qt::Horizontal,QObject::tr("salaire"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("role"));
       model->setHeaderData(6,Qt::Horizontal,QObject::tr("debut_conge"));
       model->setHeaderData(7,Qt::Horizontal,QObject::tr("fin_conge"));
       model->setHeaderData(8,Qt::Horizontal,QObject::tr("email"));
       model->setHeaderData(9,Qt::Horizontal,QObject::tr("mdp"));

       return model;
}
 bool Employe::supprimer(int id_e)
 {
     QSqlQuery query;
     QString id_e_string = QString::number(id_e); // Convertir l'ID en chaîne de caractères
     query.prepare("DELETE FROM EMPLOYE WHERE ID_E = :id_e");
     query.bindValue(":id_e", id_e_string);

     return query.exec();
 }
 bool Employe::modifier(int id_e) {
     QSqlQuery query;
     QString id = QString::number(id_e);
     QString salaire = QString::number(salaire_e);
     QString tel = QString::number(tel_e);

     query.prepare("UPDATE EMPLOYE SET NOM_E=:nom_e, PRENOM_E=:prenom_e, TEL_E=:tel_e, SALAIRE_E=:salaire_e, ROLE_E=:role_e, DEBUT_CONGE=:debut_conge, FIN_CONGE=:fin_conge, EMAIL=:email, MDP=:mdp WHERE ID_E=:id_e");
     query.bindValue(":id_e", id);
     query.bindValue(":nom_e", nom_e);
     query.bindValue(":prenom_e", prenom_e);
     query.bindValue(":tel_e", tel_e);
     query.bindValue(":salaire_e", salaire_e);
     query.bindValue(":role_e", role_e);
     query.bindValue(":debut_conge", debut_conge);
     query.bindValue(":fin_conge", fin_conge);
     query.bindValue(":email", email);
     query.bindValue(":mdp", mdp);

     return query.exec();
 }
 QSqlQueryModel * Employe::tri()
 {
     QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM employe ORDER BY nom_e");
        return model;

 }
 bool Employe::seConnecter()
 {
     QSqlQuery query;
     query.prepare("SELECT * FROM EMPLOYE WHERE email = :email AND mdp = :password");
     query.bindValue(":email",email);
     query.bindValue(":password",mdp);
     query.exec();
     if(query.next()){
         this->nom_e = query.value(1).toString();
         this->prenom_e = query.value(2).toString();
         this->id_e = query.value(0).toInt();
         return true;
     }
     return false;
 }

 QSqlQueryModel * Employe::afficher_calendar(QDate x)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     QString x1=QString::number(x.month()),x2=QString::number(x.day()),x3=QString::number(x.year());
     model->setQuery("select * from EMPLOYE where(extract(day  from DEBUT_CONGE)='"+x2+"' and extract(month  from DEBUT_CONGE)='"+x1+"' and extract(year  from DEBUT_CONGE)='"+x3+"') OR (extract(day  from FIN_CONGE)='"+x2+"' and extract(month  from FIN_CONGE)='"+x1+"' and extract(year  from FIN_CONGE)='"+x3+"')");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("telephone"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("salaire"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("role"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("debut_conge"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("fin_conge"));
     model->setHeaderData(8,Qt::Horizontal,QObject::tr("email"));
     model->setHeaderData(9,Qt::Horizontal,QObject::tr("mdp"));
     return model;
 }

