//
//  GameOverScene.cpp
//  Yakitori
//
//  Created by Akio Yamazaki on 2014/03/23.
//
//

#include "GameOverScene.h"
#include "GameScene.h"
#include "TitleScene.h"

USING_NS_CC;

CCScene* GameOverScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameOverScene *layer = GameOverScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->initCompornent();
    return true;
}

void GameOverScene::onEnter()
{
    CCLayer::onEnter();
}

void GameOverScene::initCompornent()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* back = CCSprite::create("close_background.png");
    back->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(back);
    
    CCLayer* baseLayer = CCLayer::create();
    baseLayer->setVisible(false);
    this->addChild(baseLayer, ORDER_GAME_OVER_SCENE_BASE_LAYER, TAG_GAME_OVER_SCENE_BASE_LAYER);
    CCDelayTime* delayTime = CCDelayTime::create(1.5f);
    CCCallFuncN* funcN = CCCallFuncN::create(this , callfuncN_selector(GameOverScene::showViewAfter));
    CCSequence* sequence = CCSequence::create(delayTime, funcN, NULL);
    baseLayer->runAction(sequence);

    CCMenuItemImage *titleItem = CCMenuItemImage::create(
                                                         "for_title_on.png",
                                                         "for_title_off.png",
                                                         this,
                                                         menu_selector(GameOverScene::menuTitleCallback));
    titleItem->setPosition(ccp(size.width * 0.3, size.height * 0.3));
    
    CCMenuItemImage *retryItem = CCMenuItemImage::create(
                                                         "retry_on.png",
                                                         "retry_off.png",
                                                         this,
                                                         menu_selector(GameOverScene::menuRetryCallback));
    retryItem->setPosition(ccp(size.width * 0.7, size.height * 0.3));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(titleItem, retryItem, NULL);
    pMenu->setPosition(CCPointZero);
    baseLayer->addChild(pMenu);
}

void GameOverScene::showViewAfter()
{
    CCLayer* baseLayer = (CCLayer*)this->getChildByTag(TAG_GAME_OVER_SCENE_BASE_LAYER);
    baseLayer->setVisible(true);
}

void GameOverScene::menuTitleCallback(cocos2d::CCObject *pSender)
{
    CCScene* scene = (CCScene*)TitleScene::create();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void GameOverScene::menuRetryCallback(cocos2d::CCObject *pSender)
{
    CCScene* scene = (CCScene*)GameScene::create();
    CCDirector::sharedDirector()->replaceScene(scene);
}