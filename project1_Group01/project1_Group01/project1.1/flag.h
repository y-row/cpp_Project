#ifndef FLAG_H
#define FLAG_H

#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include "mario.h"

class Flag : public QGraphicsObject
{
    Q_OBJECT
public:
    Flag(int x, int y);
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    void fall(); //穩定下降

private:
    QPixmap flagPixmap; // 圖片
    qreal posX; // x座標
    qreal posY; // y座標

    QTimer *timer;
};

#endif // FLAG_H
