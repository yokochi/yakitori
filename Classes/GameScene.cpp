//
//  GameScene.cpp
//  Yakitori
//
//  Created by Akio Yamazaki on 2014/03/16.
//
//

#include "GameScene.h"
#include "TitleScene.h"
#include "NativeBridge.h"
#include "GameOverScene.h"
#include "GameManager.h"

GameScene::GameScene()
{
    yakitori1 = none;
    yakitori2 = none;
    yakitori3 = none;
    yakitori4 = none;
    yakitori5 = none;
    order1 = none;
    order2 = none;
    order3 = none;
    order4 = none;
    order5 = none;
    orderFlg = false;
    countDown = 0;
    countYakitori1 = 0;
    countYakitori2 = 0;
    countYakitori3 = 0;
    countYakitori4 = 0;
    countYakitori5 = 0;
    yakitori1Status = rare;
    yakitori2Status = rare;
    yakitori3Status = rare;
    yakitori4Status = rare;
    yakitori5Status = rare;
    isPackCatch = false;
    sales = 0;
    lossCost = 0;
    life = 0;
    isGameOver = false;
}

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->initCompornent();
    
    countDown = 3;
    life = USER_MAX_LIFE;
    this->beforeAction();
    return true;
}

void GameScene::initCompornent()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* back = CCSprite::create("game_background.jpg");
    back->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(back, ORDER_GAME_SCENE_BACKGROUND);
    
    CCSprite* back2 = CCSprite::create("game_background2.png");
    back2->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(back2, ORDER_GAME_SCENE_BACKGROUND_2);
    
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("game_main.plist");
    CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("game_main.png");
    this->addChild(batchNode, ORDER_GAME_SCENE_BATCH_NODE, TAG_GAME_SCENE_BATCH_NODE);
    
    // ami
    CCSprite* backAmi = CCSprite::createWithSpriteFrameName(TEXTURE_IMG_YAKITORI_AMI);
    backAmi->setPosition(ccp(size.width * 0.64, size.height * 0.49));
    batchNode->addChild(backAmi, ORDER_GAME_SCENE_BACKGROUND_AMI);
    
    
    // yakitori button
    CCMenuItemImage *yakitori1Item = CCMenuItemImage::create(
                                                         "yakitori_button1.png",
                                                         "yakitori_button1_off.png",
                                                         this,
                                                         menu_selector(GameScene::yakitori1MenuCallback));
    yakitori1Item->setPosition(ccp(size.width * 0.175, size.height * 0.35));
    
    CCMenuItemImage *yakitori2Item = CCMenuItemImage::create(
                                                             "yakitori_button2.png",
                                                             "yakitori_button2_off.png",
                                                             this,
                                                             menu_selector(GameScene::yakitori2MenuCallback));
    yakitori2Item->setPosition(ccp(size.width * 0.5, size.height * 0.35));
    
    CCMenuItemImage *yakitori3Item = CCMenuItemImage::create(
                                                             "yakitori_button3.png",
                                                             "yakitori_button3_off.png",
                                                             this,
                                                             menu_selector(GameScene::yakitori3MenuCallback));
    yakitori3Item->setPosition(ccp(size.width * 0.825, size.height * 0.35));
    
    CCMenuItemImage *yakitori4Item = CCMenuItemImage::create(
                                                             "yakitori_button4.png",
                                                             "yakitori_button4_off.png",
                                                             this,
                                                             menu_selector(GameScene::yakitori4MenuCallback));
    yakitori4Item->setPosition(ccp(size.width * 0.175, size.height * 0.185));
    
    CCMenuItemImage *yakitori5Item = CCMenuItemImage::create(
                                                             "yakitori_button5.png",
                                                             "yakitori_button5_off.png",
                                                             this,
                                                             menu_selector(GameScene::yakitori5MenuCallback));
    yakitori5Item->setPosition(ccp(size.width * 0.5, size.height * 0.185));
    
    CCMenuItemImage *yakitori6Item = CCMenuItemImage::create(
                                                             "yakitori_button6.png",
                                                             "yakitori_button6_off.png",
                                                             this,
                                                             menu_selector(GameScene::yakitori6MenuCallback));
    yakitori6Item->setPosition(ccp(size.width * 0.825, size.height * 0.185));
    
    // home
    CCMenuItemImage *home = CCMenuItemImage::create("home.png", "home.png", this, menu_selector(GameScene::homeMenuCallback));
    home->setPosition(ccp(size.width * 0.1, size.height * 0.95));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(yakitori1Item, yakitori2Item, yakitori3Item, yakitori4Item, yakitori5Item, yakitori6Item, home, NULL);
    pMenu->setPosition(CCPointZero);
    pMenu->setEnabled(false);
    this->addChild(pMenu, ORDER_GAME_SCENE_MENU, TAG_GAME_SCENE_MENU);
    
    // pack
    CCSprite* pack = CCSprite::createWithSpriteFrameName(TEXTURE_IMG_YAKITORI_PACK);
    packPosition = ccp(size.width * 0.125, size.height * 0.5);
    pack->setPosition(packPosition);
    batchNode->addChild(pack, ORDER_GAME_SCENE_YAKITORI_PACK, TAG_GAME_SCENE_YAKITORI_PACK);
    
    CCSprite* packDummy = CCSprite::createWithSpriteFrameName(TEXTURE_IMG_YAKITORI_PACK);
    packDummy->setPosition(packPosition);
    batchNode->addChild(packDummy, ORDER_GAME_SCENE_YAKITORI_PACK_DUMMY);
    
    // score
    CCSprite* saleWaku = CCSprite::createWithSpriteFrameName("sale_waku.png");
    saleWaku->setPosition(ccp(size.width * 0.8, size.height * 0.95));
    batchNode->addChild(saleWaku, ORDER_GAME_SCENE_SCORE_WAKU);
    
    CCString* sale = CCString::createWithFormat(NativeBridge::getLocalizeString("SaleSuffix"), 0);
    CCLabelBMFont* saleLabel = CCLabelBMFont::create(sale->getCString(), "YakitoriFont.fnt");
    saleLabel->setColor(ccc3(0, 0, 0));
    saleLabel->setScale(0.75f);
    saleLabel->setPosition(CCPointMake(size.width * 0.85, size.height * 0.95));
    this->addChild(saleLabel, ORDER_GAME_SCENE_SCORE, TAG_GAME_SCENE_YAKITORI_SALE);
    
    // gauge
    CCSprite* gaugeBase = CCSprite::createWithSpriteFrameName("gauge_base.png");
    gaugeBase->setPosition(ccp(size.width * 0.2, size.height * 0.95));
    gaugeBase->setAnchorPoint(ccp(0, 0.5));
    batchNode->addChild(gaugeBase, ORDER_GAME_SCENE_GAUGE_1);
    
    CCSprite* gaugeBase2 = CCSprite::createWithSpriteFrameName("gauge_base2.png");
    gaugeBase2->setPosition(ccp(size.width * 0.2, size.height * 0.95));
    gaugeBase2->setAnchorPoint(ccp(0, 0.5));
    batchNode->addChild(gaugeBase2, ORDER_GAME_SCENE_GAUGE_2);
    
    CCSprite* gaugeLife = CCSprite::createWithSpriteFrameName("gauge_life.png");
    gaugeLife->setPosition(ccp(size.width * 0.2, size.height * 0.95));
    gaugeLife->setAnchorPoint(ccp(0, 0.5));
    batchNode->addChild(gaugeLife, ORDER_GAME_SCENE_GAUGE_LIFE, TAG_GAME_SCENE_GAUGE_LIFE);
}

void GameScene::beforeAction()
{
    if (countDown <= 0) {
        this->afterAction();
        return;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *text = CCLabelTTF::create(CCString::createWithFormat("%d", countDown--)->getCString(), "MarkerFelt-Thin", 80);
    text->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    text->setColor(ccc3(0, 0, 0));
    this->addChild(text, ORDER_GAME_SCENE_COUNT_DOWN);
    
    CCRotateBy* rotate = CCRotateBy::create(0.25f, 360);
    CCScaleTo* scale = CCScaleTo::create(1.0f, 4.0f);
    CCSpawn* spawn = CCSpawn::create(rotate, scale, NULL);
    CCCallFuncN* funcN = CCCallFuncN::create(this , callfuncN_selector(GameScene::beforeAction));
    CCSequence* sequence = CCSequence::create(spawn, funcN, CCRemoveSelf::create(), NULL);
    text->runAction(sequence);
}

void GameScene::afterAction()
{
    CCMenu* pMenu = (CCMenu*)this->getChildByTag(TAG_GAME_SCENE_MENU);
    pMenu->setEnabled(true);
    this->order();
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    this->scheduleUpdate();
}

void GameScene::update(float delta)
{
    if (!isGameOver) {
        this->updateBakeYakitori();
        this->updateScore();
        this->updateLife();
        if (isGameOver) {
            this->gameOverAction();
        }
    }
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (this->isTouchSprite(pTouch, TAG_YAKITORI1)) {
        this->touchYakitoriAction(this->yakitori1Status, this->yakitori1, TAG_YAKITORI1);
    } else if (this->isTouchSprite(pTouch, TAG_YAKITORI2)) {
        this->touchYakitoriAction(this->yakitori2Status, this->yakitori2, TAG_YAKITORI2);
    } else if (this->isTouchSprite(pTouch, TAG_YAKITORI3)) {
        this->touchYakitoriAction(this->yakitori3Status, this->yakitori3, TAG_YAKITORI3);
    } else if (this->isTouchSprite(pTouch, TAG_YAKITORI4)) {
        this->touchYakitoriAction(this->yakitori4Status, this->yakitori4, TAG_YAKITORI4);
    } else if (this->isTouchSprite(pTouch, TAG_YAKITORI5)) {
        this->touchYakitoriAction(this->yakitori5Status, this->yakitori5, TAG_YAKITORI5);
    } else if (this->isTouchSprite(pTouch, TAG_GAME_SCENE_YAKITORI_PACK)) {
        if (0 < yakitoriList.size()) {
            isPackCatch = true;
        }
    }
    return true;
}

void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isPackCatch) {
        CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)this->getChildByTag(TAG_GAME_SCENE_BATCH_NODE);
        CCSprite* pack = (CCSprite*)batchNode->getChildByTag(TAG_GAME_SCENE_YAKITORI_PACK);
        pack->setPosition(pTouch->getLocation());
    }
}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isPackCatch) {
        CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)this->getChildByTag(TAG_GAME_SCENE_BATCH_NODE);
        CCSprite* pack = (CCSprite*)batchNode->getChildByTag(TAG_GAME_SCENE_YAKITORI_PACK);
        CCSprite* human = (CCSprite*)batchNode->getChildByTag(TAG_GAME_SCENE_HUMAN);
        CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
        
        if (human != NULL && human->boundingBox().intersectsRect(pack->boundingBox())) {
            this->showAlert(thanks);
            bool isOrder = this->checkOrder();
            if (isOrder) {
                human->setDisplayFrame(cache->spriteFrameByName(TEXTURE_IMG_HUMAN_3));
                this->life += USER_UP_LIFE;
            } else {
                human->setDisplayFrame(cache->spriteFrameByName(TEXTURE_IMG_HUMAN_2));
                this->life -= USER_DOWN_LIFE;
            }
            CCSize size = CCDirector::sharedDirector()->getWinSize();
            CCDelayTime* delayTime = CCDelayTime::create(0.75f);
            CCMoveBy* move = CCMoveBy::create(0.5f, ccp(size.width, 0));
            CCSequence* sequence = CCSequence::create(delayTime, move,
                    CCCallFunc::create(this , callfunc_selector(GameScene::order)),
                                                      CCRemoveSelf::create(), NULL);
            human->runAction(sequence);
            
            // fukidashi
            CCSprite* fukidashi = (CCSprite*)batchNode->getChildByTag(TAG_GAME_SCENE_ORDER_FUKIDASHI);
            fukidashi->removeAllChildren();
            batchNode->removeChildByTag(TAG_GAME_SCENE_ORDER_FUKIDASHI);
            
            pack->removeAllChildren();
            yakitoriList.clear();
        }
        pack->setPosition(packPosition);

        isPackCatch = false;
    }
}

void GameScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

void GameScene::touchYakitoriAction(YakitoriStatus status, Yakitori &yakitori, int tag)
{
    if (status == rare) {
        this->showAlert(rare_yakitori);
    } else if (status == medium) {
        this->addPack(tag, yakitori);
        yakitori = none;
    } else if (status == welldone) {
        this->showAlert(well_donw_yakitori);
        this->removeWellDoneYakitori(tag, yakitori);
        this->lossCost += (this->getYakitoriCost(yakitori) * YAKITORI_LOSS_COST);
        this->life -= USER_SMALL_DOWN_LIFE;
        yakitori = none;
    }
}

bool GameScene::isTouchSprite(CCTouch *pTouch, int tag)
{
    CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)this->getChildByTag(TAG_GAME_SCENE_BATCH_NODE);
    
    CCSprite* sprite = (CCSprite*)batchNode->getChildByTag(tag);
    if (sprite != NULL) {
        return sprite->boundingBox().containsPoint(pTouch->getLocation());
    }
    return false;
}


void GameScene::updateBakeYakitori()
{
    this->updateBakeYakitori(this->yakitori1, this->countYakitori1++, TAG_YAKITORI1, this->yakitori1Status);
    this->updateBakeYakitori(this->yakitori2, this->countYakitori2++, TAG_YAKITORI2, this->yakitori2Status);
    this->updateBakeYakitori(this->yakitori3, this->countYakitori3++, TAG_YAKITORI3, this->yakitori3Status);
    this->updateBakeYakitori(this->yakitori4, this->countYakitori4++, TAG_YAKITORI4, this->yakitori4Status);
    this->updateBakeYakitori(this->yakitori5, this->countYakitori5++, TAG_YAKITORI5, this->yakitori5Status);
}

void GameScene::updateBakeYakitori(GameScene::Yakitori yakitori, int count, int tag,
            GameScene::YakitoriStatus &status)
{
    CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)this->getChildByTag(TAG_GAME_SCENE_BATCH_NODE);
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    if (yakitori != none) {
        CCSprite* bakeYakitori = (CCSprite*)batchNode->getChildByTag(tag);
        if (BAKE_YAKITORI_WELL_DONE_TIME <= count) {
            if (status != welldone) {
                const char* imageName = this->getYakitoriFileName(yakitori, welldone);
                bakeYakitori->setDisplayFrame(cache->spriteFrameByName(imageName));
                status = welldone;
            }
        } else if (BAKE_YAKITORI_MEDIUM_TIME <= count) {
            if (status != medium) {
                const char* imageName = this->getYakitoriFileName(yakitori, medium);
                bakeYakitori->setDisplayFrame(cache->spriteFrameByName(imageName));
                status = medium;
            }
        }
    }
}

void GameScene::yakitori1MenuCallback()
{
    this->setYakitori(negima);
}

void GameScene::yakitori2MenuCallback()
{
    this->setYakitori(momo);
}

void GameScene::yakitori3MenuCallback()
{
    this->setYakitori(nankotu);
}

void GameScene::yakitori4MenuCallback()
{
    this->setYakitori(tsukune);
}

void GameScene::yakitori5MenuCallback()
{
    this->setYakitori(lever);
}

void GameScene::yakitori6MenuCallback()
{
    this->setYakitori(kawa);
}

void GameScene::homeMenuCallback()
{
    CCScene* titleScene = (CCScene*)TitleScene::create();
    CCDirector::sharedDirector()->replaceScene(titleScene);
}

bool GameScene::setYakitori(GameScene::Yakitori yakitori)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)this->getChildByTag(TAG_GAME_SCENE_BATCH_NODE);
    if (this->yakitori1 == none) {
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(this->getYakitoriFileName(yakitori, rare));
        sprite->setPosition(ccp(size.width * 0.3, size.height * 0.5));
        batchNode->addChild(sprite, ORDER_GAME_SCENE_YAKITORI, TAG_YAKITORI1);
        this->yakitori1 = yakitori;
        this->countYakitori1 = 0;
        this->yakitori1Status = rare;
        
    } else if (this->yakitori2 == none) {
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(this->getYakitoriFileName(yakitori, rare));
        sprite->setPosition(ccp(size.width * 0.45, size.height * 0.5));
        batchNode->addChild(sprite, ORDER_GAME_SCENE_YAKITORI, TAG_YAKITORI2);
        this->yakitori2 = yakitori;
        this->countYakitori2 = 0;
        this->yakitori2Status = rare;
        
    } else if (this->yakitori3 == none) {
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(this->getYakitoriFileName(yakitori, rare));
        sprite->setPosition(ccp(size.width * 0.6, size.height * 0.5));
        batchNode->addChild(sprite, ORDER_GAME_SCENE_YAKITORI, TAG_YAKITORI3);
        this->yakitori3 = yakitori;
        this->countYakitori3 = 0;
        this->yakitori3Status = rare;
        
    } else if (this->yakitori4 == none) {
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(this->getYakitoriFileName(yakitori, rare));
        sprite->setPosition(ccp(size.width * 0.75, size.height * 0.5));
        batchNode->addChild(sprite, ORDER_GAME_SCENE_YAKITORI, TAG_YAKITORI4);
        this->yakitori4 = yakitori;
        this->countYakitori4 = 0;
        this->yakitori4Status = rare;
        
    } else if (this->yakitori5 == none) {
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(this->getYakitoriFileName(yakitori, rare));
        sprite->setPosition(ccp(size.width * 0.9, size.height * 0.5));
        batchNode->addChild(sprite, ORDER_GAME_SCENE_YAKITORI, TAG_YAKITORI5);
        this->yakitori5 = yakitori;
        this->countYakitori5 = 0;
        this->yakitori5Status = rare;
        
    } else {
        this->showAlert(over_flow);
        return false;
    }
    return true;
}

const char* GameScene::getYakitoriFileName(GameScene::Yakitori yakitori, GameScene::YakitoriStatus status)
{
    std::string result;
    if (negima == yakitori) {
        if (status == rare) {
            result = TEXTURE_IMG_YAKITORI1_1;
        } else if (status == medium) {
            result = TEXTURE_IMG_YAKITORI1_2;
        } else {
            result = TEXTURE_IMG_YAKITORI1_3;
        }
    } else if (momo == yakitori) {
        if (status == rare) {
            result = TEXTURE_IMG_YAKITORI2_1;
        } else if (status == medium) {
            result = TEXTURE_IMG_YAKITORI2_2;
        } else {
            result = TEXTURE_IMG_YAKITORI2_3;
        }
    } else if (nankotu == yakitori) {
        if (status == rare) {
            result = TEXTURE_IMG_YAKITORI3_1;
        } else if (status == medium) {
            result = TEXTURE_IMG_YAKITORI3_2;
        } else {
            result = TEXTURE_IMG_YAKITORI3_3;
        }
    } else if (tsukune == yakitori) {
        if (status == rare) {
            result = TEXTURE_IMG_YAKITORI4_1;
        } else if (status == medium) {
            result = TEXTURE_IMG_YAKITORI4_2;
        } else {
            result = TEXTURE_IMG_YAKITORI4_3;
        }
    } else if (lever == yakitori) {
        if (status == rare) {
            result = TEXTURE_IMG_YAKITORI5_1;
        } else if (status == medium) {
            result = TEXTURE_IMG_YAKITORI5_2;
        } else {
            result = TEXTURE_IMG_YAKITORI5_3;
        }
    } else if (kawa == yakitori) {
        if (status == rare) {
            result = TEXTURE_IMG_YAKITORI6_1;
        } else if (status == medium) {
            result = TEXTURE_IMG_YAKITORI6_2;
        } else {
            result = TEXTURE_IMG_YAKITORI6_3;
        }
    }
    return result.c_str();
}

void GameScene::order()
{
    int orderNum = rand() % 100;
    if (orderNum < 10) {
        order1 = choiceYakitori();
        order2 = none;
        order3 = none;
        order4 = none;
        order5 = none;
    } else if (orderNum <= 20) {
        order1 = choiceYakitori();
        order2 = choiceYakitori();
        order3 = none;
        order4 = none;
        order5 = none;
    } else if (orderNum <= 50) {
        order1 = choiceYakitori();
        order2 = choiceYakitori();
        order3 = choiceYakitori();
        order4 = none;
        order5 = none;
    } else if (orderNum <= 80) {
        order1 = choiceYakitori();
        order2 = choiceYakitori();
        order3 = choiceYakitori();
        order4 = choiceYakitori();
        order5 = none;
    } else {
        order1 = choiceYakitori();
        order2 = choiceYakitori();
        order3 = choiceYakitori();
        order4 = choiceYakitori();
        order5 = choiceYakitori();
        
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)this->getChildByTag(TAG_GAME_SCENE_BATCH_NODE);
    
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(TEXTURE_IMG_HUMAN);
    sprite->setPosition(ccp(size.width * 0.75, size.height * 0.78));
    batchNode->addChild(sprite, ORDER_GAME_SCENE_HUMAN, TAG_GAME_SCENE_HUMAN);
    
    CCSprite* fukidashiOrder = CCSprite::createWithSpriteFrameName(TEXTURE_IMG_ORDER_FUKIDASHI);
    fukidashiOrder->setPosition(ccp(size.width * 0.35, size.height * 0.8));
    batchNode->addChild(fukidashiOrder, ORDER_GAME_SCENE_HUMAN, TAG_GAME_SCENE_ORDER_FUKIDASHI);
    
    CCSprite* orderYakitori1 = CCSprite::createWithSpriteFrameName(this->getYakitoriFileName(order1, medium));
    orderYakitori1->setPosition(ccp(fukidashiOrder->getContentSize().width * 0.2, fukidashiOrder->getContentSize().height * 0.5));
    fukidashiOrder->addChild(orderYakitori1, ORDER_GAME_SCENE_ORDER_YAKITORI, TAG_GAME_SCENE_ORDER_YAKITORI1);
    
    if (order2 != none) {
        CCSprite* orderYakitori2 = CCSprite::createWithSpriteFrameName(this->getYakitoriFileName(order2, medium));
        orderYakitori2->setPosition(ccp(fukidashiOrder->getContentSize().width * 0.35, fukidashiOrder->getContentSize().height * 0.5));
        fukidashiOrder->addChild(orderYakitori2, ORDER_GAME_SCENE_ORDER_YAKITORI, TAG_GAME_SCENE_ORDER_YAKITORI2);
    }
    if (order3 != none) {
        CCSprite* orderYakitori3 = CCSprite::createWithSpriteFrameName(this->getYakitoriFileName(order3, medium));
        orderYakitori3->setPosition(ccp(fukidashiOrder->getContentSize().width * 0.5, fukidashiOrder->getContentSize().height * 0.5));
        fukidashiOrder->addChild(orderYakitori3, ORDER_GAME_SCENE_ORDER_YAKITORI, TAG_GAME_SCENE_ORDER_YAKITORI3);
    }
    if (order4 != none) {
        CCSprite* orderYakitori4 = CCSprite::createWithSpriteFrameName(this->getYakitoriFileName(order4, medium));
        orderYakitori4->setPosition(ccp(fukidashiOrder->getContentSize().width * 0.65, fukidashiOrder->getContentSize().height * 0.5));
        fukidashiOrder->addChild(orderYakitori4, ORDER_GAME_SCENE_ORDER_YAKITORI, TAG_GAME_SCENE_ORDER_YAKITORI4);
    }
    if (order5 != none) {
        CCSprite* orderYakitori5 = CCSprite::createWithSpriteFrameName(this->getYakitoriFileName(order5, medium));
        orderYakitori5->setPosition(ccp(fukidashiOrder->getContentSize().width * 0.8, fukidashiOrder->getContentSize().height * 0.5));
        fukidashiOrder->addChild(orderYakitori5, ORDER_GAME_SCENE_ORDER_YAKITORI, TAG_GAME_SCENE_ORDER_YAKITORI5);
    }
}

GameScene::Yakitori GameScene::choiceYakitori()
{
    int choice = rand() % 6;
    if (negima == choice) {
        return negima;
    } else if (momo == choice) {
        return momo;
    } else if (nankotu == choice) {
        return nankotu;
    } else if (tsukune == choice) {
        return tsukune;
    } else if (lever == choice) {
        return lever;
    } else if (kawa == choice) {
        return kawa;
    }
    return none;
}

void GameScene::showAlert(GameScene::YakitoriAlert alertType)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)this->getChildByTag(TAG_GAME_SCENE_BATCH_NODE);
    
    CCSprite* sprite;
    if (over_flow == alertType) {
        sprite = CCSprite::createWithSpriteFrameName("fukidashi1.png");
    } else if (rare_yakitori == alertType) {
        sprite = CCSprite::createWithSpriteFrameName("rare_alert.png");
    } else if (well_donw_yakitori == alertType) {
        sprite = CCSprite::createWithSpriteFrameName("well_done_alert.png");
    } else if (thanks == alertType) {
        sprite = CCSprite::createWithSpriteFrameName("thanks.png");
    }
    
    sprite->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    batchNode->addChild(sprite, ORDER_GAME_SCENE_FUKIDASHI);
    
    CCDelayTime* delayTime = CCDelayTime::create(0.5f);
    CCSequence* sequence = CCSequence::create(delayTime, CCRemoveSelf::create(), NULL);
    sprite->runAction(sequence);
}

void GameScene::removeWellDoneYakitori(int tag, Yakitori yakitori)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)this->getChildByTag(TAG_GAME_SCENE_BATCH_NODE);
    CCSprite* sprite = (CCSprite*)batchNode->getChildByTag(tag);
    CCMoveBy* move = CCMoveBy::create(0.5f, ccp(size.width, 0));
    CCSequence* sequence = CCSequence::create(move, CCRemoveSelf::create(), NULL);
    
    this->showSaleScore(-(this->getYakitoriCost(yakitori) * YAKITORI_LOSS_COST), sprite->getPositionX(), sprite->getPositionY());
    sprite->runAction(sequence);
}

void GameScene::addPack(int tag, Yakitori yakitori)
{
    CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)this->getChildByTag(TAG_GAME_SCENE_BATCH_NODE);
    batchNode->removeChildByTag(tag);
    
    CCSprite* pack = (CCSprite*)batchNode->getChildByTag(TAG_GAME_SCENE_YAKITORI_PACK);
    
    yakitoriList.push_back(yakitori);
    int addCount = yakitoriList.size();
    float x_positon;
    if (addCount % 3 == 0) {
        x_positon = pack->getContentSize().width * 0.5;
    } else if (addCount % 2 == 0) {
        x_positon = pack->getContentSize().width * 0.75;
    } else {
        x_positon = pack->getContentSize().width * 0.25;
    }
    CCSprite* addYakitori = CCSprite::createWithSpriteFrameName(this->getYakitoriFileName(yakitori, medium));
    addYakitori->setPosition(ccp(x_positon, pack->getContentSize().height * 0.5));
    pack->addChild(addYakitori);
}

bool GameScene::checkOrder()
{
    bool order1Check = false;
    bool order2Check = (order2 == none);
    bool order3Check = (order3 == none);
    bool order4Check = (order4 == none);
    bool order5Check = (order5 == none);
    bool ngOrder = false;

    int tmpSaleCost = 0;
    
    list<Yakitori>::iterator it = yakitoriList.begin();
	while(it != yakitoriList.end())	{
		if (!order1Check && order1 == *it) {
            order1Check = true;
        } else if (!order2Check && order2 == *it) {
            order2Check = true;
        } else if (!order3Check && order3 == *it) {
            order3Check = true;
        } else if (!order4Check && order4 == *it) {
            order4Check = true;
        } else if (!order5Check && order5 == *it) {
            order5Check = true;
        } else {
            ngOrder = true;
        }
        tmpSaleCost += this->getYakitoriCost(*it);
		++it;
	}
    bool result = false;
    if (order1Check && order2Check && order3Check && order4Check && order5Check && !ngOrder) {
        result = true;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    short x = size.width * 0.7;
    short y = size.height * 0.7;
    if (result) {
        this->sales += tmpSaleCost;
        this->showSaleScore(tmpSaleCost, x, y);
    } else {
        tmpSaleCost *= YAKITORI_LOSS_COST;
        this->lossCost += tmpSaleCost;
        this->showSaleScore(-tmpSaleCost, x, y);
    }
    return result;
}

int GameScene::getYakitoriCost(GameScene::Yakitori yakitori)
{
    if (negima == yakitori) {
        return YAKITORI_COST_NEGIMA;
    } else if (momo == yakitori) {
        return YAKITORI_COST_MOMO;
    } else if (nankotu == yakitori) {
        return YAKITORI_COST_NANKOTU;
    } else if (tsukune == yakitori) {
        return YAKITORI_COST_TSUKUNE;
    } else if (lever == yakitori) {
        return YAKITORI_COST_LEVER;
    } else if (kawa == yakitori) {
        return YAKITORI_COST_KAWA;
    }
    return 0;
}

void GameScene::updateScore()
{
    int saleScore = this->sales - this->lossCost;
    CCString* sale = CCString::createWithFormat(NativeBridge::getLocalizeString("SaleSuffix"), saleScore);
    CCLabelBMFont* fontScore = (CCLabelBMFont*)this->getChildByTag(TAG_GAME_SCENE_YAKITORI_SALE);
    fontScore->setCString(sale->getCString());
}

void GameScene::showSaleScore(int saleScore, short positionX, short positionY)
{
    // score
    CCString* sale;
    if (saleScore < 0) {
        sale = CCString::createWithFormat("%d", saleScore);
    } else {
        sale = CCString::createWithFormat("+%d", saleScore);
    }
    CCLabelBMFont* saleLabel = CCLabelBMFont::create(sale->getCString(), "YakitoriFont.fnt");
    if (saleScore <= 0) {
        saleLabel->setColor(ccc3(100, 0, 0));
    } else {
        saleLabel->setColor(ccc3(0, 0, 100));
    }
    saleLabel->setScale(0.5f);
    saleLabel->setPosition(CCPointMake(positionX, positionY));
    
    CCMoveBy* move = CCMoveBy::create(0.75f, ccp(0, 100));
    CCActionInterval* fadeOut = CCFadeOut::create(0.75f);
    CCSpawn* spawn = CCSpawn::create(move, fadeOut, NULL);
    saleLabel->runAction(spawn);
    
    this->addChild(saleLabel, ORDER_GAME_SCENE_SCORE);
}

void GameScene::updateLife()
{
    CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)this->getChildByTag(TAG_GAME_SCENE_BATCH_NODE);
    CCSprite* lifeGauge = (CCSprite*)batchNode->getChildByTag(TAG_GAME_SCENE_GAUGE_LIFE);
    if (USER_MAX_LIFE < --this->life) {
        this->life = USER_MAX_LIFE;
    }
    float ratio = this->life / USER_MAX_LIFE;
    lifeGauge->setScaleX(ratio);
    if (this->life <= 0) {
        isGameOver = true;
    }
}

void GameScene::gameOverAction()
{
    GameManager* gameManager = GameManager::sharedGameManager();
    gameManager->setPoint(this->sales - this->lossCost);
    
    CCScene* scene = (CCScene*)GameOverScene::create();
    CCTransitionMoveInT* move = CCTransitionMoveInT::create(1.5f, scene);
    CCDirector::sharedDirector()->replaceScene(move);
}