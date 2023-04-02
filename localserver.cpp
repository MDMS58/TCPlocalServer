#include "localserver.h"
#include <QTcpServer>
#include <QTcpSocket>
LocalServer::LocalServer(QObject *parent)
    : QTcpServer(parent){
    socket=nullptr;

    connect(this, &LocalServer::newConnection, [&](){
       socket=nextPendingConnection();
    });
}
