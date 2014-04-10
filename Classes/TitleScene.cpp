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
#include "HelpScene.h"
#include "AudioUtil.h"
#include "InfoScene.h"

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
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SOUND_ENTER);
    
    this->initCompornent();
    NativeBridge::showAppCMarqueeView();
    return true;
}

void TitleScene::initCompornent()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* back = CCSprite::create("title_background.jpg");
    back->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(back);
    
    CCString* pTitleString = CCString::createWithFormat("%s_%s", NativeBridge::getCurrentLanguage(), "start_title.png");
    CCSprite* pTitle = CCSprite::create(pTitleString->getCString());
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
                                                            "review_off.png",
                                                            this,
                                                            menu_selector(TitleScene::menuReviewCallback));
    
    pReviewItem->setPosition(ccp(size.width * 0.725, size.height * 0.4));
    
    CCMenuItemImage *pInfoItem = CCMenuItemImage::create(
                                                           "i_icon.png",
                                                           "i_icon_off.png",
                                                           this,
                                                           menu_selector(TitleScene::menuInfoCallback));
    
    pInfoItem->setPosition(ccp(size.width * 0.25, size.height * 0.81));
    
    // speaker
    std::string pSpeakerIcon;
    if (AudioUtil::sharedEngine()->isVolume) {
        pSpeakerIcon = IMAGE_SPEAKER_ON;
    } else {
        pSpeakerIcon = IMAGE_SPEAKER_OFF;
    }
    CCMenuItemImage *pVolumeMenu = CCMenuItemImage::create(pSpeakerIcon.c_str(), pSpeakerIcon.c_str(), this, menu_selector(TitleScene::menuVolumeCallback));
    pVolumeMenu->setPosition(size.width * 0.1, size.height * 0.81);
    pVolumeMenu->setTag(TAG_TITLE_SCENE_MENU_SPEAKER);
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(startItem, pHelpItem, pMoreAppItem, pRankingItem, pReviewItem,pInfoItem, pVolumeMenu, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, ORDER_TITLE_SCENE_MENU, TAG_TITLE_SCENE_MENU);
    
    // webview
    m_webView = new ZYWebView();
    m_webView->init();
    m_webView->showWebView("http://www.shinobigames.jp/ad_icon.html", 0, 0, size.width, AD_WEBVIEW_HEIGHT);
}

void TitleScene::menuStartCallback(CCObject* pSender)
{
    AudioUtil::sharedEngine()->playEffect(SOUND_ENTER, false);
    
    m_webView->removeWebView();
    CCScene* gameScene = (CCScene*)GameScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
    NativeBridge::removeAppCMarqueeView();
}

void TitleScene::menuHelpCallback(cocos2d::CCObject *pSender)
{
    AudioUtil::sharedEngine()->playEffect(SOUND_ENTER, false);
    
    m_webView->removeWebView();
    CCScene* scene = (CCScene*)HelpScene::create();
    CCDirector::sharedDirector()->replaceScene(scene);
    NativeBridge::removeAppCMarqueeView();
}

void TitleScene::menuMoreAppCallback(cocos2d::CCObject *pSender)
{
    AudioUtil::sharedEngine()->playEffect(SOUND_ENTER, false);
    
    m_webView->removeWebView();
    if (strcmp(NativeBridge::getCurrentLanguage(), "ja") == 0) {
        CCScene* scene = (CCScene*)WebScene::create();
        CCDirector::sharedDirector()->replaceScene(scene);
    } else {
        NativeBridge::openAppStoreList();
    }
}

void TitleScene::menuRankingCallback(cocos2d::CCObject *pSender)
{
    AudioUtil::sharedEngine()->playEffect(SOUND_ENTER, false);
    NativeBridge::showBord();
}

void TitleScene::menuReviewCallback(cocos2d::CCObject *pSender)
{
    AudioUtil::sharedEngine()->playEffect(SOUND_ENTER, false);
    NativeBridge::openAppStore();
}

void TitleScene::menuInfoCallback(cocos2d::CCObject *pSender)
{
    AudioUtil::sharedEngine()->playEffect(SOUND_ENTER, false);
    
    m_webView->removeWebView();
    CCScene* scene = (CCScene*)InfoScene::create();
    CCDirector::sharedDirector()->replaceScene(scene);
    NativeBridge::removeAppCMarqueeView();
}

void TitleScene::menuVolumeCallback()
{
    AudioUtil* pAudioUtil = AudioUtil::sharedEngine();
    pAudioUtil->changeVolume();
    
    CCMenu* pMenu = (CCMenu*)this->getChildByTag(TAG_TITLE_SCENE_MENU);
    CCMenuItemImage* pSpeaker = (CCMenuItemImage*)pMenu->getChildByTag(TAG_TITLE_SCENE_MENU_SPEAKER);
    
    if (pAudioUtil->isVolume) {
        CCSprite* pSpeakerOn = CCSprite::create(IMAGE_SPEAKER_ON);
        pSpeaker->setNormalImage(pSpeakerOn);
        pSpeaker->setSelectedImage(pSpeakerOn);
        
    } else {
        CCSprite* pSpeakerOff = CCSprite::create(IMAGE_SPEAKER_OFF);
        pSpeaker->setNormalImage(pSpeakerOff);
        pSpeaker->setSelectedImage(pSpeakerOff);

    }
    pAudioUtil->playEffect(SOUND_ENTER, false);
}