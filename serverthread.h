
#include <QThread>
#include <localserver.h>
#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H


class ServerThread:public QThread
{
public:
    ServerThread();
    LocalServer *server;
    void run() override;
};

#endif // SERVERTHREAD_H
