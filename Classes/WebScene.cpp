//
//  WebScene.cpp
//  jump
//
//  Created by Akio Yamazaki on 2014/02/20.
//
//

#include "WebScene.h"
#include "TitleScene.h"
#include "AudioUtil.h"

CCScene* WebScene::scene()
{
    CCScene *scene = CCScene::create();
    WebScene *layer = WebScene::create();
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool WebScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SOUND_EFFECT1);
    this->initCompornent();
    
    return true;
}

void WebScene::onEnter()
{
    CCLayer::onEnter();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //デバイスがiOSの時
    m_webView->showWebView("http://www.shinobigames.jp/", 0, 50, winSize.width * 0.5, winSize.height * 0.5 - 100);
#else
    //デバイスがAndroidの時
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    m_webView->showWebView("http://www.shinobigames.jp/index_android.html", 0, screenSize.height * 0.1, screenSize.width, screenSize.height - (screenSize.height * 0.2));
#endif
}

void WebScene::initCompornent()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_webView = new ZYWebView();
    m_webView->init();
    
    CCLayerColor* background = CCLayerColor::create(ccc4(0, 0, 0, 255), winSize.width, winSize.height);
    this->addChild(background, ORDER_WEBSCENE_BACKGROUND);
    
    CCLabelTTF* topLabel = CCLabelTTF::create("@shinobigames.jp", "MarkerFelt-Thin", 32);
    topLabel->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.95f));
    this->addChild(topLabel, ORDER_WEBSCENE_TOP_LABEL);
    
    CCMenuItemImage* home = CCMenuItemImage::create("back_on.png", "back_off.png", this, menu_selector(WebScene::backTitle));
    
    CCMenu* topMenu = CCMenu::create(home, NULL);
    topMenu->setPosition(ccp(0, 0));
    
    home->setPosition(ccp(winSize.width*0.15f, winSize.height*0.95f));
    
    this->addChild(topMenu, ORDER_WEBSCENE_MENU);
}

void WebScene::backTitle()
{
//    AudioUtil::sharedEngine()->playEffect(SOUND_EFFECT1, false);
    m_webView->removeWebView();
    CCScene *pScene = TitleScene::scene();
    
    CCTransitionMoveInT* transition = CCTransitionMoveInT::create(0.5f, pScene);
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->replaceScene(transition);
}