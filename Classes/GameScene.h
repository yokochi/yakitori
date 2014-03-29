//
//  GameScene.h
//  Yakitori
//
//  Created by Akio Yamazaki on 2014/03/16.
//
//

#ifndef __Yakitori__GameScene__
#define __Yakitori__GameScene__

#include <iostream>

#include "cocos2d.h"

#define BAKE_YAKITORI_MEDIUM_TIME 180
#define BAKE_YAKITORI_WELL_DONE_TIME BAKE_YAKITORI_MEDIUM_TIME + 360
#define YAKITORI_LOSS_COST 0.5f
#define USER_MAX_LIFE 2400.0
#define USER_UP_LIFE 300.0
#define USER_DOWN_LIFE 60.0
#define USER_SMALL_DOWN_LIFE 30.0

#define ORDER_GAME_SCENE_BACKGROUND 10
#define ORDER_GAME_SCENE_BACKGROUND_2 11
#define ORDER_GAME_SCENE_BACKGROUND_AMI 15
#define ORDER_GAME_SCENE_MENU 20
#define ORDER_GAME_SCENE_YAKITORI 20
#define ORDER_GAME_SCENE_BATCH_NODE 30
#define ORDER_GAME_SCENE_HUMAN 40
#define ORDER_GAME_SCENE_ORDER_YAKITORI 45
#define ORDER_GAME_SCENE_SCORE_WAKU 50
#define ORDER_GAME_SCENE_SCORE 51
#define ORDER_GAME_SCENE_GAUGE_1 62
#define ORDER_GAME_SCENE_GAUGE_2 60
#define ORDER_GAME_SCENE_GAUGE_LIFE 61
#define ORDER_GAME_SCENE_FUKIDASHI 80
#define ORDER_GAME_SCENE_YAKITORI_PACK_DUMMY 89
#define ORDER_GAME_SCENE_YAKITORI_PACK 90
#define ORDER_GAME_SCENE_COUNT_DOWN 100

#define TAG_YAKITORI1 1
#define TAG_YAKITORI2 2
#define TAG_YAKITORI3 3
#define TAG_YAKITORI4 4
#define TAG_YAKITORI5 5
#define TAG_GAME_SCENE_MENU 10
#define TAG_GAME_SCENE_BATCH_NODE 11
#define TAG_GAME_SCENE_HUMAN 12
#define TAG_GAME_SCENE_ORDER_FUKIDASHI 13
#define TAG_GAME_SCENE_ORDER_YAKITORI1 14
#define TAG_GAME_SCENE_ORDER_YAKITORI2 15
#define TAG_GAME_SCENE_ORDER_YAKITORI3 16
#define TAG_GAME_SCENE_ORDER_YAKITORI4 17
#define TAG_GAME_SCENE_ORDER_YAKITORI5 18
#define TAG_GAME_SCENE_YAKITORI_PACK 30
#define TAG_GAME_SCENE_YAKITORI_SALE 31
#define TAG_GAME_SCENE_GAUGE_LIFE 40

#define TEXTURE_IMG_YAKITORI1_1 "yakitori1.png"
#define TEXTURE_IMG_YAKITORI1_2 "yakitori1_2.png"
#define TEXTURE_IMG_YAKITORI1_3 "yakitori1_3.png"
#define TEXTURE_IMG_YAKITORI2_1 "yakitori2.png"
#define TEXTURE_IMG_YAKITORI2_2 "yakitori2_2.png"
#define TEXTURE_IMG_YAKITORI2_3 "yakitori2_3.png"
#define TEXTURE_IMG_YAKITORI3_1 "yakitori3.png"
#define TEXTURE_IMG_YAKITORI3_2 "yakitori3_2.png"
#define TEXTURE_IMG_YAKITORI3_3 "yakitori3_3.png"
#define TEXTURE_IMG_YAKITORI4_1 "yakitori4.png"
#define TEXTURE_IMG_YAKITORI4_2 "yakitori4_2.png"
#define TEXTURE_IMG_YAKITORI4_3 "yakitori4_3.png"
#define TEXTURE_IMG_YAKITORI5_1 "yakitori5.png"
#define TEXTURE_IMG_YAKITORI5_2 "yakitori5_2.png"
#define TEXTURE_IMG_YAKITORI5_3 "yakitori5_3.png"
#define TEXTURE_IMG_YAKITORI6_1 "yakitori6.png"
#define TEXTURE_IMG_YAKITORI6_2 "yakitori6_2.png"
#define TEXTURE_IMG_YAKITORI6_3 "yakitori6_3.png"
#define TEXTURE_IMG_HUMAN "human.png"
#define TEXTURE_IMG_HUMAN_2 "human_2.png"
#define TEXTURE_IMG_HUMAN_3 "human_3.png"
#define TEXTURE_IMG_ORDER_FUKIDASHI "fukidashi_order.png"
#define TEXTURE_IMG_YAKITORI_PACK "yakitori_pack.png"
#define TEXTURE_IMG_YAKITORI_AMI "yakiami.png"

#define YAKITORI_COST_NEGIMA 90
#define YAKITORI_COST_MOMO 120
#define YAKITORI_COST_NANKOTU 110
#define YAKITORI_COST_TSUKUNE 140
#define YAKITORI_COST_LEVER 80
#define YAKITORI_COST_KAWA 100

USING_NS_CC;
using namespace std;

class GameScene : public cocos2d::CCLayer
{
public:
    GameScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    
    virtual void update(float delta);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
    enum Yakitori {
        negima = 0,
        momo = 1,
        nankotu = 2,
        tsukune = 3,
        lever = 4,
        kawa = 5,
        none = 6,
    };
    enum YakitoriStatus {
        rare,
        medium,
        welldone
    };
    enum YakitoriAlert {
        over_flow,
        rare_yakitori,
        well_donw_yakitori,
        thanks,
    };
    Yakitori yakitori1;
    Yakitori yakitori2;
    Yakitori yakitori3;
    Yakitori yakitori4;
    Yakitori yakitori5;
    list<Yakitori> yakitoriList;
    
    Yakitori order1;
    Yakitori order2;
    Yakitori order3;
    Yakitori order4;
    Yakitori order5;
    
    YakitoriStatus yakitori1Status;
    YakitoriStatus yakitori2Status;
    YakitoriStatus yakitori3Status;
    YakitoriStatus yakitori4Status;
    YakitoriStatus yakitori5Status;
    
    CCPoint packPosition;
    
    bool orderFlg;
    short countDown;
    int countYakitori1;
    int countYakitori2;
    int countYakitori3;
    int countYakitori4;
    int countYakitori5;
    bool isPackCatch;
    int sales;// 売り上げ
    int lossCost;
    float life;
    bool isGameOver;
    
    void initCompornent();
    void beforeAction();
    void afterAction();
    void gameOverAction();
    void yakitori1MenuCallback();
    void yakitori2MenuCallback();
    void yakitori3MenuCallback();
    void yakitori4MenuCallback();
    void yakitori5MenuCallback();
    void yakitori6MenuCallback();
    void homeMenuCallback();
    bool setYakitori(Yakitori yakitori);
    const char* getYakitoriFileName(Yakitori yakitori, YakitoriStatus status);
    void order();
    Yakitori choiceYakitori();
    void updateBakeYakitori();
    void updateBakeYakitori(Yakitori yakitori, int count, int tag, YakitoriStatus &status);
    bool isTouchSprite(CCTouch *pTouch, int tag);
    void showAlert(YakitoriAlert alertType);
    void removeWellDoneYakitori(int tag, Yakitori yaitori);
    void touchYakitoriAction(YakitoriStatus status, Yakitori &yakitori, int tag);
    void addPack(int tag, Yakitori yakitori);
    bool checkOrder();
    int getYakitoriCost(Yakitori yakitori);
    void updateScore();
    void showSaleScore(int saleScore, short positionX, short positionY);
    void updateLife();
};

#endif /* defined(__Yakitori__GameScene__) */
