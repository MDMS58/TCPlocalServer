#include <QThread>
#include <localserver.h>
class Thread:QThread{
public:
      LocalServer *server;
private:
      void start(){
          run();
      }
protected:


    void run (){
        while(true){
            std::string message=(server->socket->readAll()).toStdString();
            qDebug()<<message.c_str();
            if(message=="2"){
                break;
            }
        }
    }
};
