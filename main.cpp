#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "connection.h"
#include "event.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon("C:/Users/salem/Downloads/logoartnexus.png"));
    ArtNexus w;
    w.show();
    Connection c;
    bool test=c.createConnection();
    if(test)
    {
         w.show();
         QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
         notifyIcon->setIcon(QIcon("C:/Users/salem/Downloads/logoartnexus.png"));
         notifyIcon->show();
         // Affiche un message d'information avec une durée d'affichage de 15 secondes
         notifyIcon->showMessage("database is open","connection successful",QSystemTrayIcon::Information,15000);

            }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    return a.exec();
}


