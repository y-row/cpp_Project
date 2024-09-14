#ifndef NORMALBRICK_H
#define NORMALBRICK_H

#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
class NormalBrick : public QGraphicsObject {
    Q_OBJECT
public:
    NormalBrick(int x, int y); // 建構函式
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    /*碰撞掉金幣的函數*/
    void setNumCoin(int x);
    int getNumCoin();
    bool getCoin(); //判斷要不要變stonebrick
    QRectF collisionRect() const; // 新增碰撞矩形函式
    qreal getY() const;
    qreal getX() const;
    bool canGetCoin;


private:
    void setCanGetCoin();
    QPixmap NorbricPixmap; // 普通磚圖片
    qreal posX; // x座標
    qreal posY; // y座標
    QTimer *timer;
    int coin; //裡面有沒有coin

};



#endif // NORMALBRICK_H
