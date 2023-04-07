#include <QDebug>
#include <QApplication>
#include <localserver.h>
#include <QThread>
#include <thread.h>


#include "bulletitem.h"

#include "bulletlist.h"
#include <iostream>
class serverManager{
public:
    LocalServer *server;
    serverManager(){
        server=new LocalServer();
        server->listen(QHostAddress::Any, 1400);
    }

    void waitConnection(){
        while (true) {
            if (server->waitForNewConnection()) {
                qDebug()<<("Connected");
                break;
            }
            QThread::msleep(0.001);
        }
        MyThread *thread=new MyThread();
        thread->  server= server;
        thread->  start();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serverManager *manager= new serverManager();
     manager->waitConnection();
    return a.exec();
}
