#include "mainwindow.h"
<<<<<<< HEAD
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "connection.h"
#include "event.h"
#include <QObject>
#include <QVariant>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon("C:/Users/salem/Downloads/logoartnexus.png"));
    ArtNexus w;
    w.show();
    connection c;


    bool test=c.createconnection();
    if(test)
    {
         w.show();
         QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
         notifyIcon->setIcon(QIcon("C:/Users/medal/Downloads/lggg.png"));
         notifyIcon->show();
         // Affiche un message d'information avec une durée d'affichage de 15 secondes
         notifyIcon->showMessage("database is open","connection successful",QSystemTrayIcon::Information,15000);

         // Dans main.cpp ou autre
         QQmlApplicationEngine engine;
         ArtNexus myObject;

         engine.rootContext()->setContextProperty("myCppObject", &myObject);



            }
                else
                    QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                QObject::tr("connection failed.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

     w.show();

    return a.exec();
}
=======
#include "connection.h"
#include<QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        connection c;
        bool test=c.createconnection();
        MainWindow w;


        if(test)
        {
             w.show();
             QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

                }
                    else
                        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                    QObject::tr("connection failed.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);

         w.show();

        return a.exec();
    }
>>>>>>> 6e2715b1c56ccbf6489582e16fa8d9d00d8a4bd1
