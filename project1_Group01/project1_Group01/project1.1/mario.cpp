#include "mario.h"
#include "normalbrick.h"
#include "stonebrick.h"
#include "floor.h"
#include "fire_flower.h"
#include "flag.h"
#include "gamebase.h"
#include "coin.h"
#include "super_mushroom.h"

#include <QGraphicsScene>
#include <QtCore>
#include <algorithm>
#include <ctime>

#include<iostream>//測試用
int Mario::num_coin = 0;
int Mario::hp = 3;
bool Mario::isBig=false;
int Mario::num_bullet=0;
Mario::Mario(int x, int y) {
    posX = x;
    posY = y;
    canJump = true;
    canMoveLeft=canMoveRight=true;
    setFlags(QGraphicsItem::ItemIsFocusable);
    setverticalSpeed(0);
    setgravity(1);
    if(isBig){
        setSpeed(70);
        setjumpSpeed(-20);
    }
    else{
        setSpeed(50);
        setjumpSpeed(-17);
    }

    actionType[1]=actionType[0]=0; //stand, 朝右
    collidingItem = nullptr;
    isMovingUp = false;
    isMovingDown = false;
    isMovingLeft = false;
    isMovingRight = false;
    canfire =(num_bullet)?true: false;
    changeImage();
    time = 0;
    time2 = 0;
    timerID = startTimer(1000);  // 1 sec clock
    star = false;
    mediaPlayer = new MediaPlayer();
}

void Mario::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, marioPixmap);
}

QRectF Mario::boundingRect() const { //碰撞邊界
    return QRectF(posX, posY, marioPixmap.width(), marioPixmap.height());
}

/*change:可以輸入數字設定馬力歐參數*/
void Mario::setSpeed(int x){
    moveSpeed = x;
}
void Mario::setverticalSpeed(int x){
    verticalSpeed = x;
}
void Mario::setgravity(int x){
    gravity = x;
}
void Mario::setjumpSpeed(int x){
    jumpSpeed = x;
}

void Mario::keyPressEvent(QKeyEvent *event) {
    if(hp==0)return; //生命值為0就不能動了
    switch (event->key()){
    case Qt::Key_Up:
        if (canJump && !isJumping) {
            isJumping = true;
            verticalSpeed = jumpSpeed; // 設置垂直速度為跳躍速度
            canJump = false; // 跳躍後設置為 false，直到再次碰到Floor
            // 跳躍音效
            if (isBig) {
                mediaPlayer->playJumpingBigSound();
            } else {
                mediaPlayer->playJumpingSmallSound();
            }
        }
        break;
    case Qt::Key_Left:
        isMovingLeft = true;
        canMoveRight = true; //往左移動的話就不會被右阻擋
        break;
    case Qt::Key_Right:
        isMovingRight = true;
        canMoveLeft   = true; //往右移動的話就不會被左阻擋
        break;
    case Qt::Key_Down:
        isMovingDown=true;
        break;
    default:
        return;
    }
}

QRectF Mario::collisionRect() const {
    QRectF bounding = boundingRect();
    return bounding.adjusted(0, 0, 0, 0); //(左,上,右,下)
}

void Mario::keyReleaseEvent(QKeyEvent *event) {
    if(hp==0)return;//生命為0就不做
    switch (event->key()) {
    case Qt::Key_Up:
        isMovingUp = false;
        break;
    case Qt::Key_Down:
        isMovingDown = false;
        break;
    case Qt::Key_Left:
        isMovingLeft = false;
        actionType[0]=stand; //設為站
        changeImage();
        break;
    case Qt::Key_Right:
        isMovingRight = false;
        actionType[0]=stand; //設為站
        changeImage();
        break;
    default:
        return;
    }

}

void Mario::timerEvent(QTimerEvent *event){
    if(event -> timerId() == timerID and timerID != 0){
        time = (time == 0)? 0 : time - 1;
        if(time2 == 0){
            time2 = 0;
            star = false;
        }
        else
            time2--;
    }
}

int Mario::moveMario() {
    int state=alive;
    if(hp<=0)return dead;//生命為0就不做
    //重力加速度
    if (verticalSpeed != 0) {//垂直移動中就不可以跳
        canJump=false;
    }
    verticalSpeed += gravity;
    posY += verticalSpeed;


    if (isMovingLeft&&canMoveLeft) {
        actionType[1]=L;
        switch(actionType[0]){
            case stand:
                actionType[0]=run1;
            break;
            case run1:
                actionType[0]=run2;
            break;
            default:
                actionType[0]=stand;
        }
        changeImage();
        moveBy(-moveSpeed / 10, 0);
        posX -= moveSpeed / 10;
    }
    if (isMovingRight&&canMoveRight) {
        actionType[1]=R;
        switch(actionType[0]){
            case stand:
                actionType[0]=run1;
            break;
            case run1:
                actionType[0]=run2;
            break;
            default:
                actionType[0]=stand;
        }
        changeImage();
        moveBy(moveSpeed / 10, 0);
        posX += moveSpeed/10;
    }



    QList<QGraphicsItem*> collidingList = collidingItems(Qt::IntersectsItemBoundingRect);


    if(collidingList.count()==0){//代表該落下

        canMoveLeft=canMoveRight=true;
    }


    for (QGraphicsItem* item : collidingList) {
        Floor* currentFloor = dynamic_cast<Floor*>(item);
        QRectF marioRect = boundingRect();                                      //設定馬力歐的碰撞邊界
        QRectF itemRect = item->boundingRect();                                //設定磚的碰撞邊界
        // 檢查碰撞地板
        if (currentFloor) {
            // 調整Mario的位置到Floor的頂部
            if(marioRect.top()+10 > itemRect.top()||(isBig&&marioRect.top()+30> itemRect.top())){
                if(isMovingRight){
                    isMovingRight = false;   // 停止向右移動
                    canMoveRight  = false;   //被右邊碰撞
                }
                else if (isMovingLeft){
                    isMovingLeft = false;    // 停止向左移動
                    canMoveLeft  = false;    //被左邊碰撞
                }
                continue;
            }
            posY = currentFloor->getY() - marioPixmap.height();
            verticalSpeed = 0;
            if(!canJump){// 停止垂直移動
                canJump = true;
                isJumping=false;
                actionType[0]=stand;
                changeImage();

            }
            continue;
        }
        //Brick的碰撞檢測
        NormalBrick* currentBrick = dynamic_cast<NormalBrick*>(item);
        StoneBrick*  stoneBrick   = dynamic_cast<StoneBrick*>(item);
        BrokenBrick* brokenBrick  = dynamic_cast<BrokenBrick*>(item);
        BoxBrick*    boxbrick     = dynamic_cast<BoxBrick*>(item);
        if (currentBrick||stoneBrick||brokenBrick||boxbrick) {
            qreal newposY=(currentBrick)?currentBrick->getY()
                                        :(stoneBrick)?stoneBrick->getY()
                                        :(brokenBrick)?brokenBrick->getY():boxbrick->getY();   //新的y值
            int itop=itemRect.top();
            int ibottom=itemRect.bottom();
            int mbottom= marioRect.bottom();
            int mtop=marioRect.top();
            int ihalf=(ibottom+itop)/2;//箱子中點

            if(mtop<ihalf&&mbottom>ihalf){//先判斷阻擋，若馬力歐的頭比物件中點高，腳卻比物件中點低
                if(isMovingRight){
                    isMovingRight = false;   // 停止向右移動
                    canMoveRight  = false;   //被右邊碰撞
                }
                else if (isMovingLeft){
                    isMovingLeft = false;    // 停止向左移動
                    canMoveLeft  = false;    //被左邊碰撞
                }
                continue;
            }
            else if ((marioRect.bottom() > itemRect.top()&& marioRect.top() < itemRect.top())) {//碰撞上方，使mario可以站在brick上
                posY = newposY - marioPixmap.height();//測試
                if(!canJump){// 停止垂直移動
                    canJump = true;
                    isJumping=false;
                    actionType[0]=stand;
                    changeImage();
                }
                verticalSpeed = 0;
            }
            //碰撞下方
            else if (marioRect.top() < itemRect.bottom() && marioRect.bottom() > itemRect.bottom()) {
                verticalSpeed = 5;
                  /*如果是normal brick 則判斷裡面有無金幣*/
                if(currentBrick){
                    if(currentBrick->canGetCoin){//可以得到金幣
                        QGraphicsItem* coin = new Coin(currentBrick -> getX(), currentBrick -> getY() - 50);
                        scene()->addItem(coin);
                        if(currentBrick->getCoin()){//得到金幣後要不要刪除
                            StoneBrick *newStone = new StoneBrick(currentBrick -> getX(), currentBrick -> getY());
                            scene()->addItem(newStone);  // 将物品添加到场景
                            //使normalbrick消失
                            scene()->removeItem(currentBrick);
                            delete currentBrick;
                        }
                    }
                }
                else if(brokenBrick){//如果是brokenbrick就破壞
                    delete brokenBrick;
                }
                else if(boxbrick){
                    //碰撞下方: 隨機生成coin或Super mushroom或Fire flower
                    QGraphicsItem* newItem1 = nullptr;
                    QGraphicsItem* newItem2 = nullptr;
                    switch (boxbrick->ID){
                        case 1:
                        case 2:
                            newItem1 = new Fire_flower(boxbrick -> getX(), boxbrick -> getY() - 50);
                            break;
                        case 3:
                        case 7:
                            newItem1 = new Coin(boxbrick -> getX(), boxbrick -> getY() - 50);
                            break;
                        case 6:
                        case 4:
                            newItem1 = new SuperStar(boxbrick -> getX(), boxbrick -> getY() - 50);
                        break;
                        default:
                            newItem1 = new Super_mushroom(boxbrick -> getX(), boxbrick -> getY() - 50);
                            break;
                        }
                    //box brick換成stone brick
                    newItem2 = new StoneBrick(boxbrick -> getX(), boxbrick -> getY());
                    scene()->addItem(newItem2);
                    scene()->addItem(newItem1);

                    scene()->removeItem(boxbrick);
                    delete boxbrick;

                }
            }
            continue;
        }
        //waterpipe的碰撞檢測
        WaterPipe* waterpipe= dynamic_cast<WaterPipe*>(item);
        if (waterpipe) {
            //碰撞上方，使mario可以站在waterpipe上
            if (marioRect.bottom() > itemRect.top() && marioRect.top() < itemRect.top()) {
                posY = waterpipe->getY() - marioPixmap.height();
                if(!canJump){// 停止垂直移動
                    canJump = true;
                    isJumping=false;
                    actionType[0]=stand;
                    changeImage();
                }
                if(isMovingDown&&waterpipe->candown){
                    mediaPlayer->playPipeSound();
                    return movingdown;
                }
                verticalSpeed = 0;
            }
            //碰撞左側
            else if (marioRect.bottom() > itemRect.top()){ //代表馬力歐沒有跳超過他
                if(isMovingRight){
                    isMovingRight = false;   // 停止向右移動
                    canMoveRight  = false;   //被右邊碰撞
                }
                else if (isMovingLeft){
                    isMovingLeft = false;    // 停止向左移動
                    canMoveLeft  = false;    //被左邊碰撞
                }
            }
            continue;
        }
        //碰到fire flower時可以發射bullet
        Fire_flower *currentFire;
        currentFire = dynamic_cast<Fire_flower*>(item);
        if (currentFire) {
            canfire = true;
            if(num_bullet < 3){
                num_bullet = 3;   //3
            }
            scene()->removeItem(item);
            delete item;
            continue;
        }

        //super star的碰撞檢測
        SuperStar *currentstar;
        currentstar = dynamic_cast<SuperStar*>(item);
        if (currentstar) {
            delete currentstar;
            time2 = 4; //無敵時間有4秒
            star = true;
            state=invincible;//設定無敵
        }
        // 結束音樂
        Flag_pole *currentflagpole;
        currentflagpole = dynamic_cast<Flag_pole*>(item);
        if (currentflagpole) {
            state= complete;  //遊戲結束
        }
    }
    return state;//說明是存活還是無敵
}

//設定子彈能否發射及數量
void Mario::setcanfire(bool a){
    canfire = a;
}
bool Mario::getcanfire(){
    return canfire;
}
void Mario::setnum_bullet(int a){
    num_bullet = a;
}

int Mario::getnum_bullet(){
    return num_bullet;
}

//mario的位置(生成bullet時會用到)
float Mario::getX(){
    return posX;
}
float Mario::getY(){
    return posY;
}
void Mario::changeImage(){
    if(actionType[0]==die){
        if(isBig){
            marioPixmap.load(":/new/prefix1/image/Mario_big/b_mario_die.png");
        }
        else{
            marioPixmap.load(":/new/prefix1/image/Mario_small/s_mario_die.png");
        }
        return;//死了就不判斷別的
    }
    if(!canJump){
        if(isBig&&actionType[1]==R){//大右跳
           marioPixmap.load(":/new/prefix1/image/Mario_big/mario_R_jump1.png");
           marioPixmap=marioPixmap.scaled(56,80);//設為56*80大小
        }
        else if(isBig&&actionType[1]==L){//大左跳
            marioPixmap.load(":/new/prefix1/image/Mario_big/mario_L_jump1.png");
            marioPixmap=marioPixmap.scaled(56,80);
        }
        else if(actionType[1]==R){//小右跳
            marioPixmap.load(":/new/prefix1/image/Mario_small/s_mario_jump1_R.png");
            marioPixmap=marioPixmap.scaled(50,50);//小馬力歐大小
        }
        else{//小左跳
            marioPixmap.load(":/new/prefix1/image/Mario_small/s_mario_jump1_L.png");
            marioPixmap=marioPixmap.scaled(50,50);
        }
    }
    else{
        switch(actionType[0]){
            case stand:
                if(isBig&&actionType[1]==R){//大右
                   marioPixmap.load(":/new/prefix1/image/Mario_big/mario_R_run0.png");
                   marioPixmap=marioPixmap.scaled(56,80);
                }
                else if(isBig&&actionType[1]==L){//大左
                    marioPixmap.load(":/new/prefix1/image/Mario_big/mario_L_run0.png");
                    marioPixmap=marioPixmap.scaled(56,80);
                }
                else if(actionType[1]==R){//小右
                    marioPixmap.load(":/new/prefix1/image/Mario_small/s_mario_stand_R.png");
                    marioPixmap=marioPixmap.scaled(50,50);
                }
                else{//小左
                    marioPixmap.load(":/new/prefix1/image/Mario_small/s_mario_stand_L.png");
                    marioPixmap=marioPixmap.scaled(50,50);
                }
            break;
            case run1:
                if(isBig&&actionType[1]==R){//大右
                   marioPixmap.load(":/new/prefix1/image/Mario_big/mario_R_run1.png");
                   marioPixmap=marioPixmap.scaled(56,80);
                }
                else if(isBig&&actionType[1]==L){//大左
                    marioPixmap.load(":/new/prefix1/image/Mario_big/mario_L_run1.png");
                    marioPixmap=marioPixmap.scaled(56,80);
                }
                else if(actionType[1]==R){//小右
                    marioPixmap.load(":/new/prefix1/image/Mario_small/s_mario_run1_R.png");
                    marioPixmap=marioPixmap.scaled(50,50);
                }
                else{//小左
                    marioPixmap.load(":/new/prefix1/image/Mario_small/s_mario_run1_L.png");
                    marioPixmap=marioPixmap.scaled(50,50);
                }
            break;
            case run2:
                if(isBig&&actionType[1]==R){//大右
                   marioPixmap.load(":/new/prefix1/image/Mario_big/mario_R_run2.png");
                   marioPixmap=marioPixmap.scaled(56,80);
                }
                else if(isBig&&actionType[1]==L){//大左
                    marioPixmap.load(":/new/prefix1/image/Mario_big/mario_L_run2.png");
                    marioPixmap=marioPixmap.scaled(56,80);
                }
                else if(actionType[1]==R){//小右
                    marioPixmap.load(":/new/prefix1/image/Mario_small/s_mario_run2_R.png");
                    marioPixmap=marioPixmap.scaled(50,50);
                }
                else{//小左
                    marioPixmap.load(":/new/prefix1/image/Mario_small/s_mario_run2_L.png");
                    marioPixmap=marioPixmap.scaled(50,50);
                }
            break;
        }
    }

}
void Mario::marioGoDie(){ //掉到洞裡就會被呼叫
    hp=0;
    actionType[0]=die;
    changeImage();
}

void Mario::touchtoxic(){//碰到了毒魔菇且距上次碰到已過2秒且沒有無敵時間: -HP & 變成小mario & 不能射子彈
    if(time == 0 and !star){
        hp--;
        num_bullet=0;
        isBig = false;
        setjumpSpeed(-17);
        setSpeed(50);
        changeImage();
        canfire = false;
        time = 2;   // 2秒內不會被同一隻影響
        if(hp==0){//如果生命為0就死了
            this->marioGoDie();
            mediaPlayer->playGameOverMusic(); // GameOver 音樂
        }
    }
}


void Mario::touchsuper(){
    if(hp < 3){
       hp++;
    }
    isBig=true;
    setSpeed(70);
    setjumpSpeed(-20);
    posY -= 20;
    update();
    changeImage();
    mediaPlayer->playPowerupSound();
}



qreal Mario::getverticalSpeed(){
    return verticalSpeed;
}

int Mario::gethp(){
    return hp;
}
int Mario::getCoinNumber(){
    return num_coin;
}
void Mario::getCoin(){
    mediaPlayer->playCoinSound();
    num_coin++;
}

bool Mario::getstar(){
    return star;
}

bool Mario::getCanJump(){
    return canJump;
}
