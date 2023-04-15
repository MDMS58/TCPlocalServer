#include "thread.h"
#include "bulletNode.h"
#include <QDialog>
#include <QLabel>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <QtXml/QtXml>
#include <QFile>
#include "listid.h"

int itemId;

QVariant enemyId;

QVariant num_items1 = 90;
QVariant num_items=90;
QVariant num_enemies=3;
QVariant speed=7;
QVariant enemiesKilled=0;
QVariant round1=1;

QVariant fileName=":strategy1";
QVariant power1="";
QVariant counterPower1=0;
QVariant power2="";
QVariant life=80;
QVariant bulletSpeed=20;


bool booleansControler=false;
bool doubleDamage=false;
bool HalfDamage=false;

bool flag=false;
bool flag1=false;
bool flag2=false;
bool flag3=false;

bool x=false;


MyThread::MyThread(QObject *parent)
    : QThread(parent)

{
    scene = new QGraphicsScene(0,0,1000,500);
    QPixmap pixap(":background"); // Cargar la imagen de disco
    QBrush textureBrush(pixap);
    scene->setBackgroundBrush(textureBrush);
    view = new QGraphicsView(scene);
    QPixmap pixma((":nave1.png"));
    item = new QGraphicsPixmapItem(pixma);

}

void MyThread::powers(){

    QTimer *timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [=]() {

        // Create an instance of QDomDocument to represent the XML document
        QDomDocument xmlDocument;

        // Load the XML document from a file
        QFile file(fileName.toString());

        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Error opening file:" << file.errorString();
        }
        if (!xmlDocument.setContent(&file)) {
            file.close();

        }

        file.close();


        // Traverse the XML document
        QDomElement root = xmlDocument.documentElement();
        QDomNodeList childNodes = root.childNodes();

        for (int i = 0; i < childNodes.count(); i++) {
            QDomNode childNode = childNodes.item(i);
            if (childNode.isElement()) {
                QDomElement childElement = childNode.toElement();
                if (childElement.tagName() == "strategy") {
                    power1 = childElement.firstChildElement("power1").text();
                    power2 = childElement.firstChildElement("power2").text();
                }
            }
        }
        qDebug() << file.readAll();
    });
    timer->start(100);
}

void MyThread::definePos(){
    QPixmap pixmap(":nave.png");
    bulletNode *aux= enemiesList.head;

    for (int i = 0; i < num_enemies.toInt(); i++) {
        int numAleatorio = QRandomGenerator::global()->bounded(370);

        QGraphicsPixmapItem* rect_1 = new QGraphicsPixmapItem(pixmap);

        rect_1->setPos(1000+i*100, numAleatorio);
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

    QPixmap pixmap1(":bulletFile.png");
    bulletNode *aux1=list.head;

    for (int i = 0; i < num_items.toInt(); i++) {
        QGraphicsPixmapItem* rect1 = new QGraphicsPixmapItem(pixmap1);

        rect1->setPos(-i*100, 52.5);
        rect1->setScale(0.10);
        scene->addItem(rect1);

        aux1->item= rect1;
        aux1=aux1->nextBullet;

    }


}

void MyThread::pause(){
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() {

        if( flag==true  && flag1==true){



            if((enemiesKilled==num_enemies) ){

                //enemiesList.deleteNode(enemyId.toInt());

                enemiesList.deleteNodes();



                bulletNode *auxNode=list.head;

                while(auxNode!=nullptr){
                    scene->removeItem(auxNode->item);
                    auxNode=auxNode->nextBullet;
                }


                enemiesKilled=0;
                if(round1!=5){

                    bulletList auxlist;

                    num_enemies=num_enemies.toInt()+2;
                    auxlist.insert(num_enemies.toInt());
                    enemiesList=auxlist;

                    list.show();

                    list=list.resetList(list);

                    list.show();

                    num_items=num_items1;

                    MyThread::definePos();
                }

                if(round1==1) fileName=":strategy2";
                if(round1==5) {
                    QDialog* dialog = new QDialog();

                    dialog->setWindowTitle("");
                    QLabel* label = new QLabel("Ganaste!!", dialog);

                    dialog->setLayout(new QVBoxLayout);
                    dialog->layout()->addWidget(label);

                    int x = 1000; // posición horizontal
                    int y = 1000; // posición vertical
                    dialog->move(x, y);

                    dialog->show();
                    QTimer::singleShot(2*5000, [=]() {
                        scene->clear();
                        scene->views().first()->close();
                        dialog->close();

                    });

                }
                round1=round1.toInt()+1;
                QThread::msleep(1500);
            }



            enemyId=-1;
            booleansControler=false;
            flag=false;
            flag1=false;


        }




    });
    timer->start(10);
}

void MyThread::checkCollision(){
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&]() {

        if(!booleansControler){
            bulletNode *aux=list.head;
            bulletNode *aux_1=enemiesList.head;
            bool auxFlag=false;
            while(aux!=nullptr) {
                while(aux_1!=nullptr) {
                    if (aux->item->collidesWithItem(aux_1->item)) {
                        if(doubleDamage)
                            aux_1->health=aux_1->health - aux->damage;
                        aux_1->health=aux_1->health - aux->damage;

                        aux->item->setPos(-3500, -3000);
                        aux->erasable=true;
                        num_items1=num_items1.toInt()-1;
                        if (aux_1->health<=0){
                            aux_1->item->setPos(-3000, -50);
                            enemiesKilled=enemiesKilled.toInt()+1;
                            enemyId=aux_1->id;
                            scene->removeItem(aux_1->item);
                            auxFlag=true;
                        }
                        scene->removeItem(aux->item);
                        qDebug()<< round1 << " " <<   enemiesKilled;

                    }
                    aux_1=aux_1->nextBullet;
                }

                aux_1=enemiesList.head;
                aux=aux->nextBullet;
                if(auxFlag) booleansControler=true;

            }
        }
    }


    );
    timer->start(100);
}

void MyThread::widget_1(){

    item->setPos(0, 0);
    item->setScale(0.08);
    QPixmap pixmap(":bulletFile.png");


    list.insert(num_items.toInt());
    bulletNode *aux=list.head;

    for (int i = 0; i < num_items.toInt(); i++) {
        QGraphicsPixmapItem* rect = new QGraphicsPixmapItem(pixmap);

        rect->setPos(-(i+1)*100, 52.5);
        rect->setScale(0.10);
        scene->addItem(rect);

        aux->item= rect;
        aux=aux->nextBullet;

    }
    scene->addItem(item);
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&]() {
        if(!booleansControler){
            bulletNode *aux= list.head;
            while(aux!=nullptr) {
                QGraphicsPixmapItem* rect = aux->item;
                if(aux->item->pos().y()>0){
                    QPointF currentPos = rect->pos();
                    qreal newz = currentPos.x() + bulletSpeed.toInt();
                    rect->setPos(newz, currentPos.y());

                    if (newz >= 1000) {
                        aux->damage=aux->damage-5;
                        rect->setPos(-100*num_items.toInt(),item->pos().y()+52.5);
                    }
                    if (newz < 0) {
                        rect->setPos(newz,item->pos().y()+52.5);
                    }
                }

                aux=aux->nextBullet;
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

void MyThread::PlayerCollision()
{

    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&]() {


        bulletNode *aux_1=enemiesList.head;

        while(aux_1!=nullptr) {
            if (item->collidesWithItem(aux_1->item)) {
                if(HalfDamage)
                    life=life.toInt()-5;
                else{
                    life=life.toInt()-10;
                }


            }

            aux_1=aux_1->nextBullet;


        }

        aux_1=aux_1->nextBullet;
    }

    );
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

    enemiesList.insert(num_enemies.toInt());

    bulletNode *aux= enemiesList.head;
    for (int i = 0; i < num_enemies.toInt(); i++) {
        int numAleatorio = QRandomGenerator::global()->bounded(370);

        QGraphicsPixmapItem* rect_1 = new QGraphicsPixmapItem(pixmap);

        rect_1->setPos(1000+i*100, numAleatorio);
        rect_1->setScale(0.15);
        scene->addItem(rect_1);
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




        aux->item=rect_1;
        aux=aux->nextBullet;

    }
    scene->addItem(item);

    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() {
        if(!booleansControler ){
            bulletNode *aux= enemiesList.head;
            if( counterPower1.toInt()<=0){
                while(aux!=nullptr){
                    QGraphicsPixmapItem* rect_1 = aux->item;
                    bool moveY= rect_1->data(1).toBool();
                    bool UP= rect_1->data(2).toBool();
                    if(aux->item->pos().y()>0){
                        QPointF currentPos_1 = rect_1->pos();
                        qreal newz_1 = currentPos_1.x() - speed.toInt();
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
                    aux=aux->nextBullet;
                }

            }else{
                counterPower1=counterPower1.toInt()-1;
                qDebug()<<counterPower1.toInt();
                if(counterPower1==0) counterPower1=-1;
            }
        }
        else{
            flag1=true;

        }
    }
    );


    timer->start(50);
}

void MyThread::run()
{
    bool fla=false;
    bool flag=false;
    bool flagP=false;
    bool flagP1=false;
    bool flagP2=false;
    bool flagP3=false;
    bool flagP4=false;
    bool flagP5=false;

    while (fla==false) {
        QObject::connect(server->socket, &QTcpSocket::readyRead, [&]() {

            QByteArray data = server->socket->readAll();

            if(data=="start"){
                widget_1();
                move();
                itemMove();
                checkCollision();
                pause();
                powers();
            }
            else if (data=="S"){
                condition=1;
            }
            else if (data=="W"){
                condition=2;

            }

            else if(data=="1"){
                if(power1=="1" && counterPower1!=-1) counterPower1=40;
            }
            else if(data=="2"){
                if(!flag ){
                    if(power2=="2"){
                        bulletNode *aux=list.head;
                        while(aux!=nullptr){
                            aux->damage=20;
                            aux=aux->nextBullet;
                        }
                        flag=true;
                    }
                    else{
                        QString file=":strategy1";
                        waitPower(file);
                    }
                }


            }
            else if(data=="3"){
                if(!flagP){
                    if(  power1=="3"){
                        bulletNode *aux=enemiesList.head;
                        while(aux!=nullptr){
                            if(aux->item->pos().x()>0){
                                aux->item->setPos(-3000, -50);
                                scene-> removeItem(aux->item);
                                enemiesKilled=enemiesKilled.toInt()+1;
                                booleansControler=true;

                                flagP=true;
                                break;
                            }
                            aux=aux->nextBullet;
                        }
                    }
                    else{
                        QString file=":strategy2";
                        waitPower(file);
                    }
                }
            }
            else if(data=="4"){
                if(!flagP1){
                    if(  power2=="4"){
                        qDebug()<<"entro";
                        life=80;
                        flagP1=true;
                    }
                    else{
                        QString file=":strategy2";
                        waitPower(file);
                    }
                }
            }
            else if(data=="5"){
                if(!flagP2){
                    if(  power1=="5"){
                        int localSpeed=speed.toInt();
                        reduceSpeed(localSpeed);
                        flagP2=true;
                    }
                    else{
                        QString file=":strategy3";
                        waitPower(file);
                    }
                }
            }
            else if(data=="6"){
                if(!flagP3){
                    if(  power2=="6"){
                        int localSpeed=speed.toInt();
                        increaseSpeed(localSpeed);
                        flagP3=true;
                    }
                    else{
                        QString file=":strategy3";
                        waitPower(file);
                    }
                }
            }
            else if(data=="7"){
                if(!flagP4){
                    if(  power1=="7"){
                        HalfDamage=true;
                        halfDamage();
                        flagP4=true;
                    }
                    else{
                        QString file=":strategy4";
                        waitPower(file);
                    }
                }
            }
            else if(data=="8"){
                if(!flagP4){
                    if(  power2=="8"){
                        doubleDamage=true;
                        DoubleDamage();
                        flagP4=true;
                    }
                    else{
                        QString file=":strategy4";
                        waitPower(file);
                    }
                }
            }

        });
        msleep(100);
    }
}

void MyThread::DoubleDamage(){
    QTimer::singleShot(2500, [=]{
        doubleDamage=false;
    });
}
void MyThread::halfDamage(){
    QTimer::singleShot(2500, [=]{
        HalfDamage=false;
    });
}
void MyThread::increaseSpeed(int localSpeed){
    bulletSpeed=bulletSpeed.toInt()+10;
    QTimer::singleShot(5000, [=]() {
        bulletSpeed=localSpeed;
    });
}
void MyThread::reduceSpeed(int localSpeed){
    speed=speed.toInt()/2;
    QTimer::singleShot(5000, [=]() {
        speed=localSpeed;
    });
}
void MyThread::waitPower(QString file){
    QDialog* dialog = new QDialog();

    dialog->setWindowTitle("");
    QLabel* label = new QLabel("Poder no encontrado", dialog);

    dialog->setLayout(new QVBoxLayout);
    dialog->layout()->addWidget(label);


    int x = 100; // posición horizontal
    int y = 100; // posición vertical
    dialog->move(x, y);

    dialog->show();


    QTimer::singleShot(5000, [=]() {
        fileName=file;
        dialog->close();
    });

}
