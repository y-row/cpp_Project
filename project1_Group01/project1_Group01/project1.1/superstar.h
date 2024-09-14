#ifndef SUPERSTAR_H
#define SUPERSTAR_H

#include <QGraphicsObject>
#include <QPainter>

class SuperStar : public QGraphicsObject
{
    Q_OBJECT
public:
    SuperStar(int x, int y);
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式

private:
    QPixmap superstarPixmap; // 圖片
    qreal posX; // x座標
    qreal posY; // y座標
};


#endif // SUPERSTAR_H
