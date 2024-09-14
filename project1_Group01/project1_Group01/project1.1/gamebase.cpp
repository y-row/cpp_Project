#include "gamebase.h"
GameBase::GameBase(QWidget *parent)
    : QGraphicsView(parent) {
    // 載入圖片
    img.load(":/new/prefix1/image/start_screen.png");
    img = img.scaled(1400, 620); // 將圖片縮放成1400寬
    setFixedSize(img.size());
    background = new QGraphicsScene(0, 0, 1400, 620, this);
    background->setBackgroundBrush(img);
    setScene(background);
    isUnderGround=false;
    mediaPlayer = new MediaPlayer();
    undergroundTimer = new QTimer(this);
    gameTimer = new QTimer(this);
    // 設置按鈕
    button_start = new QPushButton(this);
    QSize iconSize(1600, 500);
    QIcon icon(":/new/prefix1/image/start_btn.png");
    button_start->setIcon(icon); // 設置icon
    button_start->setIconSize(iconSize); // 設置icon大小，有點怪怪的
    button_start->move(575, 430);
    button_start->setFixedSize(200, 60);
    connect(button_start, &QPushButton::clicked, this, &GameBase::gameStart);

    lifeLabel = new QLabel("hp: 3", this);
    lifeLabel->setGeometry(10, 10, 200, 30); // 设置位置和大小
    lifeLabel->setStyleSheet("background-color: rgba(255, 255, 255, 150); border: 1px solid black;");
    lifeLabel->hide();

    coinLabel = new QLabel("score: 0", this);
    coinLabel->setGeometry(150, 10, 200, 30);
    coinLabel->setStyleSheet("background-color: rgba(255, 255, 255, 150); border: 1px solid black;");
    coinLabel->hide();

    scoreLabel = new QLabel(this);
    scoreLabel->setGeometry(200, 100, 1000, 200); // (x, y, width, height)
    scoreLabel->setStyleSheet("background-color: rgba(255, 255, 255, 150); border: 1px solid black;");
    scoreLabel->hide();
//    scoreLabel->setText("Score: " + QString::number(Mario::num_coin));
//    scoreLabel->setFont(QFont("Arial", 100));
//    scoreLabel->show();


    mousePosLabel = new QLabel(this);
    mousePosLabel->setFixedSize(200, 20);
    mousePosLabel->move(width() - mousePosLabel->width() -100, 0);
    mousePosLabel->setStyleSheet("background-color: rgba(255, 255, 255, 150); border: 1px solid black;");
    // mario

    mario = new Mario(300, 470);
}

void GameBase::gameStart() {
    // 設定定時器，每25毫秒觸發一次
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateGame()));
    gameTimer->start(30); // 開始定時器改為50
    mediaPlayer->playGroundMusic();
    button_start->hide();

    img.load(":/new/prefix1/image/background.png");
    img.scaledToWidth(7500);
    background->clear();
    background->setSceneRect(0, 0, 7500, 620);
    background->setBackgroundBrush(img);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(FullViewportUpdate);
    lifeLabel->show();
    coinLabel->show();
    //floor brick
    int x = 0, y = 520;
    for (; x < 7500; x += 50) {
        if (x % 1500 == 0 && x){
                x+=150;
                continue;
        }
        Floor *floor = new Floor(x, y);
        background->addItem(floor);
    }
    int numCoins=0; // 硬幣總數
    int coinSpacing = 50; // 硬幣間距
    int coinY; // 硬幣 Y 座標
    int initialCoinY; // 起始 Y 座標
    int coinX; // 硬幣 X 座標
    int initialCoinX; // 起始 X 座標
    int stepX = 50; // 每步 X 座標增加量
    int stepY = 50; // 每步 Y 座標增加量
    int numbrokenbrick;
    int brokenbrickSpacing;
    int initialbrokenbrickx;
    int brokenbricky;
      // --------------------------  普通磚 ------------------------------
    int numnormalbrick;
    int normalbrickSpacing;
    int initialnormalbrickx;
    int normalbricky;
    int initialnormalbricky;
    int normalbrickx;

      // --------------------------  石磚  ------------------------------
    int numstonebrick;
    int stoneSpacing;
    int initialstonebricky;
    int stonebrickx;
    int initialstonebrickx;
    int stonebricky;


// ------------------------------------- 開始場景生成 -----------------------------------------------

      //--------------------------------- Frame 1 -------------------------------- X: 0 - 1400
    if(isUnderGround){
        mario=new Mario(4700,350);
        mediaPlayer->playPipeSound();
        //mario->setPos(4650,350);
    }
    isUnderGround=false;
    background->addItem(mario);
    mario->setFocus();
    centerOn(mario);


    //垂直連續擺放 -- 石磚 (碰撞測試用，之後要刪除)
    numstonebrick = 10;
    stoneSpacing = 50;
    initialstonebricky = 470;
    stonebrickx = -50;
    for (int i = 0; i < numstonebrick; ++i) {
      int stonebricky = initialstonebricky - i * stoneSpacing;
      stonebrick = new StoneBrick(stonebrickx, stonebricky);
      background->addItem(stonebrick);
    }
    stonebrick = new StoneBrick(0,-50);
    background->addItem(stonebrick);
    // 水平連續擺放 -- 普通磚
    numnormalbrick = 5;
    normalbrickSpacing = 50;
    initialnormalbrickx = 750;
    normalbricky = 370;
    for (int i = 0; i < numnormalbrick; i+=2) {//放024
       int normalbrickx = initialnormalbrickx + i * normalbrickSpacing;
       NormalBrick *normalbrick = new NormalBrick(normalbrickx, normalbricky);
       /*暫時將第一個普通磚放3個金幣*/
       if(i==0){
          normalbrick->setNumCoin(3);
       }
       background->addItem(normalbrick);
    }

    stonebrick = new StoneBrick(600, 395);
    background->addItem(stonebrick);
    stonebrick = new StoneBrick(800, 370);
    background->addItem(stonebrick);

    // 問號磚1
    if(BoxBrick::totalBoxBrick!=0){// 代表已經生成過
        if(BoxBrick::boxBrickList[0]){//第0號還在
          background->addItem(BoxBrick::boxBrickList[0]);
        }
        else{
          stonebrick = new StoneBrick(900, 370);
          background->addItem(stonebrick);
        }
    }
    else{ //第一次生成，加進來
        BoxBrick *boxbrick = new BoxBrick(900 ,370 );
        background->addItem(boxbrick);
    }

    // 問號磚2
    if(BoxBrick::totalBoxBrick!=1){// 代表已經生成過
        if(BoxBrick::boxBrickList[1]){//第0號還在
          background->addItem(BoxBrick::boxBrickList[1]);
        }
        else{
          stonebrick = new StoneBrick(850 , 220);
          background->addItem(stonebrick);
        }
    }
    else{ //第一次生成，加進來
      boxbrick = new BoxBrick(850 , 220);
      background->addItem(boxbrick);
    }
    //水管1
    pipe = new WaterPipe(1300, 420);
    background->addItem(pipe);
    toxicmushroom = new Toxic_mushroom(600,300);
    background->addItem(toxicmushroom);

    // 水平連續擺放 -- 金幣
    initialCoinX = 550; // 起始 X 座標
    coinY = 170; // 硬幣 Y 座標
    for (int i = 0; i < 6; ++i) {
        coinX = initialCoinX + i * coinSpacing; // 每個硬幣的 X 座標
        if(Mario::num_coin==0&&Coin::coinList[numCoins]==nullptr){ //代表還沒生成過
          Coin* coin = new Coin(coinX, coinY);
          background->addItem(coin);
        }
        else if(Coin::coinList[numCoins]){
          background->addItem(Coin::coinList[numCoins]);
        }
        numCoins++;
    }

    //測試
    superstar = new SuperStar(500,350);
    background->addItem(superstar);

    turtle = new Turtle(400, 350);  //turtle: 60*74  shell: 50*50
    background->addItem(turtle);

    flower = new Flower(1303, 365); //6(生成): 60*66  4: 60*96  2: 60*126
    background->addItem(flower);

     //--------------------------------- Frame 2 -------------------------------- X: 1400 - 2800

     //水管2
     pipe = new WaterPipe(1800, 420);
     pipe->candown=true;               //第二個水管可以下去
     background->addItem(pipe);

     // 水平連續擺放 -- 普通磚
     numnormalbrick = 4;
     normalbrickSpacing = 50;
     initialnormalbrickx = 2150;
     normalbricky = 300;
     for (int i = 0; i < numnormalbrick; ++i) {
         int normalbrickx = initialnormalbrickx + i * normalbrickSpacing;
         NormalBrick *normalbrick = new NormalBrick(normalbrickx, normalbricky);
         background->addItem(normalbrick);
     }

     // 水平連續擺放 -- 普通磚
     numnormalbrick = 5;
     normalbrickSpacing = 50;
     initialnormalbrickx = 2550;
     normalbricky = 197;
     for (int i = 0; i < numnormalbrick; ++i) {
         int normalbrickx = initialnormalbrickx + i * normalbrickSpacing;
         NormalBrick *normalbrick = new NormalBrick(normalbrickx, normalbricky);
         background->addItem(normalbrick);
     }

    // 水平連續擺放 -- 破壞磚
    numbrokenbrick = 2;
    brokenbrickSpacing = 50;
    initialbrokenbrickx = 2350;
    brokenbricky = 300;
    for (int i = 0; i < numbrokenbrick; ++i) {
       int brokenbrickx = initialbrokenbrickx + i * brokenbrickSpacing;
       BrokenBrick *brokenbrick = new BrokenBrick(brokenbrickx, brokenbricky);
       background->addItem(brokenbrick);
    }

               stonebrick = new StoneBrick(1950, 370);
               background->addItem(stonebrick);

             // 毒蘑菇
             toxicmushroom = new Toxic_mushroom(2150,320);
             background->addItem(toxicmushroom);

             // 毒蘑菇
             toxicmushroom = new Toxic_mushroom(2650,320);
             background->addItem(toxicmushroom);

             // 階梯形上升連續擺放 -- 金幣
          initialCoinX = 2400; // 起始 X 座標
          initialCoinY = 220; // 起始 Y 座標
          for (int i = 0; i <4; ++i) {
              coinX = initialCoinX + i * stepX; // 每個硬幣的 X 座標
              coinY = initialCoinY - i * stepY; // 每個硬幣的 Y 座標
              if(Mario::num_coin==0&&Coin::coinList[numCoins]==nullptr){ //代表還沒生成過
                  Coin* coin = new Coin(coinX, coinY);
                  background->addItem(coin);
              }
              else if(Coin::coinList[numCoins]){
                  background->addItem(Coin::coinList[numCoins]);
              }
              numCoins++;
          }

             //--------------------------------- Frame 3 -------------------------------- X: 2800 - 4200

             //垂直連續擺放 -- 普通磚
             numnormalbrick = 5;
             normalbrickSpacing = 50;
             initialnormalbricky = 470;
             normalbrickx = 2850;
             for (int i = 0; i < numnormalbrick; ++i) {
                 int normalbricky = initialnormalbricky - i * normalbrickSpacing;
                 NormalBrick *normalbrick = new NormalBrick(normalbrickx, normalbricky);
                 background->addItem(normalbrick);
             }

             //水管3
             pipe = new WaterPipe(3350, 420);
             background->addItem(pipe);

             // 水平連續擺放 -- 石磚
             numstonebrick = 4;
             stoneSpacing = 50;
             initialstonebrickx = 3500;
             stonebricky = 320;
             for (int i = 0; i < numstonebrick; ++i) {
                 int stonebrickx = initialstonebrickx + i * stoneSpacing;
                 StoneBrick *stonebrick = new StoneBrick(stonebrickx, stonebricky);
                 background->addItem(stonebrick);
             }

             // 問號磚3
             if(BoxBrick::totalBoxBrick!=2){// 代表已經生成過
                 if(BoxBrick::boxBrickList[2]){//第2號還在
                     background->addItem(BoxBrick::boxBrickList[2]);
                 }
                 else{
                     stonebrick = new StoneBrick(3550 , 320);
                     background->addItem(stonebrick);
                 }
             }
             else{ //第一次生成，加進來

                 boxbrick = new BoxBrick(3550 , 320);
                 background->addItem(boxbrick);
             }


             // 問號磚4
             if(BoxBrick::totalBoxBrick!=3){// 代表已經生成過
                 if(BoxBrick::boxBrickList[3]){//第3號還在
                     background->addItem(BoxBrick::boxBrickList[3]);
                 }
                 else{
                     stonebrick = new StoneBrick(3600 , 320);
                     background->addItem(stonebrick);
                 }
             }
             else{ //第一次生成，加進來
                 boxbrick = new BoxBrick(3600 , 320);
                 background->addItem(boxbrick);
             }

             //水管4
             pipe = new WaterPipe(3800, 420);
             background->addItem(pipe);

             //垂直連續擺放 -- 普通磚
             numnormalbrick = 2;
             normalbrickSpacing = 50;
             initialnormalbricky = 470;
             normalbrickx = 4100;
             for (int i = 0; i < numnormalbrick; ++i) {
                 int normalbricky = initialnormalbricky - i * normalbrickSpacing;
                 NormalBrick *normalbrick = new NormalBrick(normalbrickx, normalbricky);
                 background->addItem(normalbrick);
             }

             //垂直連續擺放 -- 普通磚
             numnormalbrick = 3;
             normalbrickSpacing = 50;
             initialnormalbricky = 470;
             normalbrickx = 4150;
             for (int i = 0; i < numnormalbrick; ++i) {
                 int normalbricky = initialnormalbricky - i * normalbrickSpacing;
                 NormalBrick *normalbrick = new NormalBrick(normalbrickx, normalbricky);
                 background->addItem(normalbrick);
             }


             // 毒蘑菇
             toxicmushroom = new Toxic_mushroom(3500,320);
             background->addItem(toxicmushroom);

             // 階梯形上升連續擺放 -- 金幣
          initialCoinX = 4150; // 起始 X 座標
          initialCoinY = 270; // 起始 Y 座標
          for (int i = 0; i < 5; ++i) {
              coinX = initialCoinX + i * stepX; // 每個硬幣的 X 座標
              coinY = initialCoinY - i * stepY; // 每個硬幣的 Y 座標
              if(Mario::num_coin==0&&Coin::coinList[numCoins]==nullptr){ //代表還沒生成過
                  Coin* coin = new Coin(coinX, coinY);
                  background->addItem(coin);
              }
              else if(Coin::coinList[numCoins]){
                  background->addItem(Coin::coinList[numCoins]);
              }
              numCoins++;
          }



             //--------------------------------- Frame 4 -------------------------------- X:4200 - 5600

             //垂直連續擺放 -- 普通磚
             numnormalbrick = 5;
             normalbrickSpacing = 50;
             initialnormalbricky = 470;
             normalbrickx = 4350;
             for (int i = 0; i < numnormalbrick; ++i) {
                 int normalbricky = initialnormalbricky - i * normalbrickSpacing;
                 NormalBrick *normalbrick = new NormalBrick(normalbrickx, normalbricky);
                 background->addItem(normalbrick);
             }

             //垂直連續擺放 -- 普通磚
             numnormalbrick = 6;
             normalbrickSpacing = 50;
             initialnormalbricky = 470;
             normalbrickx = 4400;
             for (int i = 0; i < numnormalbrick; ++i) {
                 int normalbricky = initialnormalbricky - i * normalbrickSpacing;
                 NormalBrick *normalbrick = new NormalBrick(normalbrickx, normalbricky);
                 background->addItem(normalbrick);
             }



             //水管5
             pipe = new WaterPipe(4700, 420);
             background->addItem(pipe);

             // 水平連續擺放 -- 普通磚 (下)
            numnormalbrick = 15;
            normalbrickSpacing = 50;
            initialnormalbrickx = 4950;
            normalbricky = 370;
            for (int i = 0; i < numnormalbrick; ++i) {
                int normalbrickx = initialnormalbrickx + i * normalbrickSpacing;
                if(normalbrickx==5150)continue;
                NormalBrick *normalbrick = new NormalBrick(normalbrickx, normalbricky);
                background->addItem(normalbrick);
            }

            // 問號磚5
            if(BoxBrick::totalBoxBrick!=4){// 代表已經生成過
                if(BoxBrick::boxBrickList[4]){//第4號還在
                    background->addItem(BoxBrick::boxBrickList[4]);
                }
                else{
                    stonebrick = new StoneBrick(5150 , 370);
                    background->addItem(stonebrick);
                }
            }
            else{ //第一次生成，加進來
                boxbrick = new BoxBrick(5150 , 370);
                background->addItem(boxbrick);
            }


            // 水平連續擺放 -- 普通磚 (上)
            numnormalbrick = 15;
            normalbrickSpacing = 50;
            initialnormalbrickx = 4950;
            normalbricky = 170;
            for (int i = 0; i < numnormalbrick; ++i) {
                int normalbrickx = initialnormalbrickx + i * normalbrickSpacing;
                NormalBrick *normalbrick = new NormalBrick(normalbrickx, normalbricky);
                background->addItem(normalbrick);
            }





             toxicmushroom = new Toxic_mushroom(4800,300);
             background->addItem(toxicmushroom);

             // test supermushroom (須由碰撞問號磚產生)
            /* supermushroom = new Super_mushroom(5100,460);
             background->addItem(supermushroom);*/

             // 水平連續擺放 -- 金幣
             initialCoinX = 4400; // 起始 X 座標
             coinY = 70; // 硬幣 Y 座標
             for (int i = 0; i < 4; ++i) {
                 coinX = initialCoinX + i * coinSpacing; // 每個硬幣的 X 座標
                 if(Mario::num_coin==0&&Coin::coinList[numCoins]==nullptr){ //代表還沒生成過
                     Coin* coin = new Coin(coinX, coinY);
                     background->addItem(coin);
                 }
                 else if(Coin::coinList[numCoins]){
                     background->addItem(Coin::coinList[numCoins]);
                 }
                 numCoins++;
             }

             // 水平連續擺放 -- 金幣
          initialCoinX = 5050; // 起始 X 座標
          coinY = 420; // 硬幣 Y 座標
          for (int i = 0; i < 8; ++i) {
              coinX = initialCoinX + i * coinSpacing; // 每個硬幣的 X 座標
              if(Mario::num_coin==0&&Coin::coinList[numCoins]==nullptr){ //代表還沒生成過
                  Coin* coin = new Coin(coinX, coinY);
                  background->addItem(coin);
              }
              else if(Coin::coinList[numCoins]){
                  background->addItem(Coin::coinList[numCoins]);
              }
              numCoins++;
          }


             //--------------------------------- Frame 5 -------------------------------- X: 5600 - 7000

             toxicmushroom = new Toxic_mushroom(5600,370);
             background->addItem(toxicmushroom);
             toxicmushroom = new Toxic_mushroom(5700,300);
             background->addItem(toxicmushroom);


             //水管6
             pipe = new WaterPipe(5850, 420);
             background->addItem(pipe);


             // 水平連續擺放 -- 石磚
             numstonebrick = 6;
             stoneSpacing = 50;;
             initialstonebrickx = 6200;
             stonebricky = 470;
             for (int i = 0; i < numstonebrick; ++i) {
                 int stonebrickx = initialstonebrickx + i * stoneSpacing;
                 StoneBrick *stonebrick = new StoneBrick(stonebrickx, stonebricky);
                 background->addItem(stonebrick);
             }

             // 水平連續擺放 -- 石磚
             numstonebrick = 5;
             stoneSpacing = 50;
             initialstonebrickx = 6250;
             stonebricky = 420;
             for (int i = 0; i < numstonebrick; ++i) {
                 int stonebrickx = initialstonebrickx + i * stoneSpacing;
                 StoneBrick *stonebrick = new StoneBrick(stonebrickx, stonebricky);
                 background->addItem(stonebrick);
             }

             // 水平連續擺放 -- 石磚
             numstonebrick = 4;
             stoneSpacing = 50;
             initialstonebrickx = 6300;
             stonebricky = 370;
             for (int i = 0; i < numstonebrick; ++i) {
                 int stonebrickx = initialstonebrickx + i * stoneSpacing;
                 StoneBrick *stonebrick = new StoneBrick(stonebrickx, stonebricky);
                 background->addItem(stonebrick);
             }

             // 水平連續擺放 -- 石磚
             numstonebrick = 3;
             stoneSpacing = 50;
             initialstonebrickx = 6350;
             stonebricky = 320;
             for (int i = 0; i < numstonebrick; ++i) {
                 int stonebrickx = initialstonebrickx + i * stoneSpacing;
                 StoneBrick *stonebrick = new StoneBrick(stonebrickx, stonebricky);
                 background->addItem(stonebrick);
             }

             // 水平連續擺放 -- 石磚
             numstonebrick = 2;
             stoneSpacing = 50;
             initialstonebrickx = 6400;
             stonebricky = 270;
             for (int i = 0; i < numstonebrick; ++i) {
                 int stonebrickx = initialstonebrickx + i * stoneSpacing;
                 StoneBrick *stonebrick = new StoneBrick(stonebrickx, stonebricky);
                 background->addItem(stonebrick);
             }

             // 垂直連續擺放 -- 金幣
          initialCoinY = 320; // 起始 Y 座標
          coinX = 5850; // 硬幣 X 座標
          for (int i = 0; i < 2; ++i) {
              coinY = initialCoinY - i * coinSpacing; // 每個硬幣的 Y 座標
              if(Mario::num_coin==0&&Coin::coinList[numCoins]==nullptr){ //代表還沒生成過
                  Coin* coin = new Coin(coinX, coinY);
                  background->addItem(coin);
              }
              else if(Coin::coinList[numCoins]){
                  background->addItem(Coin::coinList[numCoins]);
              }
              numCoins++;
          }
            // 階梯形上升連續擺放 -- 金幣
          initialCoinX = 6200; // 起始 X 座標
          initialCoinY = 370; // 起始 Y 座標
          for (int i = 0; i < 6; ++i) {
              coinX = initialCoinX + i * stepX; // 每個硬幣的 X 座標
              coinY = initialCoinY - i * stepY; // 每個硬幣的 Y 座標
              if(Mario::num_coin==0&&Coin::coinList[numCoins]==nullptr){ //代表還沒生成過
                  Coin* coin = new Coin(coinX, coinY);
                  background->addItem(coin);
              }
              else if(Coin::coinList[numCoins]){
                  background->addItem(Coin::coinList[numCoins]);
              }
              numCoins++;
          }
    flag = new Flag(7000,50);
    background->addItem(flag);


    //旗桿
    flagpole = new Flag_pole(7060,20);
    background->addItem(flagpole);




}
//按左鍵射出子彈(位置偏移修正)
void GameBase::mousePressEvent(QMouseEvent *event){
    if(event -> button() == Qt::LeftButton){
        QPointF marioScenePos = mario->mapToScene(mario->pos()); //將馬力歐位置找出來
        QPointF scenePos = mapToScene(event->pos()); //找出滑鼠對遊戲畫面的座標
        if(mario -> getcanfire() and Mario::num_bullet > 0&&mario->getCanJump()){
            mediaPlayer->playFireballSound(); // 播放火焰彈音效
            bullet = new Bullet(marioScenePos.x()+320 , mario->getY()+25,scenePos.x(), event -> pos().y());
            background->addItem(bullet);
            mario -> setnum_bullet(mario -> getnum_bullet() - 1);
            if((marioScenePos.x()+250 - scenePos.x()) > 0){
                mario -> actionType[1] = L;
                mario -> changeImage();
            }
            else{
                mario -> actionType[1] = R;
                mario -> changeImage();
            }
        }
    }
}

void GameBase::mouseMoveEvent(QMouseEvent *event) {
        QPoint viewPos = event->pos();
}


void GameBase::updateGame() {
    // 更新遊戲的狀態，例如更新Mario的位置、確認碰撞等
    lifeLabel->setText("HP: " + QString::number(Mario::hp));
    coinLabel->setText("Score: " + QString::number(Mario::num_coin));
    mousePosLabel->setText(QString("bullet:")+QString::number(Mario::num_bullet));
    mousePosLabel->move(width() - mousePosLabel->width() - 100, 0);
    if(mario->getY()>600){

        mario->marioGoDie(); //掉下去就直接死掉
    }
    switch(mario->moveMario()){
    case invincible:
            mediaPlayer->playSuperstarMusic();
            QTimer::singleShot(4000, mediaPlayer, &MediaPlayer::stopSuperstarMusic);
            if(isUnderGround){
                QTimer::singleShot(4500, mediaPlayer, &MediaPlayer::playUndergroundMusic);
            }
            else{
                QTimer::singleShot(4500, mediaPlayer, &MediaPlayer::playGroundMusic);
            }
    break;
    case dead:
            mediaPlayer->playGameOverMusic();
            mario->marioGoDie();
    break;
    case complete:
        gameWin();
    break;
    case movingdown: //往下移動
        /*設定動畫*/
        animation = new QPropertyAnimation(mario, "pos");
        animation->setDuration(2000);
        endPos = mario->pos() + QPointF(0, 82);
        animation->setEndValue(endPos);
        animation->setEasingCurve(QEasingCurve::Linear);
        if(gameTimer->isActive()){
            disconnect(gameTimer, SIGNAL(timeout()), this, SLOT(updateGame()));
            gameTimer->stop();
            animation->start();
            isUnderGround=true;
            connect(animation, &QPropertyAnimation::finished, this, &GameBase::switchToUndergroundScene);
        }
        else{
            disconnect(undergroundTimer, SIGNAL(timeout()), this, SLOT(updateGame()));
            undergroundTimer->stop();
            animation->start();

            connect(animation, &QPropertyAnimation::finished, this, &GameBase::gameStart);
        }
    break;
    default:
        scene()->update();
        centerOn(mario);
    }
    // 重新繪製場景
}

// 地下隱藏通道
void GameBase::switchToUndergroundScene()
{
    connect(undergroundTimer, SIGNAL(timeout()), this, SLOT(updateGame()));
    lifeLabel->show();
    coinLabel->show();
    img.load(":/new/prefix1/image/background_black.png");
    img=img.scaledToWidth(7500);
    //background->removeItem(mario);
    for(int i=0;i<40;i++){
        if(Coin::coinList[i]){
            background->removeItem(Coin::coinList[i]);
        }
    }
    for(int i=0;i<9;i++){
        if(BoxBrick::boxBrickList[i]){
            background->removeItem(BoxBrick::boxBrickList[i]);
        }
    }
    background->clear();
    background->setSceneRect(0, 0, 3000, 620);
    background->setBackgroundBrush(img);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);




    mediaPlayer->playUndergroundMusic();

    //floor brick
    int x = 0, y = 520;
    for (; x < 3000; x += 100) {
        if (x % 1500 == 0 && x){
                x+=150;
                continue;
        }
        Floor *floor = new Floor(x, y,true); //創建新地板
        background->addItem(floor);
    }

    x = 0, y = 20;
    for (; x < 3000; x += 50) {
        if (x % 1500 == 0 && x){
                x+=100;
                continue;
        }
        BrokenBrick *brokenbrick = new BrokenBrick(x, y);
        background->addItem(brokenbrick);
    }
    //垂直連續擺放 -- 石磚 (碰撞測試用，之後要刪除)
    for (int i = 0; i < 10; ++i) {
        int stonebricky = 470 - i * 50;
        stonebrick = new StoneBrick(-50, stonebricky);
        background->addItem(stonebrick);
    }

    // ------------------------------------- 磚塊生成範例(註解部分先不要刪除) -----------------------------------------------
    // ---------------------------- 金幣 ------------------------------

    int numCoins; // 硬幣數量
    int coinSpacing = 50; // 硬幣間距
    int coinY; // 硬幣 Y 座標
    int coinX; // 硬幣 X 座標
    int initialCoinX; // 起始 X 座標


    // --------------------------  普通磚 ------------------------------
    int numnormalbrick;
    int normalbrickSpacing;
    int initialnormalbrickx;
    int normalbricky;

    // --------------------------  石磚  ------------------------------
    int numstonebrick;
    int stoneSpacing;
    int initialstonebricky;
    int stonebrickx;
    int numbrokenbrick;
    int brokenbrickSpacing;
    int initialbrokenbrickx;
    int brokenbricky;
    int initialbrokenbricky;
    int brokenbrickx;
    // ------------------------------------- 開始場景生成 -----------------------------------------------

    //--------------------------------- Frame 1 -------------------------------- X: 0 - 1400


    // mario
    mario = new Mario(300, 470);
    //mario->setPos(0,150);
    background->addItem(mario);
    mario->setFocus();

    // 問號磚
    boxbrick = new BoxBrick( 625, 390);
    background->addItem(boxbrick);

    // 問號磚
    boxbrick = new BoxBrick( 675, 390);
    background->addItem(boxbrick);

    toxicmushroom = new Toxic_mushroom(670,470);
    background->addItem(toxicmushroom);

    /*  // 水平連續擺放 -- 金幣
    numCoins = 4; // 硬幣數量
    initialCoinX = 1579; // 起始 X 座標
    coinY = 189; // 硬幣 Y 座標
    for (int i = 0; i < numCoins; ++i) {
    coinX = initialCoinX + i * coinSpacing; // 每個硬幣的 X 座標
    Coin* coin = new Coin(coinX, coinY);
    background->addItem(coin);
    }*/

    // 水平連續擺放 -- 普通磚
    numnormalbrick = 4;
    normalbrickSpacing = 50;
    initialnormalbrickx = 725;
    normalbricky = 390;
    for (int i = 0; i < numnormalbrick; ++i) {
    int normalbrickx = initialnormalbrickx + i * normalbrickSpacing;
    NormalBrick *normalbrick = new NormalBrick(normalbrickx, normalbricky);
    background->addItem(normalbrick);
    }

    //垂直連續擺放 -- 石磚
    numstonebrick = 2;
    stoneSpacing = 50;
    initialstonebricky = 470;
    stonebrickx = 1231;
    for (int i = 0; i < numstonebrick; ++i) {
    int stonebricky = initialstonebricky - i * stoneSpacing;
    StoneBrick *stonebrick = new StoneBrick(stonebrickx, stonebricky);
    background->addItem(stonebrick);
    }

    //垂直連續擺放 -- 石磚
    numstonebrick = 3;
    stoneSpacing = 50;
    initialstonebricky = 470;
    stonebrickx = 1450;
    for (int i = 0; i < numstonebrick; ++i) {
    int stonebricky = initialstonebricky - i * stoneSpacing;
    StoneBrick *stonebrick = new StoneBrick(stonebrickx, stonebricky);
    background->addItem(stonebrick);
    }

    //--------------------------------- Frame 2 -------------------------------- X: 1400 - 2800

    //垂直連續擺放 -- 石磚
    numstonebrick = 3;
    stoneSpacing = 50;
    initialstonebricky = 470;
    stonebrickx = 1750;
    for (int i = 0; i < numstonebrick; ++i) {
    int stonebricky = initialstonebricky - i * stoneSpacing;
    StoneBrick *stonebrick = new StoneBrick(stonebrickx, stonebricky);
    background->addItem(stonebrick);
    }


    pipe = new WaterPipe(1948, 420);
    background->addItem(pipe);

    flower = new Flower(1950, 364); //6(生成): 60*66  4: 60*96  2: 60*126
    background->addItem(flower);

    turtle = new Turtle(2202, 454);  //turtle: 60*74  shell: 50*50
    background->addItem(turtle);



   /* //水平連續擺放 -- 破壞磚
    numbrokenbrick = 8;
    brokenbrickSpacing = 50;
    initialbrokenbrickx = 2105;
    brokenbricky = 120;
    for (int i = 0; i < numbrokenbrick; ++i) {
    int brokenbrickx = initialbrokenbrickx + i * brokenbrickSpacing;
    BrokenBrick *brokenbrick = new BrokenBrick(brokenbrickx, brokenbricky);
    background->addItem(brokenbrick);
    }
*/
    //垂直連續擺放 -- 破壞磚
    numbrokenbrick = 3;
    brokenbrickSpacing = 50;
    initialbrokenbricky = 340;
    brokenbrickx = 2105;
    for (int i = 0; i < numbrokenbrick; ++i) {
    int brokenbricky = initialbrokenbricky - i * brokenbrickSpacing;
    BrokenBrick *brokenbrick = new BrokenBrick(brokenbrickx, brokenbricky);
    background->addItem(brokenbrick);
    }

    //水平連續擺放 -- 破壞磚
    numbrokenbrick = 9;
    brokenbrickSpacing = 50;
    initialbrokenbrickx = 2105;
    brokenbricky = 390;
    for (int i = 0; i < numbrokenbrick; ++i) {
      int brokenbrickx = initialbrokenbrickx + i * brokenbrickSpacing;
      BrokenBrick *brokenbrick = new BrokenBrick(brokenbrickx, brokenbricky);
      background->addItem(brokenbrick);
    }

    //垂直連續擺放 -- 破壞磚
    numbrokenbrick = 2;
    brokenbrickSpacing = 50;
    initialbrokenbricky = 240;
    brokenbrickx = 2505;
    for (int i = 0; i < numbrokenbrick; ++i) {
    int brokenbricky = initialbrokenbricky - i * brokenbrickSpacing;
    BrokenBrick *brokenbrick = new BrokenBrick(brokenbrickx, brokenbricky);
    background->addItem(brokenbrick);
    }

    // 問號磚
    boxbrick = new BoxBrick( 2220, 260);
    background->addItem(boxbrick);

    // 碎磚
    BrokenBrick *brokenbrick =new BrokenBrick( 2270, 260);
    background->addItem(brokenbrick);

    // 碎磚
    brokenbrick =new BrokenBrick( 2320, 260);
    background->addItem(brokenbrick);

    // 問號磚
    boxbrick = new BoxBrick( 2370, 260);
    background->addItem(boxbrick);


    pipe = new WaterPipe(2760, 420);
    pipe->candown=true;
    background->addItem(pipe);

    undergroundTimer->start(30);
}

void GameBase::gameWin(){

    if(Mario::num_coin>=20){
       mediaPlayer->playLevelCompleteMusic();
       disconnect(gameTimer, SIGNAL(timeout()), this, SLOT(updateGame()));
       flag->fall();
       QLabel *label=new QLabel("YOU Win!!", this);
       label->setFont(QFont("Arial", 50));
       label->show();
       label->setGeometry(450, 350, 1000, 200);
       scoreLabel->setText("Score: " + QString::number(Mario::num_coin));
       scoreLabel->setFont(QFont("Arial", 100));
       scoreLabel->show();
    }
    else {
        mediaPlayer->playGameOverMusic();
        mario->marioGoDie();
       QLabel *label=new QLabel("YOU LOSE!!", this);
       label->setFont(QFont("Arial", 50));
       label->show();
       label->setGeometry(450, 100, 1000, 200);
    }
}
