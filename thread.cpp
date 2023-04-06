#include "thread.h"
#include "bulletNode.h"

#include <QThread>
#include <QTimer>
#include <QRandomGenerator>




int num_items = 5;
bool resetLoop=false;
bool resetLoop1=false;


MyThread::MyThread(QObject *parent)
    : QThread(parent)
{
    scene = new QGraphicsScene(0,0,1000,500);
    view = new QGraphicsView(scene);
    QPixmap pixma((":nave1.png"));
    item = new QGraphicsPixmapItem(pixma);

}


void MyThread::widget_1(){

    item->setPos(0, 0);
    item->setScale(0.08);
    QPixmap pixmap(":bulletFile.png");


    list.insert(num_items);
    bulletNode *aux=list.head;

    for (int i = 0; i < num_items; i++) {
        QGraphicsPixmapItem* rect = new QGraphicsPixmapItem(pixmap);


        rect->setPos((i+1)*100, 47.5);
        rect->setScale(0.15);
        scene->addItem(rect);


        aux->item= rect;

        aux=aux->nextBullet;


    }
    scene->addItem(item);


    QTimer *timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&]() {

        bulletNode *aux= list.head;

        for (int i = 0; i < num_items; i++) {
            QGraphicsPixmapItem* rect = aux->item;

            QPointF currentPos = rect->pos();
            qreal newz = currentPos.x() + 5;
            rect->setPos(newz, currentPos.y());

            if (newz >= 1000) {
                rect->setPos(20,item->pos().y()+47.5);
            }
            if(resetLoop) {
                resetLoop=false;
                break;
            }

            if(aux->nextBullet!=nullptr)
                aux=aux->nextBullet;
        }




    });

    timer->start(50);

    view->setFixedSize(1000,500);
    view->show();
}


void MyThread::checkCollision(){
    QTimer *timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&]() {

        bulletNode *aux=list.head;
        bulletNode *aux_1=enemiesList.head;

        bool flag=false;

        for (int i = 0; i < num_items; i++) {
            for (int j = 0; j < num_items; j++) {
                if (aux->item->collidesWithItem(aux_1->item)) {

                    scene->removeItem(aux->item);
                    scene->removeItem(aux_1->item);

                    list.deleteNode(aux->id);
                    enemiesList.deleteNode(aux_1->id);

                    delete aux;
                    delete aux_1;


                    flag=true;
                    resetLoop=true;
                    resetLoop1=true;
                }
                if(aux_1->nextBullet!=nullptr)
                    aux_1=aux_1->nextBullet;

            }
            if(flag==true){
                num_items--;
                break;
            }
            aux_1=enemiesList.head;
            aux=aux->nextBullet;
        }


    }  );
    timer->start(1);
}




void MyThread::itemMove(){



    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() {
        if(condition==1){
            if(item->pos().y()<370){
                item->moveBy(0, 20);
            }

            condition=0; }
        if(condition==2){
            if(item->pos().y()>10){
                item->moveBy(0, -20);
            }

            condition=0; }


    });
    timer->start(50);


}


void MyThread::move(){
    QPixmap pixmap(":nave.png");

    enemiesList.insert(num_items);

    bulletNode *aux= enemiesList.head;
    for (int i = 0; i < num_items; i++) {
        int numAleatorio = QRandomGenerator::global()->bounded(414);

        QGraphicsPixmapItem* rect_1 = new QGraphicsPixmapItem(pixmap);

        rect_1->setPos(1000-i*100, numAleatorio);
        rect_1->setScale(0.15);

        scene->addItem(rect_1);

        aux->item=rect_1;
        aux=aux->nextBullet;

    }
    scene->addItem(item);
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() {
        bulletNode *aux= enemiesList.head;
        for(int i=0; i<num_items; i++){
            QGraphicsPixmapItem* rect_1 = aux->item;
            QPointF currentPos_1 = rect_1->pos();
            qreal newz_1 = currentPos_1.x() - 5;
            rect_1->setPos(newz_1, currentPos_1.y());


            if (newz_1 <= 0) {
                int numAleatorio = QRandomGenerator::global()->bounded(420);
                rect_1->setPos(1000,numAleatorio);
            }
            if(resetLoop1) {
                resetLoop1=false;
                break;
            }
            if(aux->nextBullet!=nullptr)
                aux=aux->nextBullet;
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
