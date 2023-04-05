#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
class bulletItem;
class scene : public QGraphicsScene
{
public:
    scene(QObject *parent = nullptr);
    bulletItem *bullet_Item;
public slots:
    void onUpdate();
private:

};

#endif // SCENE_H
