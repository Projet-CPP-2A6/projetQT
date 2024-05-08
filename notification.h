#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QSystemTrayIcon>
#include<QString>
#include <QMainWindow>
#include "arduino.h"

class notification
{
public:
    notification();
    void notifAjouterOeuvre();
    void notifSupprimerOeuvre();
    void notifModifierOeuvre();
    void notifvol(const QString &time,const QString &oeuvre);
    void notifintervention(const QString &oeuvre);
    void notifentre();
    void notifmal();
    void notifAlert();
private:
    Arduino A;
};

#endif // NOTIFICATION_H
