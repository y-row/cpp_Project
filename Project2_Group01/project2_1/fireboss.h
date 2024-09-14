#ifndef FIREBOSS_H
#define FIREBOSS_H

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include <QProgressBar>
#include <QStyleOptionProgressBar>
#include <QTimer>
#include "monster.h"

class FireBoss : public Monster
{
public:
    explicit FireBoss(qreal x, qreal y);
 protected:
    QRectF boundingRect() const override;
};

#endif // FIREBOSS_H
