#include "threadserver.h"

ThreadServer::ThreadServer()
{
    server=new LocalServer();
    server->listen(QHostAddress::Any, 1310);
}
void ThreadServer:: run() {

    QByteArray data = server->socket->readAll();
      qDebug()<<data;
}
void ThreadServer:: aux(){
    run();
}
