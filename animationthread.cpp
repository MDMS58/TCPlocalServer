#include "animationthread.h"
#include "widget.h"
AnimationThread::AnimationThread(QObject *parent) : QThread()
{

}
void AnimationThread:: run(){

    while(true){
        msleep(20);
    }
}
