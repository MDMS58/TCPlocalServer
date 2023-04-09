#ifndef BULLETLIST_H
#define BULLETLIST_H
#include "bulletNode.h"

class bulletList
{
public:
    bulletList();
    bulletNode *head;
    bulletList *collector;
    int elements=0;

    void insert(int bulletAmount);
    void show();
    void deleteNodes();
    void deleteNode(int bullet_id);
    int counter();
    void operator delete(void* ptr); //Autores: Michael Marcia e Isaac Solis, Marco no, porque no hizo una basura

};

#endif // BULLETLIST_H
