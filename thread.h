#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "localserver.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointF>
#include <QGraphicsRectItem>
#include <bulletlist.h>
#include <QLabel>

class MyThread : public QThread
{
    Q_OBJECT

public:
    LocalServer *server;
    QGraphicsScene *scene ;
    QGraphicsView *view ;
    QLabel *label ;
    QVariant condition=0;

    bulletList enemiesList;

    bulletList list;

    QGraphicsPixmapItem* item ;


    void move();
    void itemMove();
    void widget_1();
    void checkCollision();
    void PlayerCollision();
    void pause();
    void definePos();
    void waitPower(QString file);
    void powers();
    void reduceSpeed(int localSpeed);
    void increaseSpeed(int localSpeed);
    void halfDamage();
    void showInformation();
    void DoubleDamage();
    explicit MyThread(QObject *parent = nullptr);


signals:
    void mySignal(int value);

protected:
    void run() override;
};

#endif // MYTHREAD_H
