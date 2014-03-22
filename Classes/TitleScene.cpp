//
//  TitleScene.cpp
//  Yakitori
//
//  Created by Akio Yamazaki on 2014/03/16.
//
//

#include "TitleScene.h"
#include "GameScene.h"

USING_NS_CC;

CCScene* TitleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TitleScene *layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
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

void TitleScene::initCompornent()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* back = CCSprite::create("title_background.png");
    back->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(back);
    
    CCMenuItemImage *startItem = CCMenuItemImage::create(
                                                          "start_on.png",
                                                          "start_off.png",
                                                          this,
                                                          menu_selector(TitleScene::menuStartCallback));
    
    startItem->setPosition(ccp(size.width * 0.5, size.height * 0.4));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(startItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
}

void TitleScene::menuStartCallback(CCObject* pSender)
{
    CCScene* gameScene = (CCScene*)GameScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
}