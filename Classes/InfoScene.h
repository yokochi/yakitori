//
//  InfoScene.h
//  Yakitori
//
//  Created by Akio Yamazaki on 2014/04/10.
//
//

#ifndef __Yakitori__InfoScene__
#define __Yakitori__InfoScene__

#include <iostream>

#include "cocos2d.h"

class InfoScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(InfoScene);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
private:
    
    void initCompornent();
};

#endif /* defined(__Yakitori__InfoScene__) */
