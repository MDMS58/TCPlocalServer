#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "localserver.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointF>
#include <QGraphicsRectItem>
#include <bulletlist.h>


class MyThread : public QThread
{
    Q_OBJECT

public:
    LocalServer *server;
    QGraphicsScene *scene ;
    QGraphicsView *view ;

    bulletList list;

    QGraphicsPixmapItem* item ;

    void move();
    void widget_1();

    explicit MyThread(QObject *parent = nullptr);
    ~MyThread();

signals:
    void mySignal(int value);

protected:
    void run() override;
};

#endif // MYTHREAD_H
