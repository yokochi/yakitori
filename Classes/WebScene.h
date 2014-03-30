//
//  WebScene.h
//  jump
//
//  Created by Akio Yamazaki on 2014/02/20.
//
//

#ifndef __jump__WebScene__
#define __jump__WebScene__

#include <iostream>
#include "ZYWebView.h"

#define ORDER_WEBSCENE_BACKGROUND 10
#define ORDER_WEBSCENE_TOP_LABEL 15
#define ORDER_WEBSCENE_MENU 20


class WebScene : public cocos2d::CCLayer
{
public:
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    virtual void onEnter();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(WebScene);
    //    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TitleScene, create);
    
private:
    ZYWebView* m_webView;
    
    void backTitle();
    void initCompornent();
};

#endif /* defined(__jump__WebScene__) */
