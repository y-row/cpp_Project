Supermario
group 1 member:E24119029許彥喬、AN4104016楊子毅、E14104080廖奕喆
----------------------------------------


#overall description
----------------------------------------
1.按下START之後開始遊戲
2.使用方向鍵使瑪莉歐跳躍、平滑移動瑪莉歐
3.若吃到火焰花(Fire flower)則可以按下左鍵發射最多三顆火焰彈射擊怪物。射擊不能在跳躍時進行，並且使用滑鼠瞄準。
4.碰到怪物則會扣除一點生命值，兩秒內不會再被同一隻扣血；同時子彈數量還會清零，馬莉歐會變小
5若吃到大蘑菇則會獲得一點生命值並且變大，馬莉歐最多可以有3hp
6.在第二個水管按下下鍵則可以進入隱藏場景，進入隱藏場景後，在第二個frame的最後一個水管上按下鍵，可以返回原場景。
7.整場遊戲必須集滿20個金幣以上並觸碰旗桿即為遊戲勝利。
8.若生命值歸0或掉入洞中，則會死掉。


#class description
----------------------------------------
Basic Requirements:
GameBase:
作為遊戲的主畫面
1.顯示磚塊(普通磚、破壞磚、石磚、問號磚)
2.顯示怪物(蘑菇、花、烏龜)
3.顯示道具(金幣、無敵星星、變大蘑菇、火焰花)
4.顯示狀態(hp、分數、子彈數量)
5.顯示旗子與旗桿
6.顯示開始畫面、結束畫面
7.將視角固定在馬莉歐身上
8.進入水管的轉場畫面

mario:  
1.道具、磚塊、地板跟馬莉歐的碰撞
2.瑪莉歐碰到物件狀態改變(碰到道具、怪物)
3.平滑左右移動、重力跳躍、移動及死亡圖片
4.滑鼠左鍵可以射出子彈  
5.掉到洞裡死亡、必須跳躍才能跨過洞、不能二段跳 

Broken brick:
1.由下往上撞會消失

Box brick:
1.每個畫面只有1或2個
2.mario碰到下面生成coin或super mushroom或fire flower並轉成stone brick

normal brick
1.有藏金幣的，可以由下往上撞產生

Super mushroom:
1.瑪莉歐碰到會消失
2.碰到瑪莉歐hp+1
3.小瑪莉歐碰到變大瑪莉歐
4.碰到box brick後才生成
5.生成後一直往右跑，碰到水管、子彈、磚塊時反彈
6.可以踩在所有brick以及水管上，懸空時會往下掉

Fire flower:
1.碰到box brick底部後有機會生成
2.瑪莉歐碰到後將子彈設為3發
3.瑪莉歐碰到會消失

Coin:
1.增加分數
2.不能生成在地板(floor)
3.每個畫面最多只有10個
4.整個遊戲最多只有40個
5. Mario碰到會消失

Flag&flagpole:
1.放在畫面最後的brick上
2.碰到後判斷遊戲是否勝利
3.印出x座標

Toxic mushroom:
1.每個畫面至少有1個
2.生成後一直往右跑，碰到水管、磚塊時反彈
3.可以踩在所有brick以及水管上，懸空時會往下掉
4.碰到後馬力歐生命 -1、大mario變小、不能射子彈直到再次碰到fire flower且2秒內不會再被扣血
5.從上面碰到後被踩扁，過0.5秒後消失，不扣血
6.子彈碰到就消失

bullet:
1.碰到所有brick和水管後消失
2.點擊滑鼠左鍵發射且飛向左鍵點擊的位置
3.碰到怪物會消滅怪物

Bonus:
Super star:
1.碰到mario後可以消失
2.碰到以後無敵4秒，期間碰到怪物不會扣血且會直接死去

Turtle:
1.踩到之後會變成龜殼，過3秒後會變回去
2.龜殼狀態下再踩到會在地板上移動，期間碰到怪物可以消滅牠們。

Flower:
1.每8秒出現在管子上
2.出現在管子上的時候馬力歐碰到後馬力歐生命 -1、大mario變小、不能射子彈直到再次碰到fire flower且2秒內不會再被扣血

Water pipe:
1.放置食人花
2.可以按方向鍵下進入隱藏關

multimedia:
1.新增多種音效，共11種

Compile&Execute
----------------------------------------
1.安裝qt creator後點擊進行。
