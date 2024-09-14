#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include <cmath>

class Bullet : public QGraphicsObject
{
    Q_OBJECT
public:
    Bullet(qreal x, qreal y);
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    void move(int x, int y);

private:
    QPixmap bulletPixmap; // 圖片
    qreal posX; // x座標
    qreal posY; // y座標
};

#endif // BULLET_H
