#include "scene.h"
#include "bulletitem.h"

#define XPOS 0.0
#define YPOS 0.0
#define WIDTH 600.0
#define HEIGHT 600.0

scene::scene(QObject *parent):
    QGraphicsScene(XPOS, YPOS, WIDTH, HEIGHT, parent)
{
    bullet_Item= new bulletItem((":bulletFile.png"));
    bullet_Item->position=QPointF(20.0, 20.0);
    bullet_Item->size=QSizeF(50.0, 50.0 );
    addItem(bullet_Item);
}
void scene:: onUpdate(){
    bullet_Item->position=QPointF(bullet_Item->position.x()+1, bullet_Item->position.y());
    update();
}
