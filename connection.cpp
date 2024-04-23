#include "connection.h"

Connection::Connection()
{

}

bool Connection::createConnection()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet_gallery");
db.setUserName("rihemm");
db.setPassword("zoghlami");

if (db.open())
test=true;
    return  test;
}
void Connection::closeConnection(){db.close();}
