#include "thread.h"
#include <QThread>

#include <QTimer>

QGraphicsRectItem *item = new QGraphicsRectItem(0, 0, 50, 50);

MyThread::MyThread(QObject *parent)
    : QThread(parent)
{
   scene = new QGraphicsScene();
   view = new QGraphicsView(scene);
}

MyThread::~MyThread()
{
}
void MyThread::widget_1(){


    QPixmap pixmap(":bulletFile.png");

    // Crear un QGraphicsPixmapItem y establecer la imagen pixmap
    QGraphicsPixmapItem* rect = new QGraphicsPixmapItem(pixmap);
    rect->setPos(rect->boundingRect().center() - pixmap.rect().center());
    rect->setScale(0.15);

    scene->addItem(rect);
    scene->addItem(item);

    // Agregar el QGraphicsPixmapItem como hijo del QGraphicsRectItem

    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() {

        QPointF currentPos = rect->pos();

        qreal newX = currentPos.x() + 5;
        rect->setPos(newX, currentPos.y());

        if (newX >= scene->width()) {
            rect->setPos(0,item->pos().y());
        }
    });

    timer->start(50);
    view->setFixedSize(500,500);
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

        });
        msleep(0.001);
    }
}
