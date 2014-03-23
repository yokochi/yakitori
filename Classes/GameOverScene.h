//
//  GameOverScene.h
//  Yakitori
//
//  Created by Akio Yamazaki on 2014/03/23.
//
//

#ifndef __Yakitori__GameOverScene__
#define __Yakitori__GameOverScene__

#include <iostream>

#include "cocos2d.h"

#define ORDER_GAME_OVER_SCENE_BASE_LAYER 10

#define TAG_GAME_OVER_SCENE_BASE_LAYER 1

class GameOverScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameOverScene);
    
private:
    void initCompornent();
    void menuTitleCallback(CCObject* pSender);
    void menuRetryCallback(CCObject* pSender);
    void showViewAfter();
    
};

#endif /* defined(__Yakitori__GameOverScene__) */
