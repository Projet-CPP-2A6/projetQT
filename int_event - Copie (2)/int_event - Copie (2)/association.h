#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Association
{
private:
    QString nom_association,tel_association, adresse_association, domaine_association;
    int id_association;
    float montant_association;

public:
    // Constructors
    Association();


        Association(int id_association,QString nom_association, QString adresse_association, QString tel_association, QString domaine_association, float montant_association)
        {
            this->id_association=id_association;
            this->nom_association = nom_association;
            this->adresse_association = adresse_association;
            this->tel_association = tel_association;
            this->domaine_association = domaine_association;
            this->montant_association = montant_association;

        }

        Association(QString nom_association, QString adresse_association, QString tel_association, QString domaine_association, float montant_association)
        {

            this->nom_association = nom_association;
            this->adresse_association = adresse_association;
            this->tel_association = tel_association;
            this->domaine_association = domaine_association;
            this->montant_association = montant_association;

        }

        Association (int id_association)
        {
            this->id_association=id_association;
        }
        void setNom_association(QString nom_association){
            this->nom_association = nom_association;
        }
        void setAdresse_association(QString adresse_association){
            this->adresse_association = adresse_association;
        }
        void setTel_association(QString tel_association){
            this->tel_association = tel_association;
        }
        void setDomaine_association(QString domaine_association){
            this->domaine_association = domaine_association;
        }
        void setMontant_association(float montant_association){
            this->montant_association = montant_association;
        }

        void setId_association(int id_association){
            this->id_association = id_association;
        }
        int getId_association(){
            return this->id_association;
        }
        QString getNom_association(){
            return this->nom_association;
        }
        QString getDescript_association(){
            return this->adresse_association;
        }
        QString gettel_association(){
            return this->tel_association;
        }
        float getMontant_association(){
            return this->montant_association;
        }

    // Methods
    bool ajouter();
    QSqlQueryModel *afficher();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel *tri();
int login(QString email , QString mdp);
    QSqlQueryModel *tri(const QString &columnName);

};



#endif // ASSOCIATION_H
