#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "localserver.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointF>
#include <QGraphicsRectItem>


class MyThread : public QThread
{
    Q_OBJECT

public:
    LocalServer *server;
    QGraphicsScene *scene ;
    QGraphicsView *view ;

    void widget_1();
    explicit MyThread(QObject *parent = nullptr);
    ~MyThread();

signals:
    void mySignal(int value);

protected:
    void run() override;
};

#endif // MYTHREAD_H
