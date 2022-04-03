#include "threadwhile.h"

#include <QDebug>

ThreadWhile::ThreadWhile(QString threadName) :
    name(threadName)
{

}

void ThreadWhile::run()
{
    for (int i = 0; i <= 100; i++ ) {
        qDebug() << name << " " << i;
    }
}
