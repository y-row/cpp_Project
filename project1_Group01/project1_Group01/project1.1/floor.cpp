#include"floor.h"
Floor::Floor(int x, int y)
{
    posX=x;
    posY=y;
    floorPixmap.load(":/new/prefix1/image/brick/floor brick.png");
    floorPixmap=floorPixmap.scaled(50,100);
}
Floor::Floor(int x, int y ,bool isUnderGround){//isUnderGround
    posX=x;
    posY=y;
    floorPixmap.load(":/new/prefix1/image/brick/floor brick underground.png");
    floorPixmap=floorPixmap.scaled(100,100);
}
void Floor::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    /*消除編譯器警告，繪製固定大小的圖案*/
    Q_UNUSED(option); 
    Q_UNUSED(widget);
    painter->drawPixmap(posX,posY,floorPixmap);
}
QRectF Floor::boundingRect() const {
    return QRectF(posX, posY, floorPixmap.width(), floorPixmap.height());
}
