#include "thread.h"
#include "bulletNode.h"

#include <QThread>
#include <QTimer>
#include <QRandomGenerator>

#include "listid.h"


int itemId;
int enemyId;

int num_items = 25;
int num_enemies=10;

QVariant enemiesKilled=0;
QVariant round1=1;

QTimer *timer = new QTimer();
QTimer *timer1 = new QTimer();
QTimer *timer2 = new QTimer();
QTimer *timer3 = new QTimer();
QTimer *timer4 = new QTimer();

bool booleansControler=false;
bool flag=false;
bool flag1=false;
bool flag2=false;
bool flag3=false;
bool x=false;


MyThread::MyThread(QObject *parent)
    : QThread(parent)
{
    scene = new QGraphicsScene(0,0,1000,500);
    view = new QGraphicsView(scene);
    QPixmap pixma((":nave1.png"));
    item = new QGraphicsPixmapItem(pixma);

}

void MyThread::pause(){
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() {
        if( flag==true  && flag2==true && booleansControler==true){


        }
    });
    timer->start(10);
}

void MyThread::widget_1(){

    item->setPos(0, 0);
    item->setScale(0.08);
    QPixmap pixmap(":bulletFile.png");


    list.insert(num_items);
    bulletNode *aux=list.head;

    for (int i = 0; i < num_items; i++) {
        QGraphicsPixmapItem* rect = new QGraphicsPixmapItem(pixmap);


        rect->setPos(-1250+(i+1)*55, 52.5);
        rect->setScale(0.10);
        scene->addItem(rect);

        aux->item= rect;
        aux=aux->nextBullet;


    }
    scene->addItem(item);

    QObject::connect(timer, &QTimer::timeout, [&]() {

        bulletNode *aux= list.head;
        while(aux!=nullptr) {
            QGraphicsPixmapItem* rect = aux->item;
            if(aux->item->pos().x()>-2999){
                QPointF currentPos = rect->pos();
                qreal newz = currentPos.x() + 5;
                rect->setPos(newz, currentPos.y());

                if (newz >= 1000) {
                    aux->damage=aux->damage-5;
                    rect->setPos(20,item->pos().y()+52.5);
                }
                if (newz < 0) {
                    rect->setPos(newz,item->pos().y()+52.5);
                }
            }

            aux=aux->nextBullet;
        }


    });

    timer->start(50);

    view->setFixedSize(1000,500);
    view->show();
}

void MyThread::checkCollision(){
    QObject::connect(timer1, &QTimer::timeout, [&]() {
        bulletNode *aux=list.head;
        bulletNode *aux_1=enemiesList.head;
        while(aux!=nullptr) {
            while(aux_1!=nullptr) {
                if (aux->item->collidesWithItem(aux_1->item)) {

                    aux_1->health=aux_1->health - aux->damage;

                    qDebug()<<aux->damage;
                    qDebug()<<aux_1->health;
                    aux->item->setPos(-3000, 10);
                    scene->removeItem(aux->item);
                    if (aux_1->health<=0){
                        aux_1->item->setPos(-3000, 50);

                        enemiesKilled=enemiesKilled.toInt()+1;
                    }
                            qDebug()<<round1<< " " <<   enemiesKilled;
                    if((enemiesKilled==5 && round1==1)||(enemiesKilled==7 && round1==2)){
                        bulletNode *aux=enemiesList.head;
                        for (int i = 0; i < num_enemies; i++) {
                            int numAleatorio = QRandomGenerator::global()->bounded(370);

                            aux-> item ->setPos(1000+i*50, numAleatorio);
                            aux=aux->nextBullet;


                        }
                        enemiesKilled=0;

                        if(round1==1) {
                            round1=2; }
                        else if(round1==2) round1=3;
                    }



                }
                aux_1=aux_1->nextBullet;
            }

            aux_1=enemiesList.head;
            aux=aux->nextBullet;
        }
    }


    );
    timer1->start(50);
}

void MyThread::PlayerCollision()
{


    QObject::connect(timer2, &QTimer::timeout, [&]() {


        bulletNode *aux_1=enemiesList.head;


        for (int i = 0; i < num_enemies; i++) {
            if (item->collidesWithItem(aux_1->item)) {


                aux_1->item->setPos(-10, 50);


            }
            if(aux_1->nextBullet!=nullptr)
                aux_1=aux_1->nextBullet;


        }

        aux_1=aux_1->nextBullet;
    }

    );
    timer2->start(50);
}

void MyThread::itemMove(){



    QObject::connect(timer3, &QTimer::timeout, [=]() {
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
    timer3->start(50);


}

void MyThread::move(){
    QPixmap pixmap(":nave.png");

    enemiesList.insert(num_enemies);

    bulletNode *aux= enemiesList.head;
    for (int i = 0; i < num_enemies; i++) {
        int numAleatorio = QRandomGenerator::global()->bounded(370);

        QGraphicsPixmapItem* rect_1 = new QGraphicsPixmapItem(pixmap);

        rect_1->setPos(1010+i*50, numAleatorio);
        rect_1->setScale(0.15);
        qreal randomNum = QRandomGenerator::global()->generateDouble();
        if (randomNum < 0.5) {

            rect_1->setData(1, true);
        } else {

            rect_1->setData(1, false);

        }
        qreal randomDireccion = QRandomGenerator::global()->generateDouble() * 0.5 + 0.5;
        if (randomDireccion>0.75){
            rect_1->setData(2, true);
        }else{
            rect_1->setData(2, false);
        }


        scene->addItem(rect_1);

        aux->item=rect_1;
        aux=aux->nextBullet;

    }
    scene->addItem(item);


    QObject::connect(timer4, &QTimer::timeout, [=]() {
        bulletNode *aux= enemiesList.head;
        int Counter=0;
        while(aux!=nullptr){
            QGraphicsPixmapItem* rect_1 = aux->item;
             bool moveY= rect_1->data(1).toBool();
             bool UP= rect_1->data(2).toBool();
            if(aux->item->pos().x()>-2999){
                QPointF currentPos_1 = rect_1->pos();
                qreal newz_1 = currentPos_1.x() - 7;
                if(moveY){
                    rect_1->setPos(newz_1, currentPos_1.y());
                }else{
                    if(rect_1->pos().y()>10 && rect_1->pos().y()<370 ){
                        if(UP){
                            rect_1->setPos(newz_1, currentPos_1.y()-1);
                        }else{
                            rect_1->setPos(newz_1, currentPos_1.y()+1);
                        }

                    }else{
                        rect_1->setPos(newz_1, currentPos_1.y());
                    }


                }




                if (newz_1 <= 0) {
                    int numAleatorio = QRandomGenerator::global()->bounded(420);
                    rect_1->setPos(1000,numAleatorio);
                }


            }
            Counter++;
            if(Counter==5 && round1==1) break;

            if(Counter==7 && round1==2) {
                break;}



            aux=aux->nextBullet;
        }
    }
    );


    timer4->start(50);
}

void MyThread::run()
{
    bool fla=false;

    while (fla==false) {
        QObject::connect(server->socket, &QTcpSocket::readyRead, [&]() {

            QByteArray data = server->socket->readAll();

            if(data=="1"){
                MyThread::widget_1();
                MyThread::move();
                MyThread::itemMove();
                MyThread::checkCollision();
                MyThread::pause();
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
