#ifndef TOXIC_MUSHROOM_H
#define TOXIC_MUSHROOM_H

#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include "waterpipe.h"
#include "bullet.h"
#include "floor.h"
#include "mario.h"
#include "normalbrick.h"
#include "stonebrick.h"
#include "boxbrick.h"
#include "brokenbrick.h"
#include "super_mushroom.h"

class Toxic_mushroom : public QGraphicsObject
{
    Q_OBJECT
public:
    Toxic_mushroom(int x, int y);
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    void move();
    void disappear();
    bool disappear0; //判斷需不需要消失
protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QPixmap toxicmushroomPixmap; // 圖片
    qreal posX; // x座標
    qreal posY; // y座標
    QTimer *timer;
    int vx;  //水平移動速度
    int vy; //垂直移動速度
    int g;  //重力加速度
    int timerID;
    int time1; //延遲2秒避免重複判斷
    int time2; //更換圖片的時鐘

};
#endif // TOXIC_MUSHROOM_H
