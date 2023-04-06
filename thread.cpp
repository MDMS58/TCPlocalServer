#include "thread.h"
#include "bulletNode.h"

#include <QThread>
#include <QTimer>
#include <QRandomGenerator>




const int num_items = 5;

QGraphicsPixmapItem* items[num_items];
QGraphicsPixmapItem* enemies[num_items];


MyThread::MyThread(QObject *parent)
    : QThread(parent)
{
    scene = new QGraphicsScene(0,0,1000,500);
    view = new QGraphicsView(scene);
    QPixmap pixma((":bulletFile.png"));
    item = new QGraphicsPixmapItem(pixma);
}

MyThread::~MyThread()
{
}


void MyThread::widget_1(){

    item->setPos(0, 0);
    item->setScale(0.5);
    QPixmap pixmap(":bulletFile.png");


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

    QObject::connect(timer, &QTimer::timeout, [&]() {

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


void MyThread::checkCollision(){
    QTimer *timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&]() {
        for(int i=0; i<5; i++){
            QPointF bulletPos = items[i]->pos();
            for(int j=0; j<5; j++){
                 QPointF enemyPos = enemies[j]->pos();

                 if(enemyPos.x()-bulletPos.x()<=10)
                     qDebug()<<enemyPos.x()-bulletPos.x();
            }
        }
    }  );
    timer->start(100);
}




void MyThread::itemMove(){
   /* class threadcito:public MyThread{
    protected:
        void run(){
            while(true){
                if(condition==1){
                    item->moveBy(0, 20);
                    condition=0; }
                if(condition==2){
                    item->moveBy(0, -20);
                    condition=0; }
            }
        }
    };*/


    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() {
        if(condition==1){
            item->moveBy(0, 20);
            condition=0; }
        if(condition==2){
            item->moveBy(0, -20);
            condition=0; }


    });
    timer->start(50);
    /*threadcito t;
    t.start();*/


}


void MyThread::move(){
    QPixmap pixmap(":nave.png"); const int num_items = 5;


    for (int i = 0; i < num_items; i++) {
        int numAleatorio = QRandomGenerator::global()->bounded(450);

        QGraphicsPixmapItem* rect_1 = new QGraphicsPixmapItem(pixmap);

        rect_1->setPos(1000-i*100, numAleatorio);
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
                int numAleatorio = QRandomGenerator::global()->bounded(450);
                rect_1->setPos(1000,numAleatorio);
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

            QByteArray data = server->socket->readAll();

            if(data=="1"){
                MyThread::widget_1();
                MyThread::move();
                MyThread::itemMove();
                MyThread::checkCollision();
            }
            else if (data=="S"){
                condition=1;
            }
            else if (data=="W"){
                condition=2;


            }

        });
        msleep(100);
    }
}
