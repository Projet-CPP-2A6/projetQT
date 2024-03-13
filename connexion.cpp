#include "connexion.h"
#include <QDebug>
#include <QSqlError> // Include QSqlError header for error handling

Connection::Connection()
{

}

bool Connection::creatconnection()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source_Projet2A");
    db.setUserName("lamis");
    db.setPassword("lamis");

    if (db.open()) {
        test = true;
    } else {
        // Print error message to identify the reason for connection failure
        QSqlError err = db.lastError();
        qDebug() << "Database error:" << err.text(); // Print the error message
    }

    return test;
}
