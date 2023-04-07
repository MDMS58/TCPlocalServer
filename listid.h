#ifndef LISTID_H
#define LISTID_H
#include "nodeid.h"


class listid
{
public:
     nodeid *head;


    void insert(int id);

    void deleteNode(int id);
    listid();
};

#endif // LISTID_H
