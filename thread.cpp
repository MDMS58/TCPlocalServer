#include "thread.h"
#include <QThread>
MyThread::MyThread(QObject *parent)
    : QThread(parent)
{
}

MyThread::~MyThread()
{
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
                MyThread::widget.show();
            }

        });
        msleep(0.001);
    }
}
