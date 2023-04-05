#include "bulletitem.h"
#include <QPainter>
bulletItem::bulletItem(const QString &filename, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    fileName=filename;
}
void bulletItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                       QWidget *){
    painter->drawPixmap(position.x(), position.y(), size.width(), size.height(),
            QPixmap(fileName));

}
QRectF bulletItem:: boundingRect() const{
    return QRectF(position.x(), position.y(), size.width(),size.height());
}
