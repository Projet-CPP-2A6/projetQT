#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QSystemTrayIcon>
#include<QString>

class notification
{
public:
    notification();
    void notifAjouterOeuvre();
    void notifSupprimerOeuvre();
    void notifModifierOeuvre();
    void notifvol(const QString &time);
    void notifintervention();
    void notifentre();
    void notifmal();
};

#endif // NOTIFICATION_H
