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
    const int num_items = 5;
      QGraphicsPixmapItem* items[num_items];
      for (int i = 0; i < num_items; i++) {
          QGraphicsPixmapItem* rect = new QGraphicsPixmapItem(pixmap);
          rect->setPos((i+1)*100, 0);
          rect->setScale(0.15);
          scene->addItem(rect);
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
        if (!f) {

           item->moveBy(0, 20);
           f=true;
        }
        if (!w) {

            item->moveBy(0, -20);
            w = true;
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
        msleep(0.0000001);
    }
}
