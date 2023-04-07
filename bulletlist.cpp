#include "bulletlist.h"
#include <QDebug>
bulletList::bulletList()
{
    head=nullptr;
}
void bulletList:: insert(int bulletAmount){
    int i=0;
    while(bulletAmount!=0){
        bool ban=true;
        bulletNode *newBulletNode=new bulletNode;
        bulletNode *aux=head;
        if(head==nullptr){
            head=newBulletNode;
            head->id=0;
            i++;
            ban=false;
        }
        while(ban && aux->nextBullet!=nullptr ){
            aux=aux->nextBullet;
        }
        if(ban) {
            newBulletNode->id=i;
            i++;
            aux->nextBullet=newBulletNode;}

        bulletAmount--;
    }
}
void bulletList::deleteNode(int bullet_id) {
    bulletNode *aux = head;
    bulletNode *auxBefore = nullptr;
    bool flag=true;

    if (head == nullptr) {
        flag=false;
    }


    else if (bullet_id == head->id) {
        if(head->nextBullet!=nullptr)
            head = head->nextBullet;
    }

    int i = 0;
    while (flag && aux != nullptr) {
        if (i == bullet_id) {

            qDebug()<<"bienn";
            auxBefore->nextBullet = aux->nextBullet;

            break;
        }
        i++;
        auxBefore = aux;
        aux = aux->nextBullet;
    }
}
void operator delete(void* ptr){
    free(ptr);
}
void bulletList:: show(){
    bulletNode *aux=head;
    while(aux!=nullptr){
        qDebug()<<aux->id;
        aux=aux->nextBullet;

    }
}
