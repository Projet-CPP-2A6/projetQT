#include "notification.h"
#include <QDateTime>
#include <QSqlQuery>
#include <QMessageBox>
#include <QMainWindow>
#include <QVariant>
#include "arduino.h"

notification::notification()
{

}
void notification::notifAjouterOeuvre()
{
// Crée une icône pour la barre d'état système
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/loggg.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Oeuvres","Nouveau Oeuvre est ajoutée ",QSystemTrayIcon::Information,15000);
}

void notification::notifModifierOeuvre(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/loggg.png"));
    notifyIcon->show();
    // Affiche un message d'information avec une durée d'affichage de 15 secondes
    notifyIcon->showMessage("Gestion des Oeuvres","Nouveau Oeuvre est modifiée",QSystemTrayIcon::Information,15000);
}

void notification::notifSupprimerOeuvre(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/loggg.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Oeuvres","Nouveau Oeuvre est supprimée",QSystemTrayIcon::Information,15000);
}
void notification::notifintervention(const QString &oeuvre){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/loggg.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Oeuvres","Intervention sur l'oeuvre avec REF : "+oeuvre,QSystemTrayIcon::Information,15000);

}
void notification::notifvol(const QString &time,const QString &oeuvre){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/loggg.png"));
    notifyIcon->show();
    QString message = "risque de Vol sur l'oeuvre avec REF : "+oeuvre + " à " + time;
    notifyIcon->showMessage("Gestion des Oeuvres",message,QSystemTrayIcon::Information,15000);

}
void notification::notifentre(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/loggg.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des employees","un employe est entré",QSystemTrayIcon::Information,15000);
}
void notification::notifmal(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/loggg.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des employees","une carte inconnu a été scanné",QSystemTrayIcon::Information,15000);
}
void notification::notifAlert(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/loggg.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Oeuvres","oeuvre 1 en risque",QSystemTrayIcon::Information,15000);
}
