#include "thread.h"
#include "bulletNode.h"

#include <QThread>
#include <QTimer>



QGraphicsRectItem *item = new QGraphicsRectItem(0, 0, 50, 50);
bool f = true;
bool w = true;

MyThread::MyThread(QObject *parent)
    : QThread(parent)
{
    scene = new QGraphicsScene(0,0,1000,500);
    view = new QGraphicsView(scene);
}

MyThread::~MyThread()
{
}
void MyThread::widget_1(){


    QPixmap pixmap(":bulletFile.png"); const int num_items = 5;

    QGraphicsPixmapItem* items[num_items];
    QGraphicsPixmapItem* enemies[num_items];



    list.insert(num_items);
    bulletNode *aux=list.head;

    for (int i = 0; i < num_items; i++) {
        QGraphicsPixmapItem* rect = new QGraphicsPixmapItem(pixmap);


        rect->setPos((i+1)*100, 0);
        rect->setScale(0.15);
        scene->addItem(rect);


        aux->item= rect;
        aux=aux->nextBullet;

        items[i] = rect;
    }
    scene->addItem(item);


    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() {

        for (int i = 0; i < num_items; i++) {
            QGraphicsPixmapItem* rect = items[i];
            QPointF currentPos = rect->pos();
            qreal newz = currentPos.x() + 5;
            rect->setPos(newz, currentPos.y());


            if (newz >= 1000) {
                rect->setPos(20,item->pos().y());
            }
        }




    });

    timer->start(50);

    view->setFixedSize(1000,500);
    view->show();
}
void MyThread::move(){
    QPixmap pixmap(":nave.png"); const int num_items = 5;

    QGraphicsPixmapItem* enemies[num_items];



    for (int i = 0; i < num_items; i++) {


        QGraphicsPixmapItem* rect_1 = new QGraphicsPixmapItem(pixmap);

        rect_1->setPos(1000-i*100, 0);
        rect_1->setScale(0.15);

        scene->addItem(rect_1);


        enemies[i]=rect_1;

    }
    scene->addItem(item);


    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() {
        for(int i=0; i<num_items; i++){
            QGraphicsPixmapItem* rect_1 = enemies[i];
            QPointF currentPos_1 = rect_1->pos();
            qreal newz_1 = currentPos_1.x() - 5;
            rect_1->setPos(newz_1, currentPos_1.y());


            if (newz_1 <= 000) {
                rect_1->setPos(1000,item->pos().y());
            }
        }

    });

    timer->start(50);
}

void MyThread::run()
{
    bool flag=false;

    while (flag==false) {
        QObject::connect(server->socket, &QTcpSocket::readyRead, [&]() {
            // Leer los datos del socket
            QByteArray data = server->socket->readAll();
            // Imprimir los datos leídos
            if(data=="1"){
                MyThread::widget_1();
                MyThread::move();
            }
            else if (data=="S"){
                item->moveBy(0, 20);
            }
            else if (data=="W"){
                item->moveBy(0, -20);


            }

        });
        msleep(0.0000001);
    }
}
