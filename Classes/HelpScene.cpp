//
//  HelpScene.cpp
//  Yakitori
//
//  Created by Akio Yamazaki on 2014/04/01.
//
//

#include "HelpScene.h"
#include "TitleScene.h"
#include "AudioUtil.h"
#include "NativeBridge.h"

USING_NS_CC;

CCScene* HelpScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelpScene *layer = HelpScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SOUND_ENTER);
    
    this->initCompornent();
    return true;
}

void HelpScene::initCompornent()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* back = CCSprite::create("title_background.jpg");
    back->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(back);
    
    CCString* pHelpString = CCString::createWithFormat("%s_%s", NativeBridge::getCurrentLanguage(), "help.png");
    CCSprite* pHelpSprite = CCSprite::create(pHelpString->getCString());
    pHelpSprite->setPosition(ccp(size.width * 0.5, size.height * 0.55));
    this->addChild(pHelpSprite);
    
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    this->scheduleUpdate();
}

bool HelpScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    AudioUtil::sharedEngine()->playEffect(SOUND_ENTER, false);
    return true;
}

void HelpScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}
void HelpScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCScene* gameScene = (CCScene*)TitleScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
}

void HelpScene::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
}