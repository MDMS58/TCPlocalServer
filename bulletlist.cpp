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
void bulletList::deleteNode(int bullet_id, bool flag){
    bulletNode *aux=head; int i=0;
    bulletNode *auxBefore=head;;
    while(aux!=nullptr){
        if(i==bullet_id){
            auxBefore->nextBullet=aux->nextBullet;
            break;
        }
        i++;
        auxBefore=aux;
        if(flag){
            aux=aux->nextBullet;

        }
        else{
            delete aux;
        }
    }
}
void operator delete(void* ptr){

}
void bulletList:: show(){
    bulletNode *aux=head;
    while(aux!=nullptr){
        qDebug()<<aux->id;
        aux=aux->nextBullet;

    }
}
