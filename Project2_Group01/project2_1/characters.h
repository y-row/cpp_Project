#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <QGraphicsObject>
#include <QPainter>
#include"runestone.h"

enum characterSkill{changeAttribute,fireFall, resistant,aligntime15 , changetonormalstone};
class Characters: public QGraphicsObject
{
    Q_OBJECT
    friend class GameBase;
public:
    Characters(int x, int y, int id);
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    /*技能*/
    int getCD(){return cd;}
    bool useSkill(int *damage, int *NCAR, int a, int b);
    void minusOneCD();
    int getskill();
private:
    int cd;
    int mySkill;
    QPixmap charactersPixmap; // 圖片
    qreal posX; // x座標
    qreal posY; // y座標
    int attributeType;
    int originalCD;
};

#endif // CHARACTERS_H
