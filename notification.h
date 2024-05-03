#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QSystemTrayIcon>
#include<QString>
#include <QMainWindow>

class notification
{
public:
    notification();
    void notifAjouterOeuvre();
    void notifSupprimerOeuvre();
    void notifModifierOeuvre();
    void notifvol(const QString &time,const QString &oeuvre);
    void notifintervention(const QString &oeuvre);
};

#endif // NOTIFICATION_H
