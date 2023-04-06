#ifndef BULLETNODE_H
#define BULLETNODE_H
#include <QGraphicsItem>

class bulletNode
{
public:
    QGraphicsPixmapItem *item;
    bulletNode *nextBullet;

    int damage;
    int id;
    bulletNode();
};

#endif // BULLETNODE_H
