#include "thread.h"
#include "bulletNode.h"

#include <QThread>
#include <QTimer>
#include <QRandomGenerator>




int num_items = 5;
int num_enemies=5;

QTimer *timer = new QTimer();
QTimer *timer1 = new QTimer();
QTimer *timer2 = new QTimer();
QTimer *timer3 = new QTimer();
QTimer *timer4 = new QTimer();

bool booleansControler=false;
bool flag=false;
bool flag1=false;
bool flag2=false;




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
        if(flag==true  && flag2==true){

            // se actualiza la lista

            //actualizar banderas
            flag=false;
            flag2=false;

            //se reinicia
            booleansControler=false;


        }
    });
    timer->start(50);
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




    QObject::connect(timer, &QTimer::timeout, [&]() {

        bulletNode *aux= list.head;
        if(!booleansControler){
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
                flag=true;

            }
        }
        else{
            flag=true;
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

        if(!booleansControler){
            for (int i = 0; i < num_items; i++) {
                for (int j = 0; j < num_enemies; j++) {
                    if (aux->item->collidesWithItem(aux_1->item)) {

                        aux_1->item->setPos(-100, 50);
                        aux->item->setPos(-100, 10);

                        booleansControler=true;
                    }
                    if(aux_1->nextBullet!=nullptr)
                        aux_1=aux_1->nextBullet;
                }

                aux_1=enemiesList.head;
                aux=aux->nextBullet;
            }
        }


    }  );
    timer1->start(50);
}

void MyThread::PlayerCollision()
{


    QObject::connect(timer2, &QTimer::timeout, [&]() {


        bulletNode *aux_1=enemiesList.head;
        if(!booleansControler){

            for (int i = 0; i < num_enemies; i++) {
                if (item->collidesWithItem(aux_1->item)) {


                    aux_1->item->setPos(-10, 50);


                }
                if(aux_1->nextBullet!=nullptr)
                    aux_1=aux_1->nextBullet;


            }

            aux_1=aux_1->nextBullet;
        }
        else{
            flag1=true;
        }

    }  );
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


    QObject::connect(timer4, &QTimer::timeout, [=]() {
        bulletNode *aux= enemiesList.head;
        if(!booleansControler){
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
        }
        else{
            flag2=true;
        }
    });

    timer4->start(25);
}


void MyThread::run()
{
    bool fla=false;

    while (fla==false) {
        QObject::connect(server->socket, &QTcpSocket::readyRead, [&]() {

            QByteArray data = server->socket->readAll();
            qDebug()<<flag << " "<< flag1 << "  "<<flag2;

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
