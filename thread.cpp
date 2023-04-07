#include "thread.h"
#include "bulletNode.h"

#include <QThread>
#include <QTimer>
#include <QRandomGenerator>




int num_items = 5;
int num_enemies=5;
bool resetLoop=false;
bool resetLoop1=false;
bool resetLoop2=false;
bool resetLoop3=false;


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
            if(aux->item->pos().x()>0){
                QPointF currentPos = rect->pos();
                qreal newz = currentPos.x() + 5;
                rect->setPos(newz, currentPos.y());

                if (newz >= 1000) {
                    rect->setPos(20,item->pos().y()+47.5);
                }
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


        for (int i = 0; i < num_items; i++) {
            for (int j = 0; j < num_enemies; j++) {
                if (aux->item->collidesWithItem(aux_1->item)) {

                    scene->removeItem(aux->item);
                    scene->removeItem(aux_1->item);

                    aux_1->item->setPos(-10, 50);
                    aux->item->setPos(-10, 10);
                }
                if(aux_1->nextBullet!=nullptr)
                    aux_1=aux_1->nextBullet;
            }

            aux_1=enemiesList.head;
            aux=aux->nextBullet;
        }


    }  );
    timer->start(50);
}

void MyThread::PlayerCollision()
{
    QTimer *timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&]() {


        bulletNode *aux_1=enemiesList.head;


        for (int i = 0; i < num_enemies; i++) {
            if (item->collidesWithItem(aux_1->item)) {

                scene->removeItem(aux_1->item);

                enemiesList.deleteNode(aux_1->id);



            }
            if(aux_1->nextBullet!=nullptr)
                aux_1=aux_1->nextBullet;

        }
        aux_1=aux_1->nextBullet;

    }  );
    timer->start(50);
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

    enemiesList.insert(num_enemies);

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
        for(int i=0; i<num_enemies; i++){
            QGraphicsPixmapItem* rect_1 = aux->item;\
            if(aux->item->pos().x()>0){
                QPointF currentPos_1 = rect_1->pos();
                qreal newz_1 = currentPos_1.x() - 5;
                rect_1->setPos(newz_1, currentPos_1.y());


                if (newz_1 <= 0) {
                    int numAleatorio = QRandomGenerator::global()->bounded(420);
                    rect_1->setPos(1000,numAleatorio);
                }

            }
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
