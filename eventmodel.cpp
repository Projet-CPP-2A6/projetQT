#include "eventmodel.h"
#include <QDebug>
void eventmodel::refresh()
{

    setQuery("SELECT * FROM event ");

}

void eventmodel::refresh1()
{
    setQuery(QString("SELECT * FROM event WHERE id = %1").arg(11));
}
