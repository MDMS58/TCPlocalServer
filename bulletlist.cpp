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
        if(bulletAmount==0) last=newBulletNode;
    }
}
int bulletList::counter(){
    bulletNode *aux=head;
    while(aux!=nullptr){
        elements++;
        aux=aux->nextBullet;
    }
    return elements;
}
void bulletList:: deleteNodes(){

    bulletNode *aux=head;
    while(aux!=nullptr){
        bulletNode *aux2=aux;
        aux=aux->nextBullet;
        delete aux2;
    }
    head=nullptr;


}
void bulletList::deleteNode(int bullet_id) {
    bulletNode *aux = head;
    bulletNode *auxBefore = head;
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
bulletList bulletList:: resetList(bulletList list){
    bulletNode *newHead=nullptr;
    bulletNode *aux=list.head;
     bulletNode *auxiliar=aux;
    while(aux!=nullptr){
        if(!aux->erasable){
            if(newHead==nullptr){
               newHead=aux;
            }
            else{
                bulletNode *secondAux=newHead;
                while (secondAux!=nullptr) {
                    secondAux=secondAux->nextBullet;
                }
                secondAux=aux;
            }
        }


        aux=aux->nextBullet;
    }    bulletList newList;    newList.head=newHead;    return newList;
}
