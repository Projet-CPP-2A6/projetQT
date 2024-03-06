#ifndef HHH_H
#define HHH_H

#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class hhhData;

class hhh
{
    Q_OBJECT
public:
    hhh();
    hhh(const hhh &);
    hhh &operator=(const hhh &);
    ~hhh();

private:
    QSharedDataPointer<hhhData> data;
};

#endif // HHH_H
