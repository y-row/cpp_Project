#ifndef FLOWER_H
#define FLOWER_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <QTimerEvent>
#include "mario.h"
#include "bullet.h"

class Flower : public QGraphicsObject {
    Q_OBJECT
public:
    Flower(int x, int y); // 建構函式
    QRectF boundingRect() const override; // 返回繪製區域
    bool alive;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    QRectF collisionRect() const; // 新增碰撞矩形函式
    qreal getY() const;
    qreal getX() const;
    void move();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QPixmap FlowerPixmap; // 普通磚圖片
    qreal posX; // x座標
    qreal posY; // y座標
    QTimer *timer;
    int vy; //垂直移動速度
    int timerID;
    int time1; //動畫的計時器
};


#endif // FLOWER_H
