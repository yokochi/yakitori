//
//  TitleScene.h
//  Yakitori
//
//  Created by Akio Yamazaki on 2014/03/16.
//
//

#ifndef __Yakitori__TitleScene__
#define __Yakitori__TitleScene__

#include <iostream>

#include "cocos2d.h"
#include "ZYWebView.h"

#define AD_WEBVIEW_HEIGHT 90

#define TAG_TITLE_SCENE_MENU_SPEAKER 1
#define TAG_TITLE_SCENE_MENU 2

#define ORDER_TITLE_SCENE_MENU 30

#define IMAGE_SPEAKER_ON "speaker_icon.png"
#define IMAGE_SPEAKER_OFF "speaker_icon_off.png"

class TitleScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    TitleScene();
    ~TitleScene();
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuStartCallback(CCObject* pSender);
    void menuMoreAppCallback(CCObject* pSender);
    void menuRankingCallback(CCObject* pSender);
    void menuHelpCallback(CCObject* pSender);
    void menuReviewCallback(CCObject* pSender);
    void menuInfoCallback(CCObject* pSender);
    void menuVolumeCallback();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(TitleScene);
    
private:
    ZYWebView* m_webView;
    
    void initCompornent();
};

#endif /* defined(__Yakitori__TitleScene__) */
