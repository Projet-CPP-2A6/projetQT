#include "connection.h"

connection::connection()
{

}
bool connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("source_project2A");
    db.setUserName("yassineee");
    db.setPassword("yassineseen");
    if(db.open()) test=true;
    return test;
}
void connection::closeConnection(){db.close();}
