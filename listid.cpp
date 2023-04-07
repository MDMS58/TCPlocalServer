#include "listid.h"

listid::listid()
{
    head=nullptr;
}
void listid::insert(int id){
    nodeid *node = new nodeid(id);
    nodeid *aux =head;
    if (head == nullptr){
        head=node;
    }
    else{
        while(aux->next!=nullptr){
            aux=aux->next;
        }
        aux->next = node;
    }
}
void listid::deleteNode(int id){
    nodeid *aux=head;
    nodeid *aux_back=nullptr;
    if(head==nullptr){
        return;
    }
    if (aux != nullptr && aux->id == id) {
           head = aux->next;
           delete aux;
           return;
       }
    while (aux != nullptr && aux->id != id) {
            aux_back = aux;
            aux = aux->next;
    }
    aux_back->next=aux->next;
    delete aux;


}
