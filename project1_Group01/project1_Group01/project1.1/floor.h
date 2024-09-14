#ifndef FLOOR_H
#define FLOOR_H
#include <QGraphicsObject>
#include <QPainter>
class Floor : public QGraphicsObject
{
    Q_OBJECT
public:
    //Floor(); //必須指定xy座標
    Floor(int x, int y);
    Floor(int x, int y ,bool isUnderGround);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    qreal getY() const { return posY; }
private:
    QPixmap floorPixmap;
    qreal posX;
    qreal posY;

};
#endif // FLOOR_H
