#ifndef COIN_H
#define COIN_H

#include <QGraphicsObject>
#include <QPainter>
#include "mario.h"
class Coin : public QGraphicsObject
{
    Q_OBJECT
public:
    static int totalcoin;
    static Coin *coinList[40];
    Coin(int x, int y);
    //~Coin();
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    void touchmario();


private:
    QPixmap coinPixmap; // 圖片
    qreal posX; // x座標
    qreal posY; // y座標
    QTimer *timer;
    int coinID;
};

#endif // COIN_H
