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
#include "NativeBridge.h"
#include "GameManager.h"
#include "AudioUtil.h"

USING_NS_CC;

GameOverScene::GameOverScene()
{
    m_score = 0;
}

GameOverScene::~GameOverScene()
{
//    m_webView->removeWebView();
}

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
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SOUND_ENTER);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(SOUND_GAMEOVER_SCENE);
    
    this->initCompornent();
    return true;
}

void GameOverScene::onEnter()
{
    CCLayer::onEnter();
    AudioUtil::sharedEngine()->playBackgroundMusic(SOUND_GAMEOVER_SCENE, false);
}

void GameOverScene::initCompornent()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* back = CCSprite::create("close_background.jpg");
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
    titleItem->setPosition(ccp(size.width * 0.25, size.height * 0.2));
    
    CCMenuItemImage *retryItem = CCMenuItemImage::create(
                                                         "retry_on.png",
                                                         "retry_off.png",
                                                         this,
                                                         menu_selector(GameOverScene::menuRetryCallback));
    retryItem->setPosition(ccp(size.width * 0.75, size.height * 0.2));
    
    CCMenuItemImage *twitterItem = CCMenuItemImage::create(
                                                         "twitter_on.png",
                                                         "twitter_off.png",
                                                         this,
                                                         menu_selector(GameOverScene::menuTwitterCallback));
    twitterItem->setPosition(ccp(size.width * 0.1, size.height * 0.55));
    
    CCMenuItemImage *facebookItem = CCMenuItemImage::create(
                                                           "facebook_on.png",
                                                           "facebook_off.png",
                                                           this,
                                                           menu_selector(GameOverScene::menuFaceBookCallback));
    facebookItem->setPosition(ccp(size.width * 0.1, size.height * 0.45));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(titleItem, retryItem, twitterItem, facebookItem, NULL);
    pMenu->setPosition(CCPointZero);
    baseLayer->addChild(pMenu);
    
    GameManager* pGameManager = GameManager::sharedGameManager();
    m_score = pGameManager->getPoint();
    bool pIsNewRecord = pGameManager->putScore(m_score);
    
    // label
    CCSprite* waku = CCSprite::create("game_over_sale_waku.png");
    waku->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    baseLayer->addChild(waku, ORDER_GAME_OVER_SCENE_LABEL_WAKU);
    CCSize wakuSize = waku->getContentSize();
    
    if (pIsNewRecord) {
        CCSprite* pNewSprite = CCSprite::create("new.png");
        pNewSprite->setPosition(ccp(size.width * 0.65, size.height * 0.7));
        baseLayer->addChild(pNewSprite, ORDER_GAME_OVER_SCENE_LABEL);
        // gamecenter
        NativeBridge::sendRecordSales(m_score);
    }
    
    CCLabelBMFont* saleLabel = CCLabelBMFont::create(NativeBridge::getLocalizeString("Sale"), "YakitoriFont.fnt");
    saleLabel->setColor(ccc3(0, 0, 0));
    saleLabel->setScale(0.75f);
    saleLabel->setPosition(CCPointMake(wakuSize.width * 0.5, wakuSize.height * 0.85));
    waku->addChild(saleLabel, ORDER_GAME_OVER_SCENE_LABEL);
    
    CCString* pScoreFormat = CCString::createWithFormat(NativeBridge::getLocalizeString("SaleFormat"), m_score);
    CCLabelBMFont* pScoreLabel = CCLabelBMFont::create(pScoreFormat->getCString(), "YakitoriFont.fnt");
    pScoreLabel->setColor(ccc3(0, 0, 0));
    pScoreLabel->setScale(0.75f);
    pScoreLabel->setPosition(CCPointMake(wakuSize.width * 0.5, wakuSize.height * 0.75));
    waku->addChild(pScoreLabel, ORDER_GAME_OVER_SCENE_LABEL);
    
    CCLabelBMFont* bestLabel = CCLabelBMFont::create(NativeBridge::getLocalizeString("BestSale"), "YakitoriFont.fnt");
    bestLabel->setColor(ccc3(0, 0, 0));
    bestLabel->setScale(0.75f);
    bestLabel->setPosition(CCPointMake(wakuSize.width * 0.5, wakuSize.height * 0.55));
    waku->addChild(bestLabel, ORDER_GAME_OVER_SCENE_LABEL);
    
    CCString* pBestScoreFormat = CCString::createWithFormat(NativeBridge::getLocalizeString("SaleFormat"), pGameManager->getHighScore());
    CCLabelBMFont* pBestScoreLabel = CCLabelBMFont::create(pBestScoreFormat->getCString(), "YakitoriFont.fnt");
    pBestScoreLabel->setColor(ccc3(0, 0, 0));
    pBestScoreLabel->setScale(0.75f);
    pBestScoreLabel->setPosition(CCPointMake(wakuSize.width * 0.5, wakuSize.height * 0.45));
    waku->addChild(pBestScoreLabel, ORDER_GAME_OVER_SCENE_LABEL);
    
    CCLabelBMFont* accumulationLabel = CCLabelBMFont::create(NativeBridge::getLocalizeString("AccumulationSales"), "YakitoriFont.fnt");
    accumulationLabel->setColor(ccc3(0, 0, 0));
    accumulationLabel->setScale(0.75f);
    accumulationLabel->setPosition(CCPointMake(wakuSize.width * 0.5, wakuSize.height * 0.25));
    waku->addChild(accumulationLabel, ORDER_GAME_OVER_SCENE_LABEL);
    
    CCString* pAllScoreFormat = CCString::createWithFormat(NativeBridge::getLocalizeString("SaleFormat"), pGameManager->getAllScore());
    CCLabelBMFont* pAllScoreLabel = CCLabelBMFont::create(pAllScoreFormat->getCString(), "YakitoriFont.fnt");
    pAllScoreLabel->setColor(ccc3(0, 0, 0));
    pAllScoreLabel->setScale(0.75f);
    pAllScoreLabel->setPosition(CCPointMake(wakuSize.width * 0.5, wakuSize.height * 0.15));
    waku->addChild(pAllScoreLabel, ORDER_GAME_OVER_SCENE_LABEL);
    
    // gamecenter
    NativeBridge::sendGrossSales(pGameManager->getAllScore());
    
    // webview
    m_webView = new ZYWebView();
    m_webView->init();
    m_webView->showWebView("http://www.shinobigames.jp/ad.html", 0, 0, size.width, AD_WEBVIEW_HEIGHT);
}

void GameOverScene::showViewAfter()
{
    CCLayer* baseLayer = (CCLayer*)this->getChildByTag(TAG_GAME_OVER_SCENE_BASE_LAYER);
    baseLayer->setVisible(true);
}

void GameOverScene::menuTitleCallback(cocos2d::CCObject *pSender)
{
    AudioUtil::sharedEngine()->stopBackgroundMusic(true);
    AudioUtil::sharedEngine()->playEffect(SOUND_ENTER, false);
    m_webView->removeWebView();
    CCScene* scene = (CCScene*)TitleScene::create();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void GameOverScene::menuRetryCallback(cocos2d::CCObject *pSender)
{
    AudioUtil::sharedEngine()->stopBackgroundMusic(true);
    AudioUtil::sharedEngine()->playEffect(SOUND_ENTER, false);
    m_webView->removeWebView();
    CCScene* scene = (CCScene*)GameScene::create();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void GameOverScene::menuTwitterCallback(cocos2d::CCObject *pSender)
{
    AudioUtil::sharedEngine()->playEffect(SOUND_ENTER, false);
    NativeBridge::openTweetDialog(m_score);
}

void GameOverScene::menuFaceBookCallback(cocos2d::CCObject *pSender)
{
    AudioUtil::sharedEngine()->playEffect(SOUND_ENTER, false);
    NativeBridge::openFacebookDialog(m_score);
}