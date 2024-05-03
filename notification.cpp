#include "notification.h"
#include <QDateTime>
notification::notification()
{

}
void notification::notifAjouterOeuvre()
{
// Crée une icône pour la barre d'état système
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/amine/Downloads/image_2024-01-29_221240496-removebg-preview (1).png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Oeuvres","Nouveau Oeuvre est ajoutée ",QSystemTrayIcon::Information,15000);
}

void notification::notifModifierOeuvre(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/amine/Downloads/image_2024-01-29_221240496-removebg-preview (1).png"));
    notifyIcon->show();
    // Affiche un message d'information avec une durée d'affichage de 15 secondes
    notifyIcon->showMessage("Gestion des Oeuvres","Nouveau Oeuvre est modifiée",QSystemTrayIcon::Information,15000);
}

void notification::notifSupprimerOeuvre(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/amine/Downloads/image_2024-01-29_221240496-removebg-preview (1).png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Oeuvres","Nouveau Oeuvre est supprimée",QSystemTrayIcon::Information,15000);
}
void notification::notifintervention(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/amine/Downloads/image_2024-01-29_221240496-removebg-preview (1).png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Oeuvres","Intervention",QSystemTrayIcon::Information,15000);
}
void notification:: notification::notifvol(const QString &time){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/amine/Downloads/image_2024-01-29_221240496-removebg-preview (1).png"));
    notifyIcon->show();
    QString message = "risque de Vol at " + time;
    notifyIcon->showMessage("Gestion des Oeuvres",message,QSystemTrayIcon::Information,15000);
}
void notification::notifentre(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/amine/Downloads/image_2024-01-29_221240496-removebg-preview (1).png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des employees","un employe est entré",QSystemTrayIcon::Information,15000);
}
