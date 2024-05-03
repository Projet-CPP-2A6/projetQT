#include "connection.h"
#include <QSqlDatabase>

Connection::Connection()
{

}

bool Connection::createConnection()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_projet2A");
db.setUserName("sellami");//inserer nom de l'utilisateur
db.setPassword("sellami");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}
void Connection::closeConnection(){db.close();}
