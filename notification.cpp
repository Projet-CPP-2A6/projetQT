#include "notification.h"
notification::notification()
{

}
void notification::notifAjouterOeuvre()
{
// Crée une icône pour la barre d'état système
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/lggg.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Oeuvres","Nouveau Oeuvre est ajoutée ",QSystemTrayIcon::Information,15000);
}

void notification::notifModifierOeuvre(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/lggg.png"));
    notifyIcon->show();
    // Affiche un message d'information avec une durée d'affichage de 15 secondes
    notifyIcon->showMessage("Gestion des Oeuvres","Nouveau Oeuvre est modifiée",QSystemTrayIcon::Information,15000);
}

void notification::notifSupprimerOeuvre(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/lggg.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Oeuvres","Nouveau Oeuvre est supprimée",QSystemTrayIcon::Information,15000);
}
