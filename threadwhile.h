#ifndef THREADWHILE_H
#define THREADWHILE_H

#include <QThread>

class ThreadWhile : public QThread
{
    Q_OBJECT
public:
    explicit ThreadWhile(QString threadName);

    // Переопределяем метод run(), в котором будет
    // располагаться выполняемый код
    void run();
private:
    QString name;
};

#endif // THREADWHILE_H
