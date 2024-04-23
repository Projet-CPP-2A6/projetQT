#include "connection.h"

Connection::Connection()
{

}

bool Connection::createConnection()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_project2A");
db.setUserName("yassineee");//inserer nom de l'utilisateur
db.setPassword("yassineseen");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}
void Connection::closeConnection(){db.close();}
