#ifndef GREENMONSTER_H
#define GREENMONSTER_H

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include <QProgressBar>
#include "monster.h"

class GreenMonster :  public Monster
{
    public:
        GreenMonster(qreal x, qreal y);
    protected:
        QRectF boundingRect() const override;
};

#endif // GREENMONSTER_H
