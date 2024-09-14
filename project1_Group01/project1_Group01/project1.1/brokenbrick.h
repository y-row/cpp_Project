#ifndef BROKENBRICK_H
#define BROKENBRICK_H

#include <QGraphicsObject>
#include <QPainter>

class BrokenBrick : public QGraphicsObject {
    Q_OBJECT
public:
    BrokenBrick(int x, int y); // 建構函式
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    QRectF collisionRect() const; // 新增碰撞矩形函式
    qreal getY() const;

private:
    QPixmap BrobricPixmap; // 普通磚圖片
    qreal posX; // x座標
    qreal posY; // y座標
};

#endif // BROKENBRICK_H
