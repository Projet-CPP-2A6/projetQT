
#include "chatbox.h"
#include <QDebug>
#include <QSqlQuery> // Add this line to include the QSqlQuery header

Message::Message() {}
Message::Message(QString sender, QString receiver, QString msg) {
    this->sender = sender;
    this->receiver = receiver;
    this->msg = msg;
    this->timestamp = QDateTime::currentDateTime(); // Set current timestamp
}

bool Message::sendmsg(QString sender, QString receiver) {
    QSqlQuery query;
    query.prepare("INSERT INTO message (sender, receiver, msg, timestamp) VALUES (:sender, :receiver, :msg, TO_DATE(:timestamp, 'YYYY-MM-DD HH24:MI:SS'))");
    query.bindValue(":sender", sender);
    query.bindValue(":receiver", receiver);
    query.bindValue(":msg", msg);
    query.bindValue(":timestamp", timestamp.toString("yyyy-MM-dd hh:mm:ss")); // Format the timestamp
    return query.exec();
}


QSqlQueryModel *Message::retrieveMessages(QString receiver) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT sender, msg, timestamp FROM message WHERE receiver = :receiver AND (sender, timestamp) IN (SELECT sender, MAX(timestamp) FROM message WHERE receiver = :receiver GROUP BY sender)");
    query.bindValue(":receiver", receiver);
    query.exec();
    model->setQuery(query);
    return model;
}


QSqlQueryModel *Message::retrieveFullConversation(QString sender, QString receiver) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT sender, receiver, msg, timestamp FROM message WHERE (sender = :sender AND receiver = :receiver) OR (sender = :receiver AND receiver = :sender) ORDER BY timestamp ASC");
    query.bindValue(":sender", sender);
    query.bindValue(":receiver", receiver);
         qDebug() << "Debug message here"<<sender;
    query.exec();
    model->setQuery(query);
    return model;
}
