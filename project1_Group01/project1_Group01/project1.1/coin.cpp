#include "coin.h"
int Coin::totalcoin =0;
Coin* Coin::coinList[40] = { nullptr };
Coin::Coin(int x, int y) : posX(x), posY(y)
{
    coinID=totalcoin; //代表第幾號coin
    totalcoin++;
    coinList[coinID]=this; //將自己加入coinList中
    coinPixmap.load(":/new/prefix1/image/item/coin.png");
    coinPixmap=coinPixmap.scaled(50,50);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Coin::touchmario);
    timer -> start(30);
}

void Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, coinPixmap);
}

QRectF Coin::boundingRect() const {
    return QRectF(posX, posY, coinPixmap.width(), coinPixmap.height());
}

void Coin::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

void Coin::touchmario(){
    Mario *currentmario;
    QList<QGraphicsItem*> collidingmarioList = collidingItems(Qt::IntersectsItemBoundingRect);
    for (QGraphicsItem* item : collidingmarioList) {
        currentmario = dynamic_cast<Mario*>(item);
        if (currentmario) {
            currentmario->getCoin();
            coinList[coinID]=nullptr;
            delete this;
        }
    }
}
