#ifndef SLIME_H
#define SLIME_H

#include <QGraphicsPixmapItem>
#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include <QProgressBar>
#include "runestone.h"
#include "monster.h"

class Slime : public Monster
{
public:
    Slime(int x, int y, int attribute);
    qreal getX() const;
    qreal getY() const;
    QString getSpecialMechanism() const;
    QString getImagePath() const;

protected:
    QRectF boundingRect() const override;
    void initializeAttributes();
};

#endif // SLIME_H
