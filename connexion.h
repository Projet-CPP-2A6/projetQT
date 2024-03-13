#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
class Connection
{
public:
    Connection();
    bool creatconnection();
    void closeconnection();
};

#endif // CONNECTION_H

