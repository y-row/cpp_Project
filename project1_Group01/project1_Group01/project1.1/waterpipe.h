#ifndef WATERPIPE_H
#define WATERPIPE_H

#include <QGraphicsObject>
#include <QPainter>

class WaterPipe : public QGraphicsObject {
    Q_OBJECT
public:
    WaterPipe(int x, int y); // 建構函式
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    qreal getY() const;
    bool candown;

private:
    QPixmap pipePixmap; // 水管圖片
    qreal posX; // x座標
    qreal posY; // y座標
};

#endif // WATERPIPE_H
