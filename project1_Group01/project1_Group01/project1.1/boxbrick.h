#ifndef BOXBRICK_H
#define BOXBRICK_H
#include <QGraphicsObject>
#include <QPainter>
enum itemtype{coin,fire_flower,super_mushroom}; //錢、火花、超級蘑菇

class BoxBrick : public QGraphicsObject {
    Q_OBJECT
public:
    static int totalBoxBrick;
    static BoxBrick *boxBrickList[15];
    ~BoxBrick();
    BoxBrick(int x, int y); // 建構函式
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    QRectF collisionRect() const; // 新增碰撞矩形函式
    qreal getY() const;
    qreal getX() const;
    const int  ID ;
private:
    QPixmap BoxbricPixmap; // 普通磚圖片
    qreal posX; // x座標
    qreal posY; // y座標

};


#endif // BOXBRICK_H
