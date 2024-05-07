// chatbox.h
#ifndef CHATBOX_H
#define CHATBOX_H

#include <QString>
#include <QSqlQueryModel>
#include <QDateTime> // Include QDateTime header

class Message {
    QString sender;
    QString receiver;
    QString msg;
    QDateTime timestamp;

public:
    Message();
    Message(QString sender, QString receiver, QString msg);
    QSqlQueryModel *retrieveMessages(QString receiver);
    bool sendmsg(QString sender, QString receiver);
    QSqlQueryModel *retrieveFullConversation(QString sender, QString receiver);
};

#endif // CHATBOX_H
