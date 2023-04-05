#ifndef BULLETITEM_H
#define BULLETITEM_H
#include <QGraphicsItem>
#include <QRectF>

class bulletItem: public QGraphicsItem
{
public:
    bulletItem(const QString &filename, QGraphicsItem *parent=nullptr );
    QPointF position;
    QString fileName;
    QSizeF size;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget=0);
    QRectF boundingRect() const;
};

#endif // BULLETITEM_H
