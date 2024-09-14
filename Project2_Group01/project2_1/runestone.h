#ifndef RUNESTONE_H
#define RUNESTONE_H
#include <QGraphicsObject>
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
enum attribute{null,water,fire,earth,light,dark,heart};  //屬性
class Runestone: public QGraphicsObject
{
    Q_OBJECT
    friend class GameBase;
    friend class Slime;
    friend class Characters;
public:
    Runestone(int x, int y, int attribute);
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    void normal();
    void weathered();
    void burning();
    bool getburn();
    bool getweather();
    int coordinate[2];
    bool isMarking;
    static int attributemap[6][5];
    static Runestone *rune[6][5];//放符石的指標
    ~Runestone();
    static void swap(Runestone*a, Runestone*b){ //將rune的指標、stonemap的值換掉
        if(a==nullptr||b==nullptr)return;
        int x1=a->coordinate[0];
        int y1=a->coordinate[1];
        int x2=b->coordinate[0];
        int y2=b->coordinate[1];
        rune[x1][y1]=b;
        attributemap[x1][y1]=b->attributeType;
        rune[x2][y2]=a;
        attributemap[x2][y2]=a->attributeType;
        a->coordinate[0]=x2;
        a->coordinate[1]=y2;
        b->coordinate[0]=x1;
        b->coordinate[1]=y1;

    }

    Runestone();

    QRectF collidingRect() const;

    QPainterPath shape() const override;

    int getType() const  { return attributeType; }
    void changeType(int newType){attributeType=newType;}

private:
    QPixmap runestonePixmap; // 圖片
    qreal posX; // x座標
    qreal posY; // y座標
    int attributeType;
    bool burn;
    bool weather;
};

#endif // RUNESTONE_H

