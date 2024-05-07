#include "association.h"
#include <QDebug>
#include <QSqlError>

Association::Association()
{

}

bool Association::ajouter()
{
    QSqlQuery query;

    QString ress = QString::number(montant_association);
       query.prepare("insert into associations (nom_association, adresse_association, tel_association, domaine_association,montant_association) "
                     "values (:nom_association, :adresse_association, :tel_association, :domaine_association,:montant_association)");
       // Bind the event details to the query parameters
       query.bindValue(":nom_association", nom_association);
       query.bindValue(":adresse_association", adresse_association);
       query.bindValue(":tel_association", tel_association);
       query.bindValue(":domaine_association", domaine_association);
       query.bindValue(":montant_association", ress);
          return query.exec() ;
}
QSqlQueryModel* Association::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT id_association, nom_association, adresse_association, tel_association, domaine_association, montant_association FROM ASSOCIATIONS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DOMAINE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MONTANT"));

    return model;
}

bool Association::modifier()
{
    QSqlQuery query;
    QString num=QString::number(id_association);
    QString ress=QString::number(montant_association);
    query.prepare("UPDATE ASSOCIATIONS SET nom_association = :nom_association, adresse_association = :adresse_association, tel_association = :tel_association, domaine_association = :domaine_association, montant_association = :montant_association WHERE id_association = :id_association");
    query.bindValue(":id_association", num);
    query.bindValue(":nom_association", nom_association);
    query.bindValue(":adresse_association", adresse_association);
    query.bindValue(":tel_association", tel_association);
    query.bindValue(":domaine_association", domaine_association);
    query.bindValue(":montant_association", ress);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        return false;
    }
}
bool Association::supprimer(int id)
{
     QSqlQuery query;
    // QString num=QString::number(id_association);
    query.prepare("delete from ASSOCIATIONS where id_association=:id_association");
    query.bindValue(":id_association", id);



    return  query.exec();
}
QSqlQueryModel * Association::tri()
{
      QSqlQueryModel * model = new QSqlQueryModel();
      model->setQuery("SELECT * FROM ASSOCIATIONS ORDER BY montant_association");
      return model;
}

int Association::login(QString email, QString mdp)
{
int row_count = 0;
QSqlQuery query;
query.prepare("SELECT * FROM CADMIN where NOM=? and MOTDEPASSE=? ");
query.addBindValue(email);
    query.addBindValue(mdp);
 query.exec();
 while(query.next())
 {
     row_count++;
 }
qDebug() << "Number of Rows: " << row_count;
return row_count;
}

QSqlQueryModel * Association::tri(const QString &columnName)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ASSOCIATIONS ORDER BY " + columnName);
    return model;
}
