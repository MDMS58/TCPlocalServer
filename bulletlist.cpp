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

    if (head == nullptr) {
        return;
    }


    if (bullet_id == head->id) {
        head = head->nextBullet;
        delete aux;
        return;
    }


    int i = 0;
    while (aux != nullptr) {
        if (i == bullet_id) {
            auxBefore->nextBullet = aux->nextBullet;
            delete aux;
            return;
        }
        i++;
        auxBefore = aux;
        aux = aux->nextBullet;
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
