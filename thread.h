#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "localserver.h"

class MyThread : public QThread
{
    Q_OBJECT

public:
    LocalServer *server;

    explicit MyThread(QObject *parent = nullptr);
    ~MyThread();

signals:
    void mySignal(int value);

protected:
    void run() override;
};

#endif // MYTHREAD_H
