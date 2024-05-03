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
};

#endif // NOTIFICATION_H
