#include "runestone.h"
Runestone* Runestone::rune[6][5]={};
int Runestone::attributemap[6][5]={};
Runestone::Runestone(int x, int y, int attribute)
{
    posX = x;
    posY = y;
    isMarking=false;
    attributeType = attribute;
    normal();

}

void Runestone::normal(){
    burn = false;
    weather = false;
    switch (attributeType) {
    case water:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/water_stone.png");
        break;
    case fire:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/fire_stone.png");
        break;
    case earth:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/earth_stone.png");
        break;
    case light:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/light_stone.png");
        break;
    case dark:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/dark_stone.png");
        break;
    case heart:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/heart_stone.png");
        break;
    default:
        return;
    }
    update();
}

void Runestone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, runestonePixmap);
}

QRectF Runestone::boundingRect() const {
    return QRectF(posX, posY, runestonePixmap.width(), runestonePixmap.height());
}

void Runestone::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
    update();
}
void Runestone::weathered(){
    weather = true;
    burn = false;
    switch (attributeType) {
    case water:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/weathered_water_stone.png");
        break;
    case fire:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/weathered_fire_stone.png");
        break;
    case earth:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/weathered_earth_stone.png");
        break;
    case light:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/weathered_light_stone.png");
        break;
    case dark:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/weathered_dark_stone.png");
        break;
    case heart:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/weathered_heart_stone.png");
        break;
    default:
        return;
    }
    update();
}

void Runestone::burning(){
    weather = false;
    burn = true;
    switch (attributeType) {
    case water:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/burning_water_stone.png");
        break;
    case fire:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/burning_fire_stone.png");
        break;
    case earth:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/burnibg_earth_stone.png");
        break;
    case light:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/burning_light_stone.png");
        break;
    case dark:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/burning_dark_stone.png");
        break;
    case heart:
        runestonePixmap.load(":/new/prefix1/dataset/runestone/burning_heart_stone.png");
        break;
    default:
        return;
    }
    update();
}


QPainterPath Runestone::shape() const {
    QPainterPath path;
    // Define the smaller collision shape here, for example:
    QRectF smallerRect = boundingRect().adjusted(25, 25, -25, -25); // Adjust according to your needs
    path.addRect(smallerRect);
    return path;
}

bool Runestone::getburn(){
    return burn;
}

bool Runestone::getweather(){
    return weather;
}

Runestone::~Runestone(){
    rune[coordinate[0]][coordinate[1]]=nullptr;
    attributemap[coordinate[0]][coordinate[1]]=null;
}




