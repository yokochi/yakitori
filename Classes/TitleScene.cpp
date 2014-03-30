//
//  TitleScene.cpp
//  Yakitori
//
//  Created by Akio Yamazaki on 2014/03/16.
//
//

#include "TitleScene.h"
#include "GameScene.h"
#include "WebScene.h"
#include "NativeBridge.h"

USING_NS_CC;

TitleScene::TitleScene()
{
    
}

TitleScene::~TitleScene()
{
    m_webView->removeWebView();
}

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
    CCSprite* back = CCSprite::create("title_background.jpg");
    back->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(back);
    
    CCSprite* pTitle = CCSprite::create("start_title.png");
    pTitle->setPosition(ccp(size.width * 0.5, size.height * 0.65));
    this->addChild(pTitle);
    
    CCMenuItemImage *startItem = CCMenuItemImage::create(
                                                          "start_on.png",
                                                          "start_off.png",
                                                          this,
                                                          menu_selector(TitleScene::menuStartCallback));
    
    startItem->setPosition(ccp(size.width * 0.275, size.height * 0.3));
    
    CCMenuItemImage *pHelpItem = CCMenuItemImage::create(
                                                         "help_on.png",
                                                         "help_off.png",
                                                         this,
                                                         menu_selector(TitleScene::menuHelpCallback));
    
    pHelpItem->setPosition(ccp(size.width * 0.725, size.height * 0.3));
    
    CCMenuItemImage *pMoreAppItem = CCMenuItemImage::create(
                                                         "more_on.png",
                                                         "more_off.png",
                                                         this,
                                                         menu_selector(TitleScene::menuMoreAppCallback));
    
    pMoreAppItem->setPosition(ccp(size.width * 0.275, size.height * 0.2));
    
    CCMenuItemImage *pRankingItem = CCMenuItemImage::create(
                                                            "ranking_on.png",
                                                            "ranking_off.png",
                                                            this,
                                                            menu_selector(TitleScene::menuRankingCallback));
    
    pRankingItem->setPosition(ccp(size.width * 0.725, size.height * 0.2));
    
    CCMenuItemImage *pReviewItem = CCMenuItemImage::create(
                                                            "review_on.png",
                                                            "review_on.png",
                                                            this,
                                                            menu_selector(TitleScene::menuReviewCallback));
    
    pReviewItem->setPosition(ccp(size.width * 0.725, size.height * 0.45));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(startItem, pHelpItem, pMoreAppItem, pRankingItem, pReviewItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
    
    // webview
    m_webView = new ZYWebView();
    m_webView->init();
    m_webView->showWebView("http://www.shinobigames.jp/ad_icon.html", 0, 0, size.width, AD_WEBVIEW_HEIGHT);
}

void TitleScene::menuStartCallback(CCObject* pSender)
{
    m_webView->removeWebView();
    CCScene* gameScene = (CCScene*)GameScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
}

void TitleScene::menuHelpCallback(cocos2d::CCObject *pSender)
{
    
}

void TitleScene::menuMoreAppCallback(cocos2d::CCObject *pSender)
{
    m_webView->removeWebView();
    CCScene* scene = (CCScene*)WebScene::create();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void TitleScene::menuRankingCallback(cocos2d::CCObject *pSender)
{
    
}

void TitleScene::menuReviewCallback(cocos2d::CCObject *pSender)
{
    NativeBridge::openAppStore();
}