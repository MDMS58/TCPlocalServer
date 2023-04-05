#include "thread.h"
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


    QPixmap pixmap(":bulletFile.png");

    // Crear un QGraphicsPixmapItem y establecer la imagen pixmap
    QGraphicsPixmapItem* rect = new QGraphicsPixmapItem(pixmap);
    rect->setPos(item->pos().x()+20,0);
    rect->setScale(0.15);

    scene->addItem(rect);
    scene->addItem(item);

    // Agregar el QGraphicsPixmapItem como hijo del QGraphicsRectItem

    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() {

       QPointF currentPos = rect->pos();

        qreal newX = currentPos.x() + 5;
        rect->setPos(newX, currentPos.y());

        if(!f){
            item->setPos(item->pos().x(),item->pos().y()+10);

            f=true;
        }
        if(!w){
            item->setPos(item->pos().x(),item->pos().y()-10);

            w=true;
        }


        if (newX >= 1000   ) {
            rect->setPos(20,item->pos().y());
        }
    });

    timer->start(50);

    view->setFixedSize(1000,500);
    view->show();
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
            }
            else if (data=="S"){
                qDebug()<<data;

              f=false;
            }
            else if (data=="W"){
                qDebug()<<data;

               w=false;
            }

        });
        msleep(0.001);
    }
}
