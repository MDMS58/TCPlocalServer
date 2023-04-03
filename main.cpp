#include "widget.h"
#include <QDebug>
#include <QApplication>
#include <localserver.h>
#include <QThread>
#include <QCloseEvent>
#include <string>
#include "thread.h"
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
        thread->server= server;
        thread->start();
    }
};

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

   // serverManager *manager= new serverManager();
   // manager->waitConnection();

    bulletList list;
    list.insert(10);
    list.deleteNode(7,true);
    list.show();



    return a.exec();

}
